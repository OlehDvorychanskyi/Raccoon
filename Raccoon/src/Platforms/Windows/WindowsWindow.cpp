#include <Platforms/Windows/WindowsWindow.h>
#include <Raccoon/Core/Assert.h>

#include <codecvt>

#include <Raccoon/Events/WindowEvents.h>
#include <Raccoon/Events/KeyEvents.h>
#include <Raccoon/Events/MouseEvents.h>

#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Raccoon::WindowData* data = reinterpret_cast<Raccoon::WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_DESTROY:
        data->Callback(std::make_shared<Raccoon::WindowCloseEvent>());
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        data->Props.Width = LOWORD(lParam);
        data->Props.Height = HIWORD(lParam);
        data->Callback(std::make_shared<Raccoon::WindowResizeEvent>(data->Props.Width, data->Props.Height));
        break;

    case WM_LBUTTONDOWN:
        data->Callback(std::make_shared<Raccoon::MouseButtonPressedEvent>(VK_LBUTTON));
        break;
    case WM_MBUTTONDOWN:
        data->Callback(std::make_shared<Raccoon::MouseButtonPressedEvent>(VK_MBUTTON));
        break;
    case WM_RBUTTONDOWN:
        data->Callback(std::make_shared<Raccoon::MouseButtonPressedEvent>(VK_RBUTTON));
        break;

    case WM_LBUTTONUP:
        data->Callback(std::make_shared<Raccoon::MouseButtonReleasedEvent>(VK_LBUTTON));
        break;
    case WM_MBUTTONUP:
        data->Callback(std::make_shared<Raccoon::MouseButtonReleasedEvent>(VK_MBUTTON));
        break;
    case WM_RBUTTONUP:
        data->Callback(std::make_shared<Raccoon::MouseButtonReleasedEvent>(VK_RBUTTON));
        break;

    case WM_MOUSEMOVE:
        data->Callback(std::make_shared<Raccoon::MouseMovedEvent>(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;
    case WM_MOUSEWHEEL:
        data->Callback(std::make_shared<Raccoon::MouseScrolledEvent>(GET_WHEEL_DELTA_WPARAM(wParam), 0.f));
        break;

    case WM_KEYDOWN:
        data->Callback(std::make_shared<Raccoon::KeyPressedEvent>(wParam));
        break;
    case WM_KEYUP:
        data->Callback(std::make_shared<Raccoon::KeyReleasedEvent>(wParam));
        break;
    case WM_CHAR:
        data->Callback(std::make_shared<Raccoon::KeyTypedEvent>(static_cast<char>(wParam)));
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    };

    return 0;
}

namespace Raccoon
{
    WNDCLASS WindowsWindow::s_WindowClass = {0};

    WindowsWindow::WindowsWindow(const WindowProperties &props)
        : m_Data {props} 
    {
        if (Window::s_WindowCount == 1)
            InitWindowClass();

        InitWindow();
    }

    WindowsWindow::~WindowsWindow()
    {
        DestroyWindow(m_NativeWindow);
        
        if (Window::s_WindowCount == 1)
            UnregisterClass(s_WindowClass.lpszClassName, GetModuleHandle(NULL));
    }

    void WindowsWindow::InitWindowClass()
    {
        s_WindowClass = { 0 };
        s_WindowClass.lpfnWndProc = WindowProc;
        s_WindowClass.hInstance = GetModuleHandle(NULL);
        s_WindowClass.hbrBackground = nullptr;
        s_WindowClass.lpszClassName = L"WindowClass";

        RE_CORE_ASSERT(RegisterClass(&s_WindowClass), "Fail to register window class");
    }

    void WindowsWindow::InitWindow()
    {
        RECT rc = { 0, 0, (LONG)m_Data.Props.Width, (LONG)m_Data.Props.Height }; // add position here 
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        m_NativeWindow = CreateWindowEx(0, s_WindowClass.lpszClassName, converter.from_bytes(m_Data.Props.Title).c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, s_WindowClass.hInstance, nullptr);

        RE_CORE_ASSERT(m_NativeWindow, "Fail to create a window");
        
        m_Data.Callback = [this](std::shared_ptr<Event> event)
        {
            this->m_Events.AddEvent(event);
        };

        SetWindowLongPtr(m_NativeWindow, GWLP_USERDATA, (LONG_PTR)&m_Data);

        ShowWindow(m_NativeWindow, SW_SHOWDEFAULT);
    }

    void Window::ProcessInternalEvents()
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WindowsWindow::SetTitle(const std::string &title)
    {
        m_Data.Props.Title = title;

        std::wstring wTitle(title.begin(), title.end());
        SetWindowTextW(m_NativeWindow, wTitle.c_str());
    }

    void WindowsWindow::Resize(uint32_t width, uint32_t height)
    {
        m_Data.Props.Width = width; 
        m_Data.Props.Height = height; 

        MoveWindow(m_NativeWindow, 0, 0, width, height, FALSE);
    }

    void WindowsWindow::OnWindowClose(WindowCloseEvent &event)
    {
        m_ShouldClose = true;
    }

    void WindowsWindow::OnWindowResize(WindowResizeEvent &event)
    {
        
    }
}
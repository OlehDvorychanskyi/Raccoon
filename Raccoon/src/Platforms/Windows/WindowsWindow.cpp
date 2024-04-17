#include <Platforms/Windows/WindowsWindow.h>
#include <Raccoon/Core/Assert.h>

#include <codecvt>

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
        s_WindowClass.lpfnWndProc = DefWindowProc;
        s_WindowClass.hInstance = GetModuleHandle(NULL);
        s_WindowClass.hbrBackground = nullptr;
        s_WindowClass.lpszClassName = L"WindowClass";

        RE_CORE_ASSERT(RegisterClass(&s_WindowClass), "Fail to register window class");
    }

    void WindowsWindow::InitWindow()
    {
        RECT rc = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height }; // add position here 
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        m_NativeWindow = CreateWindowEx(0, s_WindowClass.lpszClassName, converter.from_bytes(m_Data.Title).c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, s_WindowClass.hInstance, nullptr);

        RE_CORE_ASSERT(m_NativeWindow, "Fail to create a window");

        ShowWindow(m_NativeWindow, SW_SHOWDEFAULT);
    }

    void WindowsWindow::ProcessEvents()
    {
        
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
        m_Data.Title = title;

        std::wstring wTitle(title.begin(), title.end());
        SetWindowTextW(m_NativeWindow, wTitle.c_str());
    }

    void WindowsWindow::Resize(uint32_t width, uint32_t height)
    {
        m_Data.Width = width; 
        m_Data.Height = height; 

        MoveWindow(m_NativeWindow, 0, 0, width, height, FALSE);
    }
}

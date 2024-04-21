#pragma once 
#include <cstdint>

#ifdef RE_WIN32_WINDOW
    #include <Windows.h>
#endif

namespace Raccoon 
{
    using KeyCode = int16_t;

    namespace Key
    {
        enum : KeyCode
        {
            #ifdef RE_GLFW_WINDOW
                Unknown = -1,

                A = 65,
                B = 66,
                C = 67,
                D = 68,
                E = 69,
                F = 70,
                G = 71,
                H = 72,
                I = 73,
                J = 74,
                K = 75,
                L = 76,
                M = 77,
                N = 78,
                O = 79,
                P = 80,
                Q = 81,
                R = 82,
                S = 83,
                T = 84,
                U = 85,
                V = 86,
                W = 87,
                X = 88,
                Y = 89,
                Z = 90,

                Num0 = 48,
                Num1 = 49,
                Num2 = 50,
                Num3 = 51,
                Num4 = 52,
                Num5 = 53,
                Num6 = 54,
                Num7 = 55,
                Num8 = 56,
                Num9 = 57,

                F1 = 290,
                F2 = 291,
                F3 = 292,
                F4 = 293,
                F5 = 294,
                F6 = 295,
                F7 = 296,
                F8 = 297,
                F9 = 298,
                F10 = 299,
                F11 = 300,
                F12 = 301,
                F13 = 302,
                F14 = 303,
                F15 = 304,
                F16 = 305,
                F17 = 306,
                F18 = 307,
                F19 = 308,
                F20 = 309,
                F21 = 310,
                F22 = 311,
                F23 = 312,
                F24 = 313,
                F25 = 314,

                Keypad0 = 320,
                Keypad1 = 321,
                Keypad2 = 322,
                Keypad3 = 323,
                Keypad4 = 324,
                Keypad5 = 325,
                Keypad6 = 326,
                Keypad7 = 327,
                Keypad8 = 328,
                Keypad9 = 329,
                KeypadDecimal = 330,
                KeypadDivide = 331,
                KeypadMultiply = 332,
                KeypadSubtract = 333,
                KeypadAdd = 334,
                KeypadEnter = 335,
                KeypadEqual = 336,
                NumLock = 282,

                Space = 32,
                Apostrophe = 39,
                Comma = 44,
                Minus = 45,
                Period = 46,
                Slash = 47,
                
                Semicolon = 59,
                Equal = 61,

                LeftBracket = 91,
                Backslash = 92,
                RightBracket = 93,
                GraveAccent = 96,
                World1 = 161,
                World2 = 162,
                Escape = 256,
                Enter = 257,
                Tab = 258,
                Backspace = 259,
                Insert = 260,
                Delete = 261,
                Right = 262,
                Left = 263,
                Down = 264,
                Up = 265,
                PageUp = 266,
                PageDown = 267,
                Home = 268,
                End = 269,
                CapsLock = 280,
                ScrollLock = 281,
                
                PrintScreen = 283,
                Pause = 284,
                
                
                LeftShift = 340,
                LeftControl = 341,
                LeftAlt = 342,
                LeftSuper = 343,
                RightShift = 344,
                RightControl = 345,
                RightAlt = 346,
                RightSuper = 347,
                Menu = 348
            #elif defined(RE_WIN32_WINDOW)
                Unknown = -1,

                A = 'A',
                B = 'B',
                C = 'C',
                D = 'D',
                E = 'E',
                F = 'F',
                G = 'G',
                H = 'H',
                I = 'I',
                J = 'J',
                K = 'K',
                L = 'L',
                M = 'M',
                N = 'N',
                O = 'O',
                P = 'P',
                Q = 'Q',
                R = 'R',
                S = 'S',
                T = 'T',
                U = 'U',
                V = 'V',
                W = 'W',
                X = 'X',
                Y = 'Y',
                Z = 'Z',

                Num0 = '0',
                Num1 = '1',
                Num2 = '2',
                Num3 = '3',
                Num4 = '4',
                Num5 = '5',
                Num6 = '6',
                Num7 = '7',
                Num8 = '8',
                Num9 = '9',

                F1 = VK_F1,
                F2 = VK_F2,
                F3 = VK_F3,
                F4 = VK_F4,
                F5 = VK_F5,
                F6 = VK_F6,
                F7 = VK_F7,
                F8 = VK_F8,
                F9 = VK_F9,
                F10 = VK_F10,
                F11 = VK_F11,
                F12 = VK_F12,
                F13 = VK_F13,
                F14 = VK_F14,
                F15 = VK_F15,
                F16 = VK_F16,
                F17 = VK_F17,
                F18 = VK_F18,
                F19 = VK_F19,
                F20 = VK_F20,
                F21 = VK_F21,
                F22 = VK_F22,
                F23 = VK_F23,
                F24 = VK_F24,

                Keypad0 = VK_NUMPAD0,
                Keypad1 = VK_NUMPAD1,
                Keypad2 = VK_NUMPAD2,
                Keypad3 = VK_NUMPAD3,
                Keypad4 = VK_NUMPAD4,
                Keypad5 = VK_NUMPAD5,
                Keypad6 = VK_NUMPAD6,
                Keypad7 = VK_NUMPAD7,
                Keypad8 = VK_NUMPAD8,
                Keypad9 = VK_NUMPAD9,
                KeypadDecimal = VK_DECIMAL,
                KeypadDivide = VK_DIVIDE,
                KeypadMultiply = VK_MULTIPLY,
                KeypadSubtract = VK_SUBTRACT,
                KeypadAdd = VK_ADD,
                // KeypadEnter = 335,
                // KeypadEqual = 336,
                NumLock = VK_NUMLOCK,

                Space = VK_SPACE,
                Escape = VK_ESCAPE,
                Enter = VK_RETURN,
                Tab = VK_TAB,
                Backspace = VK_BACK,

                Apostrophe = VK_OEM_3,
                Comma = VK_OEM_COMMA,
                Minus = VK_OEM_MINUS,
                Period = VK_OEM_PERIOD,
                Slash = VK_OEM_2,
                Semicolon = VK_OEM_1,
                Equal = VK_OEM_PLUS,

                LeftBracket = VK_OEM_4,
                Backslash = VK_OEM_5,
                RightBracket = VK_OEM_6,
                // GraveAccent = 96,
                // World1 = 161,
                // World2 = 162,
                
                Insert = VK_INSERT,
                Delete = VK_DELETE,
                Right = VK_RIGHT,
                Left = VK_LEFT,
                Down = VK_DOWN,
                Up = VK_UP,
                PageUp = VK_PRIOR,
                PageDown = VK_NEXT,
                Home = VK_HOME,
                End = VK_END,
                CapsLock = VK_CAPITAL,
                ScrollLock = VK_NUMLOCK,
                
                PrintScreen = VK_SNAPSHOT,
                Pause = VK_PAUSE,

                LeftShift = VK_LSHIFT,
                LeftControl = VK_LCONTROL,
                LeftAlt = VK_LMENU,
                LeftSuper = VK_LWIN,
                RightShift = VK_RSHIFT,
                RightControl = VK_RCONTROL,
                RightAlt = VK_RMENU,
                RightSuper = VK_RWIN,                
                Menu = VK_MENU
            #endif
        };
    }
}
#pragma once
#include <Raccoon/Core/Logger.h>
#include <filesystem>

#ifdef RE_ENABLE_ASSERTS
    #define RE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) {if (!(check)) { RE##type##ERROR(msg, __VA_ARGS__); RE_DEBUGBREAK(); }}
    #define RE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define RE_INTERNAL_ASSERT_WITH_NO_MSG(type, check)  RE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
    
    #define RE_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define RE_ASSERT_GET_MACRO(...) RE_EXPAND_MACRO( RE_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RE_INTERNAL_ASSERT_WITH_MSG, RE_INTERNAL_ASSERT_WITH_NO_MSG) )

    #define RE_ASSERT(...) RE_EXPAND_MACRO( RE_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define RE_CORE_ASSERT(...) RE_EXPAND_MACRO( RE_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define RE_ASSERT(...)
    #define RE_CORE_ASSERT(...)
#endif
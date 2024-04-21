#pragma once 

#define BIT(x) (1 << x) 

#define RE_STRINGIFY_MACRO(macro) #macro

#define BIND_EVENT_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
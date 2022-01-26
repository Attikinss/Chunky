#pragma once

// Used for functions not belonging to a class
#define BIND_FUNCTION(func) std::bind(&##func, std::placeholders::_1)

// Used for class member functions
#define BIND_FUNCTION_SCOPED(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
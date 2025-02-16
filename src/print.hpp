/**
 * xyz: Collection of C++23 utilities
 * File: print.hpp - std::println like functions for C++23
 *
 * Repository: https://github.com/atomicptr/xyz
 * License:    MIT
 */
#pragma once

#include <format>
#include <iostream>

namespace xyz {
    template <class... Args>
    inline void print(std::format_string<Args...> fmt, Args&&... args) {
        print(std::cout, fmt, std::forward<Args>(args)...);
    }

    template <class... Args>
    inline void print(std::ostream& stream, std::format_string<Args...> fmt, Args&&... args) {
        stream << std::format(fmt, std::forward<Args>(args)...);
    }

    template <class... Args>
    inline void println(std::format_string<Args...> fmt, Args&&... args) {
        println(std::cout, fmt, std::forward<Args>(args)...);
    }

    template <class... Args>
    inline void println(std::ostream& stream, std::format_string<Args...> fmt, Args&&... args) {
        stream << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
}

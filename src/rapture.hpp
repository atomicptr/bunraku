#pragma once

#include <format>
#include <source_location>

#ifndef RAPTURE_PRINT_FUNC
    #include <print>
    #define RAPTURE_PRINT_FUNC(...) std::println(stderr, __VA_ARGS__)
#endif

#define rpt_assert(condition, ...)                                          \
    if (!(condition)) {                                                 \
        auto rapture_loc = std::source_location::current();             \
        RAPTURE_PRINT_FUNC("");                                         \
        RAPTURE_PRINT_FUNC(                                             \
            "========= ASSERTATION FAILED {}:{}:{} =========",          \
            rapture_loc.file_name(),                                    \
            rapture_loc.line(),                                         \
            rapture_loc.column()                                        \
        );                                                              \
        RAPTURE_PRINT_FUNC("\tAssert :\t{}", (#condition));             \
        RAPTURE_PRINT_FUNC("\tMessage:\t{}", std::format(__VA_ARGS__)); \
        RAPTURE_PRINT_FUNC("");                                         \
        std::abort();                                                   \
    }

#define rpt_expect(condition)                                       \
    if (!(condition)) {                                         \
        auto rapture_loc = std::source_location::current();     \
        RAPTURE_PRINT_FUNC("");                                 \
        RAPTURE_PRINT_FUNC(                                     \
            "========= EXPECTATION FAILED {}:{}:{} =========",  \
            rapture_loc.file_name(),                            \
            rapture_loc.line(),                                 \
            rapture_loc.column()                                \
        );                                                      \
        RAPTURE_PRINT_FUNC("\tExpectation:\t{}", (#condition)); \
        RAPTURE_PRINT_FUNC("");                                 \
        std::abort();                                           \
    }

#define rpt_panic(...)                                                                                                  \
    {                                                                                                               \
        auto rapture_loc = std::source_location::current();                                                         \
        RAPTURE_PRINT_FUNC(                                                                                         \
            "========= PANIC {}:{}:{} =========", rapture_loc.file_name(), rapture_loc.line(), rapture_loc.column() \
        );                                                                                                          \
        RAPTURE_PRINT_FUNC("\tMessage:\t{}", std::format(__VA_ARGS__));                                             \
        RAPTURE_PRINT_FUNC("");                                                                                     \
        std::abort();                                                                                               \
    }

#define rpt_unreachable()                                                                                       \
    {                                                                                                       \
        auto rapture_loc = std::source_location::current();                                                 \
        RAPTURE_PRINT_FUNC(                                                                                 \
                                                                                                            \
            "========= UNREACHABLE CODE {}:{}:{} =========",                                                \
            rapture_loc.file_name(),                                                                        \
            rapture_loc.line(),                                                                             \
            rapture_loc.column()                                                                            \
        );                                                                                                  \
        RAPTURE_PRINT_FUNC("\tMessage:\tThis point was marked as unreachable, but was reached regardless"); \
        RAPTURE_PRINT_FUNC("");                                                                             \
        std::abort();                                                                                       \
    }

#define rpt_unimplemented()                                                         \
    {                                                                           \
        auto rapture_loc = std::source_location::current();                     \
        RAPTURE_PRINT_FUNC(                                                     \
            "========= UNIMPLEMENTED CODE {}:{}:{} =========",                  \
            rapture_loc.file_name(),                                            \
            rapture_loc.line(),                                                 \
            rapture_loc.column()                                                \
        );                                                                      \
        RAPTURE_PRINT_FUNC("\tMessage:\tThis feature is not yet implemented."); \
        RAPTURE_PRINT_FUNC("");                                                 \
        std::abort();                                                           \
    }

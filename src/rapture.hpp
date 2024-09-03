#pragma once

#include <format>
#include <source_location>

#ifndef RAPTURE_PRINT_FUNC
    #include <print>
    #define RAPTURE_PRINT_FUNC(...) std::println(stderr, __VA_ARGS__)
#endif

#ifdef assert
    #ifndef RAPTURE_QUIET
        #warning "rapture: 'assert' is already defined and has been #undef'd"
    #endif
    #undef assert
#endif

#define assert(condition, ...)                                          \
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

#ifdef expect
    #ifndef RAPTURE_QUIET
        #warning "rapture: 'expect' is already defined and has been #undef'd"
    #endif
    #undef expect
#endif

#define expect(condition)                                       \
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

#ifdef panic
    #ifndef RAPTURE_QUIET
        #warning "rapture: 'panic' is already defined and has been #undef'd"
    #endif
    #undef panic
#endif

#define panic(...)                                                                                                  \
    {                                                                                                               \
        auto rapture_loc = std::source_location::current();                                                         \
        RAPTURE_PRINT_FUNC(                                                                                         \
            "========= PANIC {}:{}:{} =========", rapture_loc.file_name(), rapture_loc.line(), rapture_loc.column() \
        );                                                                                                          \
        RAPTURE_PRINT_FUNC("\tMessage:\t{}", std::format(__VA_ARGS__));                                             \
        RAPTURE_PRINT_FUNC("");                                                                                     \
        std::abort();                                                                                               \
    }

#ifdef unreachable
    #ifndef RAPTURE_QUIET
        #warning "rapture: 'unreachable' is already defined and has been #undef'd"
    #endif
    #undef unreachable
#endif

#define unreachable()                                                                                       \
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

#ifdef unimplemented
    #ifndef RAPTURE_QUIET
        #warning "rapture: 'unimplemented' is already defined and has been #undef'd"
    #endif
    #undef unimplemented
#endif

#define unimplemented()                                                         \
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

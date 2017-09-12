#pragma once

// TODO: PB_DEBUG define here
#define PB_DEBUG

#include <iostream>
#include <cassert>

namespace pb {
    namespace internal {

        template<typename T>
        void print_log(bool error, T t) {
            if (error) {
                std::cerr << t << std::endl;
            } else {
                std::cout << t << std::endl;
            }
        }

        template<typename T, typename... Args>
        void print_log(bool error, T t, Args... args) {
            if (error) {
                std::cerr << t << " ";
            } else {
                std::cout << t << " ";
            }
            print_log(error, args...);
        }

    }
}

#define PB_INFO(...)    pb::internal::print_log(false, "PB INFO     ",__VA_ARGS__)
#define PB_WARN(...)    pb::internal::print_log(false, "PB WARN     ",__VA_ARGS__)
#define PB_ERROR(...)   pb::internal::print_log(true,  "PB ERROR    ", __LINE__, __FILE__, __VA_ARGS__)
#define PB_FATAL(...)   pb::internal::print_log(true,  "PB FATAL    ", __LINE__, __FILE__, __VA_ARGS__); \
                        exit(-1);

#ifdef PB_DEBUG
#define PB_ASSERT(x) assert(x)
#define _PB_ASSERT(x, ...) {\
                                if (!x) {\
                                    PB_ERROR("***ASSERT***");\
                                    PB_ERROR("condition: <", #x, "> failed");\
                                    PB_ERROR("************");\
                                    exit(-2);\
                                }\
                                }
#else
#define PB_ASSERT(x)
    #define _PB_ASSERT(x, ...) { }
#endif
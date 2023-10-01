#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>

#include <sys/syscall.h>

namespace Common {
    /**
     * @brief Sets the affinity for the current thread to be pinned to the provided core_id.
     *
     * @param core_id The ID of the core to pin the thread to.
     * @return true if the affinity was set successfully, false otherwise.
     */
    inline auto setThreadCore(int core_id) noexcept {
        cpu_set_t cpuset;

        CPU_ZERO(&cpuset);
        CPU_SET(core_id, &cpuset);

        return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == 0);
    }

    /**
     * @brief Creates a thread instance, sets affinity on it, assigns it a name and
     * passes the function to be run on that thread as well as the arguments to the function.
     *
     * @tparam T The type of the function to be run on the thread.
     * @tparam A The types of the arguments to the function.
     * @param core_id The ID of the core to pin the thread to.
     * @param name The name of the thread.
     * @param func The function to be run on the thread.
     * @param args The arguments to the function.
     * @return A pointer to the created thread.
     */
    template<typename T, typename... A>
    inline auto createAndStartThread(int core_id, const std::string &name, T &&func, A &&... args) noexcept {
        auto t = new std::thread([&]() {
            if (core_id >= 0 && !setThreadCore(core_id)) {
                std::cerr << "Failed to set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;
                exit(EXIT_FAILURE);
            }
            std::cerr << "Set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;

            std::forward<T>(func)((std::forward<A>(args))...);
        });

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        return t;
    }
}

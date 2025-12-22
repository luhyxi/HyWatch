#include "watcher.hpp"
#include <exception>
#include <iostream>
#include <print>
#include <sys/inotify.h>

namespace hywatch {
    int Watcher::initNotify() {
        try {
            auto instance = inotify_init();
            if (instance == -1) {
                throw std::exception {};
            }
            std::println("inotify instance started sucessfully");
        } catch (const std::exception &e) {
            std::println(std::cerr, "exception was thrown {}", e.what());
            return -1;
        }
        return 0;
    }

    bool Watcher::setIsInitiated(bool value) { return m_IsInitiated = value; }
    bool Watcher::getIsInitiated() { return m_IsInitiated; }

}; // namespace hywatch

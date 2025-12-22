#pragma once

#include "event.hpp"
#include <cstddef>
#include <filesystem>
#include <queue>
#include <sys/inotify.h>
#include <sys/types.h>

// wrapper for the inotify extension in linux
namespace hywatch {

    class Watcher {
      public:
        Watcher() = default;
        ~Watcher() = default;
        Watcher(Watcher &&) = default;
        Watcher(const Watcher &) = default;
        Watcher &operator =(Watcher &&) = default;
        Watcher &operator =(const Watcher &) = default;
        int initNotify();
        void addWatch(int fileDescriptor, std::filesystem::path file, uint mask);
        std::queue<Event> getEventQueue();

      private:
        std::queue<Event> m_EventQueue {};
        bool m_IsInitiated {false};
        bool setIsInitiated(bool value);
        bool getIsInitiated();
    };
} // namespace hywatch

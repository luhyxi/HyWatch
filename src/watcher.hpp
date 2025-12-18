#pragma once

#include <filesystem>
#include <queue>
#include <sys/inotify.h>
#include "event.hpp"

// wrapper for the inotify extension in linux
namespace hywatch{

    class Watcher {
      public:
        Watcher();
        ~Watcher();
        Watcher(Watcher &&) = default;
        Watcher(const Watcher &) = default;
        Watcher &operator =(Watcher &&) = default;
        Watcher &operator =(const Watcher &) = default;
        void watchFile(std::filesystem::path file);

      private:
        std::queue<Event> m_EventQueue;
    };
} // namespace watcher

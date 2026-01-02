#pragma once

#include "event.hpp"
#include <cstddef>
#include <filesystem>
#include <limits.h>
#include <queue>
#include <sys/inotify.h>
#include <sys/types.h>

// wrapper for the inotify extension in linux
namespace hywatch {

    class Watcher {
      public:
        /* Might need to create a constructor inside the .cpp file */
        Watcher() : m_Buf(BUF_LEN) {};
        ~Watcher() = default;
        Watcher(Watcher &&) = default;
        Watcher(const Watcher &) = default;
        Watcher &operator =(Watcher &&) = default;
        Watcher &operator =(const Watcher &) = default;

        int initNotify();
        int addWatch(std::filesystem::path file, EventMask mask = EventMask::all);
        std::queue<Event> getEventQueue();

      private:
        static constexpr std::size_t BUF_LEN = 10 * (sizeof(struct inotify_event) + NAME_MAX + 1);

        std::vector<char> m_Buf;

        std::queue<Event> m_EventQueue {};
        int m_Fd {0};
        bool m_IsInitiated {false};

        bool setIsInitiated(bool value);
        bool getIsInitiated();
        int readEvents();
    };
} // namespace hywatch

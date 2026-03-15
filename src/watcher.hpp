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

    static constexpr std::size_t BUF_LEN = 10 * (sizeof(struct inotify_event) + NAME_MAX + 1);
    
    class Watcher {
      public:
        // constructors
        Watcher() : m_Buf(BUF_LEN) {};
        ~Watcher();
        Watcher(Watcher &&) = default;
        Watcher(const Watcher &) = default;
        Watcher &operator =(Watcher &&) = delete;
        Watcher &operator =(const Watcher &) = delete;

        // functions
        int initNotify();
        int addWatch(std::filesystem::path file, EventMask mask = EventMask::all);
        int readEvents();

        // members
        std::vector<char> m_Buf;
        std::queue<Event> m_EventQueue {};
        int m_Fd {0};
        bool m_IsInitiated {false};
    };
} // namespace hywatch

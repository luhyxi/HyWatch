#include "watcher.hpp"
#include "event.hpp"
#include <cstring>
#include <iostream>
#include <print>
#include <sys/inotify.h>
#include <unistd.h>

namespace hywatch {
    int Watcher::initNotify() {
        m_Fd = inotify_init();
        if (m_Fd == -1) {
            std::println(std::cerr, "inotify_init failed: {}", std::strerror(errno));
            return -1;
        }
        std::println("inotify instance started sucessfully");
        setIsInitiated(true);
        return 0;
    }

    bool Watcher::setIsInitiated(bool value) { return m_IsInitiated = value; }

    bool Watcher::getIsInitiated() { return m_IsInitiated; }

    int Watcher::addWatch(std::filesystem::path file, EventMask mask) {
        auto res = inotify_add_watch(m_Fd, file.c_str(), static_cast<uint>(mask));
        if (res == -1) {
            std::println(std::cerr, "inotify_add_watch failed {}", std::strerror(errno));
            return -1;
        }
        std::println("file added to inotify instance");

        return 0;
    }

    /* might be a good idea to make this async */
    int Watcher::readEvents() {
        do {
            auto numRead = read(m_Fd, m_Buf.data(), BUF_LEN);
            if (numRead == 0) {
                std::println(std::cerr, "read() from inotify instance failed {}", std::strerror(errno));
            }
            if (numRead == -1) {
                std::println(std::cerr, "read() error {}", std::strerror(errno));
                return -1;
            }

            for (auto p = m_Buf.data(); p < m_Buf.data() + numRead;) {
                auto *ie = reinterpret_cast<const inotify_event *>(p);

                Event e(*ie);
            }

        } while (true);
        return 0;
    };

}; // namespace hywatch

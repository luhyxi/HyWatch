#include "watcher.hpp"
#include "event.hpp"
#include <cstring>
#include <iostream>
#include <print>
#include <queue>
#include <sys/inotify.h>
#include <unistd.h>

namespace hywatch {

    Watcher::~Watcher() {
        if (m_Fd > 0) { close(m_Fd); }
    }

    int Watcher::initNotify() {
        m_Fd = inotify_init();
        if (m_Fd == -1) {
            std::println(std::cerr, "inotify_init failed: {}", std::strerror(errno));
            return -1;
        }
        std::println("inotify instance started sucessfully");
        m_IsInitiated = {true};
        return 0;
    }

    int Watcher::addWatch(std::filesystem::path file, EventMask mask) {
        auto res = inotify_add_watch(m_Fd, file.c_str(), static_cast<uint>(mask));
        if (res == -1) {
            std::println(std::cerr, "inotify_add_watch failed {}", std::strerror(errno));
            return -1;
        }
        std::println("file added to inotify instance");

        return 0;
    }

    void readEventsFromQueue(std::queue<Event> &queue) {
        while (!queue.empty()) {
            queue.front().printEvent();
            queue.pop();
        }
    }

    /* might be a good idea to make this async */
    int Watcher::readEvents() {
        do {
            auto numRead = read(m_Fd, m_Buf.data(), BUF_LEN);
            if (numRead == 0) {
                std::println(std::cerr, "read() from inotify instance failed {}", std::strerror(errno));
                return -1;
            }
            if (numRead == -1) {
                if (errno == EINTR) { continue; }
                std::println(std::cerr, "read() error {}", std::strerror(errno));
                return -1;
            }

            for (auto p = m_Buf.data(); p < m_Buf.data() + numRead;) {
                const inotify_event *ie = reinterpret_cast<const inotify_event *>(p);

                m_EventQueue.push(Event(*ie));
                p += sizeof(struct inotify_event) + ie->len;
            }
            readEventsFromQueue(m_EventQueue);
        } while (true);
    };
}; // namespace hywatch

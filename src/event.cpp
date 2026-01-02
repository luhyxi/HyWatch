#include "event.hpp"
#include <iostream>
#include <sys/inotify.h>

namespace hywatch {
    Event::Event(const inotify_event &e) :
        m_wd(e.wd),
        m_mask(static_cast<EventMask>(e.mask)) {
        m_timestamp = std::time(nullptr);
        if (e.len > 0) { m_path = e.name; }
    }

    void Event::printEvent() {
        std::cout << "[hywatch::Event]\n"
                  << "  Time : " << m_timestamp << '\n'
                  << "  WD   : " << m_wd << '\n'
                  << "  Path : " << m_path << '\n'
                  << "  Mask : " << static_cast<std::uint32_t>(m_mask) << '\n';
    }
} // namespace hywatch

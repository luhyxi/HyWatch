#include "event.hpp"
#include <sys/inotify.h>

namespace hywatch {
    Event::Event(const inotify_event& e)
        : m_wd(e.wd),
          m_mask(static_cast<EventMask>(e.mask))
    {
        if (e.len > 0) {
            m_path = e.name;
        }
    }

} // namespace hywatch

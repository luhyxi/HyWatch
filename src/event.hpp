#pragma once

#include <cstdint>
#include <filesystem>
#include <sys/inotify.h>

namespace fs = std::filesystem;

namespace hywatch {

    enum class EventEnum : std::uint32_t {
        access = IN_ACCESS,
        modify = IN_MODIFY,
        attrib = IN_ATTRIB,
        close_write = IN_CLOSE_WRITE,
        close_nowrite = IN_CLOSE_NOWRITE,
        close = IN_CLOSE,
        open = IN_OPEN,
        moved_from = IN_MOVED_FROM,
        moved_to = IN_MOVED_TO,
        move = IN_MOVE,
        create = IN_CREATE,
        idelete = IN_DELETE,
        delete_self = IN_DELETE_SELF,
        move_self = IN_MOVE_SELF
    };

    class Event {
      public:
        Event(int wd, uint32_t mask, std::string path)
            : m_wd {wd}, m_mask {(static_cast<EventEnum>(mask))},
              m_path {path} {}

        Event(Event &&) = default;
        Event(const Event &) = default;
        Event &operator =(Event &&) = default;
        Event &operator =(const Event &) = default;
        ~Event() = default;

      private:
        int m_wd {0};
        EventEnum m_mask {0};
        fs::path m_path {""};
    };

} // namespace hywatch

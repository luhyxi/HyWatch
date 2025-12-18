#pragma once

#include <sys/inotify.h>

namespace hywatch {

    enum class EventEnum : int {
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
        Event();
        Event(Event &&) = default;
        Event(const Event &) = default;
        Event &operator =(Event &&) = default;
        Event &operator =(const Event &) = default;
        ~Event();

      private:
    };

} // namespace hywatch



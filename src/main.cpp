#include "watcher.hpp"


int main (int argc, char *argv[]) {
    auto w = hywatch::Watcher {};
    auto init = w.initNotify();
    auto watche = w.addWatch("/proc/");
    auto red = w.readEvents();
    return 0;
}

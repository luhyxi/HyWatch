#include "watcher.hpp"


int main (int argc, char *argv[]) {
    auto w = hywatch::Watcher {};
    auto init = w.initNotify();
    return 0;
}

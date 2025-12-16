#include <Geode/Geode.hpp>
#include "fullscreen.hpp"

using namespace geode::prelude;

$execute {
    HWND hwnd = getGDWindow();
    if (hwnd) {
        setFullscreen(hwnd);
    }
}

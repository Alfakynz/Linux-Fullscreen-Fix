#include <Geode/Geode.hpp>
//#include <Geode/binding/GameManager.hpp>
#include "fullscreen.hpp"
#include <thread>
#include <chrono>

using namespace geode::prelude;

static bool lastFullscreenState = false;

bool isWindowFullscreen(HWND hwnd) {
    if (!hwnd) return false;

    RECT r;
    GetWindowRect(hwnd, &r);

    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi);

    // If window matches monitor size, it’s fullscreen
    return (r.left <= mi.rcMonitor.left &&
            r.top <= mi.rcMonitor.top &&
            r.right >= mi.rcMonitor.right &&
            r.bottom >= mi.rcMonitor.bottom);
}

/* Trying to find a way to work with the GD options
bool isWindowFullscreen() {
    return GameManager::sharedState() -> getGameVariable("0025");
}
*/


$execute {
    std::thread([]{
        while (true) {
            HWND hwnd = getGDWindow();
            if (!hwnd) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            // Detect if the user has toggled fullscreen in GD
            bool gdIsFullscreen = isWindowFullscreen(hwnd);

            // Sync mod fullscreen
            if (gdIsFullscreen != lastFullscreenState) {
                applyFullscreen(hwnd, gdIsFullscreen);
                lastFullscreenState = gdIsFullscreen;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }).detach();
}

#include <Geode/Geode.hpp>
#include <Geode/binding/GameManager.hpp>
#include "fullscreen.hpp"
#include <thread>
#include <chrono>

using namespace geode::prelude;

static bool lastFullscreenState = false;

bool isWindowFullscreen()
{
    return !GameManager::sharedState()->getGameVariable(GameVar::WindowedMode);
}

$execute
{
    std::thread([]
                {
        while (true) {
            HWND hwnd = getGDWindow();
            if (!hwnd) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            // Detect if the user has toggled fullscreen in GD
            bool gdIsFullscreen = isWindowFullscreen();

            // Sync mod fullscreen
            if (gdIsFullscreen != lastFullscreenState) {
                applyFullscreen(hwnd, gdIsFullscreen);
                lastFullscreenState = gdIsFullscreen;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        } })
        .detach();
}

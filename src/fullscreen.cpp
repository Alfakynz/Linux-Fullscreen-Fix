#include "fullscreen.hpp"

static bool isFullscreen = false;
static RECT oldRect;
static DWORD oldStyle;

HWND getGDWindow() {
    return FindWindowA(nullptr, "Geometry Dash");
}

void setFullscreen(HWND hwnd) {
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(
        MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY),
        &mi
    );

    SetWindowPos(
        hwnd,
        HWND_TOP,
        mi.rcMonitor.left,
        mi.rcMonitor.top,
        mi.rcMonitor.right - mi.rcMonitor.left,
        mi.rcMonitor.bottom - mi.rcMonitor.top,
        SWP_FRAMECHANGED | SWP_SHOWWINDOW
    );

    isFullscreen = true;
}

void toggleFullscreen(HWND hwnd) {
    if (!isFullscreen) {
        oldStyle = GetWindowLong(hwnd, GWL_STYLE);
        GetWindowRect(hwnd, &oldRect);
        setFullscreen(hwnd);
    } else {
        SetWindowLong(hwnd, GWL_STYLE, oldStyle);
        SetWindowPos(
            hwnd,
            nullptr,
            oldRect.left,
            oldRect.top,
            oldRect.right - oldRect.left,
            oldRect.bottom - oldRect.top,
            SWP_FRAMECHANGED | SWP_SHOWWINDOW
        );
        isFullscreen = false;
    }
}

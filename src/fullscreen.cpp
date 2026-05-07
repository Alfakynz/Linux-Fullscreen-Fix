#include "fullscreen.hpp"

static bool isFullscreen = false;
static RECT oldRect;
static DWORD oldStyle;

HWND getGDWindow()
{
    return FindWindowA(nullptr, "Geometry Dash");
}

void applyFullscreen(HWND hwnd, bool enable)
{
    if (!hwnd)
        return;

    if (enable && !isFullscreen)
    {
        // Save current window style and rect
        oldStyle = GetWindowLong(hwnd, GWL_STYLE);
        GetWindowRect(hwnd, &oldRect);

        // Set fullscreen style
        SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        SetWindowPos(
            hwnd,
            HWND_TOP,
            0,
            0,
            screenW,
            screenH,
            SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        isFullscreen = true;
    }
    else if (!enable && isFullscreen)
    {
        // Restore previous window style and rect
        SetWindowLong(hwnd, GWL_STYLE, oldStyle);
        SetWindowPos(
            hwnd,
            nullptr,
            oldRect.left,
            oldRect.top,
            oldRect.right - oldRect.left,
            oldRect.bottom - oldRect.top,
            SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        isFullscreen = false;
    }
}

#pragma once
#include <Windows.h>

// Get the Geometry Dash window handle
HWND getGDWindow();

// Apply or remove fullscreen
void applyFullscreen(HWND hwnd, bool enable);
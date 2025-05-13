#pragma once
#include <Windows.h>

// Function to be called when interacting with win32 menu elements
LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
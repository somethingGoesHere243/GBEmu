#include <Windows.h>
#include <iostream>

#include "GB.h"
#include "PPU/Menu.h"
#include "MenuHandler.h"

LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	// Retrieve Gameboy object
	GB* mainGB = (GB*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (msg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILE_OPEN:
			OPENFILENAMEW ofn;
			WCHAR fileName[260];
			HANDLE fileHandle;
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = fileName;
			// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
			// use the contents of szFile to initialize itself.
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(fileName);
			ofn.lpstrFilter = L"gb Files\0*.gb\0\0";
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			// Display the Open dialog box. 

			if (GetOpenFileNameW(&ofn) == TRUE) {
				// Convert WCHAR* into a string
				int size_needed = WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, nullptr, 0, nullptr, nullptr);
				std::string ROMFilePath(size_needed - 1, 0);
				WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, &ROMFilePath[0], size_needed, nullptr, nullptr);
				std::cout << ROMFilePath << std::endl;
				mainGB->loadROM(ROMFilePath);
			}

			PostQuitMessage(0);
			return 0;
		case ID_FILE_RESET:
			mainGB->reset();
			PostQuitMessage(0);
			return 0;
		case ID_RENDERSCALE_X1:
			mainGB->setRenderScale(1);
			PostQuitMessage(0);
			return 0;
		case ID_RENDERSCALE_X2:
			mainGB->setRenderScale(2);
			PostQuitMessage(0);
			return 0;
		case ID_RENDERSCALE_X4:
			mainGB->setRenderScale(4);
			PostQuitMessage(0);
			return 0;
		case ID_RENDERSCALE_X6:
			mainGB->setRenderScale(6);
			PostQuitMessage(0);
			return 0;
		}
	}

	// Call the original window procedure for default handling
	return CallWindowProc(mainGB->getWindProc(), hwnd, msg, wParam, lParam);
}
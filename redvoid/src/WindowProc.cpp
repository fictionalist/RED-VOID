#include "WindowProc.hpp"

/* WindowProc namespace:
	* replaces the game window's window procedure, allowing us to intercept Windows messages and
	  allow direct interaction between the player and the game by providing functions for select
	  key presses.
	* provides a mean to interact with a future user interface for the game
*/
#include <Definitions.hpp>
#include "Logger.hpp"
#include "GameState.hpp"
#include <Windows.h>

WNDPROC originalWindowProc = nullptr;

bool uiToggled = false;

LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_KEYDOWN: {
			switch (wParam) {
				case VK_F5: {
					GameState::save();
					break;
				}
				case VK_F6: {
					GameState::load();
				}
			}
			break;
		}
		case WM_MOVE:
		case WM_SIZE: {
			//UI::windowMoved();
			break;
		}
		default:
			return CallWindowProc(originalWindowProc, hWnd, msg, wParam, lParam);
	}
	return 0;
}

bool WindowProc::init() {
	HWND gameWindow = FindWindowA(WINDOW_NAME, NULL);
	if (!gameWindow) {
#ifdef _DEBUG
		Logger::log("Failed to get Game Window when trying to replace its WindowProc.");
#endif
		return false;
	}
	originalWindowProc = (WNDPROC)GetWindowLongPtr(gameWindow, GWLP_WNDPROC);
	SetWindowLong(gameWindow, GWL_WNDPROC, (LONG)windowProc);
	return true;
}
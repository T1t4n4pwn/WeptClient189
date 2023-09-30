#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>
#include <gl/GL.h>

typedef void (*GUI_CALL_BACK)();

struct Menu {
	static inline bool Open;
	static inline bool Initialized;

	static inline GUI_CALL_BACK CallBackFunc;

	static inline HWND HandleWindow;
	static inline HDC HandleDeviceContext;

	static inline HGLRC OriginalGLContext;
	static inline HGLRC MenuGLContext;

	static void SetupImgui();

	static void Hook_wndProc();
	static void Unhook_wndProc();
};
bool PlaceHookGL();


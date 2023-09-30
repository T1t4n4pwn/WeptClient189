
#include "OpenGlHK.h"
#include "TitanHook.h"
#include <filesystem>
#include <mutex>
#include <Shlobj.h>
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"

typedef bool(*template_wglSwapBuffers) (HDC hdc);
template_wglSwapBuffers original_wglSwapBuffers;
TitanHook<template_wglSwapBuffers> OPENGL_Hook;
std::once_flag setupFlag;
std::atomic_flag clipCursor = ATOMIC_FLAG_INIT;
RECT originalClip;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (Menu::Open && Menu::Initialized)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}

void Menu::Hook_wndProc()
{
	original_wndProc = (template_WndProc)SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)hook_WndProc);
}

void Menu::Unhook_wndProc()
{
	SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}
#include "bytes.hpp"


ImFont* if_tahoma;
ImFont* if_icons;

void Menu::SetupImgui()
{
	Menu::MenuGLContext = wglCreateContext(Menu::HandleDeviceContext);
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::MenuGLContext);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	//this->MyStyle();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//ImGui::GetStyle().WindowRounding = 4;

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] = {

		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;
	
	

	if_tahoma = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 14, &font_config, ranges);
	if_icons = io.Fonts->AddFontFromMemoryTTF(icons_binary, sizeof icons_binary, 15, &font_config, ranges);
	

	ImGui_ImplWin32_Init(Menu::HandleWindow);
	ImGui_ImplOpenGL2_Init();


	Menu::Initialized = true;
}
bool __stdcall hook_wglSwapBuffers(_In_ HDC hdc)
{
	Menu::HandleDeviceContext = hdc;
	Menu::HandleWindow = WindowFromDC(hdc);
	Menu::OriginalGLContext = wglGetCurrentContext();

	std::call_once(setupFlag, [&] {
		Menu::Hook_wndProc();
		Menu::SetupImgui();
		});
	glDepthFunc(GL_LEQUAL);



	wglMakeCurrent(Menu::HandleDeviceContext, Menu::MenuGLContext);
	//glDepthFunc(GL_LEQUAL);
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushFont(if_icons);
	ImGui::PushFont(if_tahoma);


	if (Menu::Open)
	{

		if (Menu::CallBackFunc) {
			Menu::CallBackFunc();
		}
		
	}
	else
	{
		// checking if originalClip is valid
		if (originalClip.right > originalClip.left && originalClip.bottom > originalClip.top)
		{
			ClipCursor(&originalClip);
			clipCursor.clear();
		}
	}

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	ImGui::PopFont();
	ImGui::PopFont();
	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	//return original_wglSwapBuffers(hdc); error!
	return OPENGL_Hook.GetOrignalFunc()(hdc);
}


bool PlaceHookGL() {
	LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	while (!wglSwapBuffers){
		wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	}
	original_wglSwapBuffers = (template_wglSwapBuffers)wglSwapBuffers;
	OPENGL_Hook.InitHook(original_wglSwapBuffers, hook_wglSwapBuffers);
	OPENGL_Hook.SetHook();
	return true;
}
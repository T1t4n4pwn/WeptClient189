#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"
#include <vector>
#include <d3d11.h>
#include <iostream>
#include <tchar.h>
#include <dwmapi.h>
#include <iostream>
//#include <atlstr.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dwmapi.lib")

/****************************************************
* Copyright (C): Liv
* @file		: OwnImGui.h
* @author	: Liv
* @email		: 1319923129@qq.com
* @version	: 1.0
* @date		: 2022/4/17	15:57
****************************************************/

// Datas
static ID3D11Device* g_pd3dDevice;
static ID3D11DeviceContext* g_pd3dDeviceContext;
static IDXGISwapChain* g_pSwapChain;
static ID3D11RenderTargetView* g_mainRenderTargetView;
typedef void(*CallBack)();
extern bool Clean;
extern WNDCLASSEX W_class;
extern std::string shitassname;
struct WindowData {
	HWND hWindow;		// 目标窗口句柄
	HWND hMyWindow;		// 绘制窗口句柄
	RECT WindowRect;	// 目标窗口数据
	char WindowName[256];
	char WindowClassName[256];
	int  Width, Height; // 目标窗口大小
};

class OwnImGui
{
private:
	// 初始化
	void Initialize();
	// 创建窗口
	bool CreateOwnWindow(HWND ToWindow);
	// 窗口消息循环
	void WindowMessageCycle(CallBack MainFunction);
	// 窗口回调
	static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// 初始字体大小
	size_t FontSize = 15;
	// 结束
	bool done = false;
public:
	OwnImGui(const char* MenuName_);
	OwnImGui() { strcpy_s(MenuName, 4, "Menu"); }
	~OwnImGui();
	// 菜单名字
	char MenuName[256]{};

	// 窗口信息
	WindowData Window;
	// 绘制主函数
	void Start(const char* WindowClassName, const char* WindowName, CallBack MainFunction);
	// 退出绘制
	void End() { done = true; }
	// 设置字体大小
	void ReSetFontSize(size_t FontSize_);
	// 个人主题(绘制前调用)
	void MyStyle();
	HWND GetSelfWindowHWND() {
		return this->Window.hMyWindow;
	}
	void SetUp();
	// 圆角选择框
	void CheckboxEx(const char* Text, bool* Point);
	// 计算文本绘制长度
	int  CalcTextWidth(const char* Text);
	// 文本
	void Text(const char* Text, ImVec2 Pos,int color,int fontsize);
	// 矩形
	void Rectangle(ImVec2 Pos, int width, int height, int color, int thickness);
	// 线
	void Line(ImVec2 From, ImVec2 To,int color,int thickness);
	// 圆
	void Circle(ImVec2 Center, float radius, int color, float thickness);
	// 填充圆
	void CircleFilled(ImVec2 Center, float radius, int color, int num = 360);
	// 填充矩形
	void RectangleFilled(ImVec2 Pos, int width, int height, int color);
	// 描边文本
	void StrokeText(const char* Text, ImVec2 Pos, int color_bg, int color);
	// 连接点
	void ConnectPoint(std::vector<ImVec2> Points, int color, float thickness);
	// 六边矩形
	void DrawHexagonFilledX(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col);

	void DrawQuadFilledX(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor col);
};
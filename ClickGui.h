#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"
#include "OpenGlHK.h"

class ClickGui : public IModule {
public:

	BoolValue* antiCapture = new BoolValue("AntiCapture(Apply when next opened)", false);


	ClickGui() : IModule("ClickGui", VK_INSERT, 0, Category::RENDER, true) {
		addValue(BoolType, antiCapture);
	}

	void onEnable() override {
		Menu::Open = true;
		//HWND sHwnd = gui.GetSelfWindowHWND();
		//SetWindowLong(sHwnd, GWL_EXSTYLE, WS_EX_LAYERED);

		//if (antiCapture->getValue()) {
		//	SetWindowDisplayAffinity(sHwnd, WDA_EXCLUDEFROMCAPTURE);
		//}
		//else {
		//	SetWindowDisplayAffinity(sHwnd, WDA_NONE);
		//}

	}

	void onUpdate() override {
		
		

	}

	void onDisable() override {
		Menu::Open = false;
		//HWND sHwnd = gui.GetSelfWindowHWND();
		//SetWindowLong(sHwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST);

		//if (antiCapture->getValue()) {
		//	SetWindowDisplayAffinity(sHwnd, WDA_EXCLUDEFROMCAPTURE);
		//}
		//else {
		//	SetWindowDisplayAffinity(sHwnd, WDA_NONE);
		//}
	}


};
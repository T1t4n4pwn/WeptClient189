#pragma once
#pragma once
#include <Windows.h>
#include "ModuleManager.h"

class KeyBoard {
public:

	static void StartListen()
	{
		while (true)
		{
			ModuleManager* mgr = ModuleManager::getInstance();
			for (size_t i = 0; i < mgr->getNumberOfModule(); i++)
			{
				IModule* crtMod = mgr->getModuleByIndex(i);
				if (crtMod == nullptr)
				{
					continue;
				}

				if (crtMod->getKey() == 0)
					continue;

				if (IsKeyPressed(crtMod->getKey()))
				{
					crtMod->setEnable(!crtMod->isEnable());
				}
			}
			Sleep(100);
		}
	}

	static bool IsKeyPressed(int key)
	{
		return (GetAsyncKeyState(key) & 1);
	}
	static bool IsKeyHold(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000);
	}
};

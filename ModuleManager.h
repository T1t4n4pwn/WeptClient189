#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Module.h"

class ModuleManager {
	std::vector<IModule*> modules;
	std::vector<HANDLE> handles;

	ModuleManager() {

	}


	~ModuleManager() {

	}
public:

	static ModuleManager*getInstance()
	{
		static auto* inst = new ModuleManager();
		return inst;
	}

	void addModule(IModule* mod)
	{
		modules.push_back(mod);
	}

	void invokeAll()
	{
		if (modules.size() == 0)
			return;

		//for (size_t i = 0; i < modules.size(); i++)
		//{
		//	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&IModule::threadEntry, modules[i], 0, NULL);
		//	handles.push_back(handle);
		//}
		while (1) {

			for (IModule* mod : modules)
			{
				mod->threadEntry(mod);
			}
			
		}


		//WaitForMultipleObjects(handles.size(), &handles[0], TRUE, INFINITE);

		Clear();
	}

	IModule* getModuleByName(const std::string name)
	{
		for (size_t i = 0; i < modules.size(); i++)
		{
			std::string crtName = modules[i]->getName();
			if (crtName.compare(name) == 0)
				return modules[i];
		}
		return nullptr;
	}

	IModule* getModuleByIndex(const int idx)
	{
		if ((modules.size() >= idx) && (idx >= 0))
		{
			return modules[idx];
		}
		return nullptr;
	}

	std::vector<IModule*> getModulesByCategory(Category cate) {
		std::vector<IModule*> result;
		for (int i = 0; i < modules.size(); i++) {
			IModule* mod = modules[i];
			if (mod == nullptr) {
				continue;
			}

			if (mod->getCategory() == cate) {
				result.push_back(mod);
			}

		}
		return result;
	}

	int getNumberOfModule() const
	{
		return modules.size();
	}

	void Clear()
	{
		for (HANDLE h : handles)
		{
			CloseHandle(h);
		}
		handles.clear();
		modules.clear();
	}



};
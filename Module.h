#pragma once
#include <iostream>
#include <Windows.h>
#include "Value.h"
#include <vector>
#include <map>

enum class Category {
	COMBAT,
	MOVEMENT,
	RENDER,
	WORLD,
	MISC
};


class IModule {
protected:
	std::string name;
	uint32_t key;
	uint32_t sleep_time;
	Category category;
	std::vector<std::pair<ValueType,Value*>> values;
private:
	bool isFrist;

public:

	bool enable;

	IModule(std::string name, uint32_t key, uint32_t sleep_time, Category cate, bool auto_enable = false) : name(name), key(key), sleep_time(sleep_time) {
		isFrist = true;
		enable = auto_enable;
		category = cate;
	}

	void addValue(ValueType type,Value* value)
	{
		values.push_back(std::pair<ValueType, Value*>(type, value));
	}

	std::vector<std::pair<ValueType, Value*>> getValues() {
		return values;
	}

	Value* getValueObjByName(const std::string& name) {
		for (int i = 0; i < values.size(); i++)
		{
			Value* crtObj = values[i].second;
			if (name.compare(crtObj->getName()) == 0)
			{
				return crtObj;
			}
		}
	}

	virtual void onEnable() {
		std::cout << "[" << "TitanAwaken" << "]" << ": " << getName() << " has enabled!" << std::endl;
	};
	virtual void onUpdate() = 0;

	virtual void onRender() {}

	virtual void onDisable() {
		std::cout << "[" << "TitanAwaken" << "]" << ": " << getName() << " has disabled!" << std::endl;
	};

	//static void threadEntry(void* arg)
	//{
	//	IModule* mod = (IModule*)arg;
	//	if (mod == nullptr)
	//		return;

	//	while (true)
	//	{
	//		if (mod->isEnable())
	//		{
	//			if (mod->isFrist)
	//			{
	//				mod->onEnable();
	//				mod->isFrist = false;
	//			}

	//			mod->onUpdate();

	//			if (mod->sleep_time)
	//			{
	//				Sleep(mod->sleep_time);
	//			}

	//		}
	//		else {
	//			if (!mod->isFrist)
	//			{
	//				mod->onDisable();
	//				mod->isFrist = true;
	//			}
	//			Sleep(1);
	//		}
	//	}
	//}

	static void threadEntry(void* arg)
	{
		IModule* mod = (IModule*)arg;
		if (mod == nullptr)
			return;

		if (mod->isEnable())
		{
			if (mod->isFrist)
			{
				mod->onEnable();
				mod->isFrist = false;
			}

			mod->onUpdate();

			if (mod->sleep_time)
			{
				Sleep(mod->sleep_time);
			}

		}
		else {
			if (!mod->isFrist)
			{
				mod->onDisable();
				mod->isFrist = true;
			}
			Sleep(1);
		}
		
	}

	bool isEnable() const {
		return enable;
	}

	std::string getName() const {
		return name;
	}

	uint32_t getKey() const {
		return key;
	}

	Category getCategory() {
		return category;
	}

	void setEnable(bool status) {
		enable = status;
	}



	virtual ~IModule() {}
};
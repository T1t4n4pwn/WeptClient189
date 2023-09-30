#pragma once

#include <iostream>
#include <map>

#include "globals.h"
#include "utils.h"

class ForgeCache {
public:

	void InitCache();

	jclass FindClassCache(const std::string& key);

	jmethodID FindMethodCache(const std::string& key);

	jfieldID FindFieldCache(const std::string& key);

private:
	void InitForge();
	void InitVanilla();
	void InitLunar();
	void setupClassLoader();
	jclass FindClassByClassLoader(const char* name);

private:
	std::map<std::string, jclass> classCache;
	std::map<std::string, jmethodID> methodCache;
	std::map<std::string, jfieldID> fieldCache;

	jobject class_loader_obj = 0;
	jmethodID method_find_class = 0;
};

extern ForgeCache forgeCache;
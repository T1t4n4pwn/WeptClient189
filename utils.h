#pragma once
#include "globals.h"

inline jclass LaunchWrapperClassLoaderClass;
inline jmethodID FindClassMethodID;
inline jclass LaunchClass;
inline jfieldID ClassLoaderFieldID;
inline jobject ClassLoaderObject;

struct WindowInfo {
	int TargetPID;
	std::string Caption;
	std::string ClassName;
};

jclass ForgeFindClass(const char* name);

WindowInfo GetWindowInfoByPID(const int pid);
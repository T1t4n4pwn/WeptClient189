#pragma once
#include <iostream>
#include <jni.h>
#include <jvmti.h>

extern std::atomic_bool hasInitialize;
extern JNIEnv* g_env;
extern JavaVM* g_vm;
extern jvmtiEnv* g_jvmtiEnv;


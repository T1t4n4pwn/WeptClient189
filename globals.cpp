#include "globals.h"

std::atomic_bool hasInitialize = false;
JNIEnv* g_env = nullptr;
JavaVM* g_vm = nullptr;
jvmtiEnv* g_jvmtiEnv = nullptr;

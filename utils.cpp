#include "utils.h"
#include <Windows.h>
#include <VMProtectSDK.h>
jclass ForgeFindClass(const char* name)
{
    VMProtectBegin("ForgeFindClass");

    if (LaunchWrapperClassLoaderClass == NULL)
    {
        LaunchWrapperClassLoaderClass = g_env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
        if (LaunchWrapperClassLoaderClass == NULL) return NULL;
    }

    if (FindClassMethodID == NULL)
    {
        FindClassMethodID = g_env->GetMethodID(LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        if (FindClassMethodID == NULL) return NULL;
    }

    if (LaunchClass == NULL)
    {
        LaunchClass = g_env->FindClass("net/minecraft/launchwrapper/Launch");
        if (LaunchClass == NULL) return NULL;
    }

    if (ClassLoaderFieldID == NULL)
    {
        ClassLoaderFieldID = g_env->GetStaticFieldID(LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
        if (ClassLoaderFieldID == NULL) return NULL;
    }

    if (ClassLoaderObject == NULL)
    {
        ClassLoaderObject = g_env->GetStaticObjectField(LaunchClass, ClassLoaderFieldID);
        if (ClassLoaderObject == NULL) return NULL;
    }

    jstring jname = g_env->NewStringUTF(name);
    jclass cls = (jclass)g_env->CallObjectMethod(ClassLoaderObject, FindClassMethodID, jname);

    g_env->DeleteLocalRef(jname);

    VMProtectEnd();

    return cls;
}

BOOL CALLBACK WindowEnumCB(HWND hwnd, LPARAM params) {
    
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    WindowInfo* info = (WindowInfo*)params;

    if (info->TargetPID == pid) {
        
        char captionBuffer[255]{ 0 };
        char classNameBuffer[255]{ 0 };

        GetWindowTextA(hwnd, captionBuffer, sizeof(captionBuffer));

        GetClassNameA(hwnd, classNameBuffer, sizeof(classNameBuffer));
        if (strcmp(classNameBuffer, "LWJGL") != 0) {
            return TRUE;
        }

        info->Caption = std::string(captionBuffer);
        info->ClassName = std::string(classNameBuffer);

        return FALSE;
    }

    return TRUE;
}

WindowInfo GetWindowInfoByPID(const int pid)
{
    WindowInfo info{ 0 };
    info.TargetPID = pid;
    EnumWindows(WindowEnumCB, (LPARAM) &info);

    return info;
}

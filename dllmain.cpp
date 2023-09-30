#include <iostream>
#include <windows.h>

#include <jni.h>
#include <VMProtectSDK.h>
#include "globals.h"
#include "TitanHook.h"
#include "Main.h"

typedef jlong(*PFUNC_Java_org_lwjgl_opencl_CL12_nclReleaseDevice)(JNIEnv* env, jclass klass, jobject obj, int* ptr);

TitanHook<PFUNC_Java_org_lwjgl_opencl_CL12_nclReleaseDevice> LWJGL_Hook;
PFUNC_Java_org_lwjgl_opencl_CL12_nclReleaseDevice LWJGL_ReleaseDevice;

jlong Java_org_lwjgl_opencl_CL12_nclReleaseDevice_Hook(JNIEnv* env, jclass klass, jobject var, int* ptr) {


    if (env != nullptr && g_env == nullptr && !hasInitialize) {

        jint ret = env->GetJavaVM(&g_vm);

        if (ret != JNI_OK) {
            MessageBoxA(0, "Get JavaVM Failed!", "TModLoader Error", 0);
        }

        ret = g_vm->GetEnv((void**)&g_jvmtiEnv, JVMTI_VERSION_1_2);
        if (ret != JNI_OK) {
            MessageBoxA(0, "Get JVMTI Env Failed!", "TModLoader Error", 0);
        }

        hasInitialize = true;
        LWJGL_Hook.RemoveHook();
    }

    return LWJGL_Hook.GetOrignalFunc()(env, klass, var, ptr);
}

__forceinline void Panic() {
    CONTEXT context;

    context.ContextFlags = 1;

    GetThreadContext((HANDLE)-2, &context);

    context.Rip = context.Rax;
    context.Rsp = context.Dr0;
    context.Rbp = context.Rbx;

    SetThreadContext((HANDLE)-2, &context);

    Sleep(1000);

    int* p = (int*)0xDEADC0DE;
    *p = 0xDEADC0DE;
}

#include <fstream>
#include <filesystem>
#include <sstream>
#include "HWIDHelper.h"
namespace fs = std::filesystem;

std::string ReadFileAsString(const std::string& filePath) {

    std::ifstream file(filePath);
    std::stringstream buffer;

    if (file.is_open()) { // 检查文件是否成功打开
        buffer << file.rdbuf(); // 将文件内容写入缓冲区
        file.close(); // 关闭文件
    }
    else {
        return std::string();
    }

    return buffer.str(); // 将缓冲区转换为字符串并返回

}

bool WriteStringAsFile(const std::string& filePath, const std::string& text) {
    
    std::ofstream out(filePath, std::ios_base::out);

    if (!out.is_open()) {
        return false;
    }

    out.write(text.c_str(), text.size());
    out.flush();
    out.close();

    return true;
}

#include "ini.h"
#include "Wetp.h"

#define CARD_LOCATION "C:\\Users\\Public\\Documents\\WeptClient.ini"

void LoginVerify() {

    VMProtectBegin("LoginVerify");
    std::string card;
    std::string hwid;

    if (fs::exists(CARD_LOCATION)) {

            mINI::INIFile file(CARD_LOCATION);
            mINI::INIStructure ini;
            if (!file.read(ini)) {
                    std::cout << "账号读取失败" << std::endl;
                    Panic();
                    return;
            }

            std::string username = ini["account"]["username"];
            std::string password = ini["account"]["password"];

            std::string err_msg;

            Wept wept;

            if (!wept.login_account(username, password, err_msg)) {
                    std::cout << err_msg << std::endl;
                    Panic();
                    return;
            }

            std::cout << "登录成功" << std::endl;

            if (!wept.check_user_permission(err_msg)) {
                    std::cout << err_msg << std::endl;
                    Panic();
                    return;
            }
            else {
                    std::cout << "权限检查成功" << std::endl;
                    return;
            }

    }
    else {
            std::cout << "未找到已保存的账号密码" << std::endl;
            Panic();
            ExitProcess(0);
    }

    VMProtectEnd();

}

DWORD WINAPI StartHack(LPVOID args) {

    LoginVerify();

    VMProtectBegin("StartHack");

    if (!GetModuleHandle("lwjgl64.dll")) {
        while (!GetModuleHandle("lwjgl64.dll")) Sleep(100);
    }

    LWJGL_ReleaseDevice = (PFUNC_Java_org_lwjgl_opencl_CL12_nclReleaseDevice)GetProcAddress(GetModuleHandle("lwjgl64.dll"), "Java_org_lwjgl_opencl_CL12_nclReleaseDevice");

    if (LWJGL_ReleaseDevice == nullptr) {
        MessageBoxA(0, "获取失败", "", 0);
        return -1;
    }

    LWJGL_Hook.InitHook(LWJGL_ReleaseDevice, Java_org_lwjgl_opencl_CL12_nclReleaseDevice_Hook);
    LWJGL_Hook.SetHook();

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackMain, 0, 0, 0);

    VMProtectEnd();
    return 0;
}

#include "XHideDll.h"
#include "XAntiDebug/XAntiDebug.h"
#include <atomic>

XAD_STATUS		status;
XAntiDebug		antiDbg(GetModuleHandle(NULL), /*FLAG_FULLON*/FLAG_DETECT_DEBUGGER | FLAG_DETECT_HARDWAREBREAKPOINT);

std::atomic_bool isFuck = 0;

DWORD WINAPI CheckThread(LPVOID args) {

    for (;;)
    {
        if (antiDbg.XAD_ExecuteDetect()) {
            isFuck = true;
        }
        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI FuckThread(LPVOID args){

    VMProtectBegin("FuckThread");

    if (isFuck == true) {
        Panic();
    }

    Sleep(1000);

    VMProtectEnd();

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        antiDbg.XAD_Initialize();

        //XHideDll::HideInLoadOrderLinks(hModule);
        //XHideDll::HideInMemoryOrderLinks(hModule);
        //XHideDll::HideInInitializationOrderLinks(hModule); 

        FreeConsole();
        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);

        CreateThread(NULL, 0, StartHack, 0, 0, 0);
        
        //CreateRemoteThreadEx(INVALID_HANDLE_VALUE, NULL, 0, CheckThread, 0, 0, 0, 0);
        //CreateRemoteThreadEx(INVALID_HANDLE_VALUE, NULL, 0, FuckThread, 0, 0, 0, 0);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


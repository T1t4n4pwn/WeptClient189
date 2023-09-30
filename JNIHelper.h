#pragma once
#include "globals.h"
#include <Windows.h>
#include <codecvt>

class JNIHelper {
public:


    static std::string JString2String(JNIEnv* env, jstring string) {
        int length = env->GetStringLength(string);
        const jchar* jcstr = env->GetStringChars(string, NULL);

        if (jcstr == NULL) {
            return NULL;
        }

        char* rtn = (char*)malloc(sizeof(char) * (2 * length + 1));
        memset(rtn, 0, sizeof(char) * (2 * length + 1));
        int size = 0;
        size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jcstr, length, rtn, sizeof(char) * (2 * length + 1), NULL, NULL);
        std::string ret(rtn);
        delete[] rtn;
        return ret;
    }

    static void printStackTrace(JNIEnv* jniEnv)
    {

        jthrowable exception = jniEnv->ExceptionOccurred();
        jniEnv->ExceptionClear();

        jclass throwableCls = jniEnv->FindClass("java/lang/Throwable");

        jmethodID printStackTrace = jniEnv->GetMethodID(throwableCls, "printStackTrace", "()V");

        jniEnv->CallVoidMethod(exception, printStackTrace);

    }

};
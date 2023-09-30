#pragma once
#include <iostream>
#include "ForgeCache.h"
#include "Object.h"
#include "JNIHelper.h"

class KeyBinding : Object {
public:
    using Object::Object;

    static void setKeyBindState(int keyCode, bool pressed) {
    
        jmethodID methodID = forgeCache.FindMethodCache("KeyBinding::setKeyBindState");

        if (methodID == 0) {
            return;
        }

        g_env->CallStaticVoidMethod(forgeCache.FindClassCache("net/minecraft/client/settings/KeyBinding"), methodID, keyCode, pressed);
        if (g_env->ExceptionOccurred()) {
            std::cout << "KeyBinding::setKeyBindState Exception: " << std::endl;
            g_env->ExceptionDescribe();
            return;
        }
    }

    static void onTick(int keyCode) {

        jmethodID methodID = forgeCache.FindMethodCache("KeyBinding::onTick");
        if (methodID == 0) {
            return;
        }

        g_env->CallStaticVoidMethod(forgeCache.FindClassCache("net/minecraft/client/settings/KeyBinding"), methodID, keyCode);

    }

    int getKeyCode() {
        
        jmethodID methodID = forgeCache.FindMethodCache("KeyBinding::getKeyCode");
        if (methodID == 0) {
            return 0;
        }

        int value = g_env->CallIntMethod(m_instance, methodID);
        
        return value;
    }

    bool isKeyDown() {

        jmethodID methodID = forgeCache.FindMethodCache("KeyBinding::isKeyDown");
        if (methodID == 0) {
            return 0;
        }

        bool value = g_env->CallBooleanMethod(m_instance, methodID);

        return value;
    }

};
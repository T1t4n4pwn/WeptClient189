#pragma once
#include "Object.h"
#include "KeyBinding.h"
#include "ForgeCache.h"

class GameSettings : Object {
public:
    using Object::Object;


    KeyBinding getKeyBindAttack() {
        
        jfieldID fieldID = forgeCache.FindFieldCache("GameSettings::keyBindAttack");
        if (fieldID == 0) {
            return KeyBinding(0);
        }

        jobject obj = g_env->GetObjectField(m_instance, fieldID);

        return KeyBinding(obj);
    }

    KeyBinding getKeyBindUseItem() {

        jfieldID fieldID = forgeCache.FindFieldCache("GameSettings::keyBindUseItem");
        if (fieldID == 0) {
            return KeyBinding(0);
        }

        jobject obj = g_env->GetObjectField(m_instance, fieldID);

        return KeyBinding(obj);
    }

};
#pragma once

#include "Object.h"
#include "EnumFacing.h"
#include "Entity.h"
#include "BlockPos.h"
#include "JNIHelper.h"

class MovingObjectPosition : public Object {
public:
	using Object::Object;

    std::string getTypeOfHit() {
        /*
            public static enum Type
            {
                MISS,
                BLOCK,
                ENTITY;
            }
        */
        jfieldID fieldID = forgeCache.FindFieldCache("MovingObjectPosition::typeOfHit");
        if (fieldID == 0) {
            return std::string("MISS");
        }

        jobject obj = g_env->GetObjectField(m_instance, fieldID);
        if (obj == 0) {
            return std::string("MISS");
        }

        jmethodID methodID = forgeCache.FindMethodCache("Enum::toString");
        if (methodID == 0) {
            return std::string("MISS");
        }

        jstring strEnum = (jstring)g_env->CallObjectMethod(obj, methodID);


        return JNIHelper::JString2String(g_env, strEnum);
    }

    EnumFacing getSideOfHit() {
        
        jfieldID fieldID = forgeCache.FindFieldCache("MovingObjectPosition::sideHit");
        if (fieldID == 0) {
            return EnumFacing(0);
        }

        jobject obj = g_env->GetObjectField(m_instance, fieldID);

        return obj;
    }

    Entity getEntityHit() {
        
        jfieldID fieldID = forgeCache.FindFieldCache("MovingObjectPosition::entityHit");
        if (fieldID == 0) {
            return Entity(0);
        }

        jobject obj = g_env->GetObjectField(m_instance, fieldID);

        return Entity(obj);
    }

    BlockPos getBlockPos() {
        
        jmethodID methodID = forgeCache.FindMethodCache("MovingObjectPosition::getBlockPos");
        if (methodID == 0) {
            return BlockPos(0);
        }

        jobject obj = g_env->CallObjectMethod(m_instance, methodID);

        return obj;
    }

};
#pragma once
#include "globals.h"
#include "EntityLivingBase.h"
#include "JNIHelper.h"
#include "IChatComponent.h"
#include "ItemStack.h"

class EntityPlayer : public EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;

	std::string getName() const {
		
		jmethodID getNameMethod = forgeCache.FindMethodCache("EntityPlayer::getName");
		if (getNameMethod == 0) {
			return std::string();
		}

		jstring nameStr = (jstring)g_env->CallObjectMethod(m_instance, getNameMethod);
		if (nameStr == 0) {
			return std::string();
		}
		return JNIHelper::JString2String(g_env, nameStr);
	}

	float getEyeHeight() const {
		
		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayer::getEyeHeight");
		if (methodID == 0) {
			return 0;
		}

		float eyeHeight = g_env->CallFloatMethod(m_instance, methodID);

		return eyeHeight;
	}

	bool isPlayerSleeping() {
		
		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayer::isPlayerSleeping");
		if (methodID == 0) {
			return false;
		}

		bool value = g_env->CallBooleanMethod(m_instance, methodID);

		return value;
	}

	IChatComponent getDisplayName() {
		
		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayer::getDisplayName");
		if (methodID == 0) {
			return IChatComponent(0);
		}

		jobject obj = g_env->CallObjectMethod(m_instance, methodID);

		return IChatComponent(obj);
	}

	ItemStack getHeldItem() {

		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayer::getHeldItem");
		if (methodID == 0) {
			return ItemStack(0);
		}

		jobject obj = g_env->CallObjectMethod(m_instance, methodID);

		return ItemStack(obj);
	}

};
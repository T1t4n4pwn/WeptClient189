#pragma once
#include "Object.h"
#include "ForgeCache.h"
#include "JNIHelper.h"

class IChatComponent : public Object {
public:
	using Object::Object;

	std::string getFormattedText() {
		
		jmethodID methodID = forgeCache.FindMethodCache("ITextComponent::getFormattedText");
		if (methodID == 0) {
			return std::string();
		}

		jstring jName = (jstring)g_env->CallObjectMethod(m_instance, methodID);

		return JNIHelper::JString2String(g_env, jName);
	}

};
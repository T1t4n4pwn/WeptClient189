#pragma once
#include "globals.h"
#include "AbstractClientPlayer.h"

class EntityPlayerSP : public AbstractClientPlayer {
public:
	using AbstractClientPlayer::AbstractClientPlayer;

	void setSprinting(bool sprinting) {

		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayerSP::setSprinting");
		if (methodID == nullptr) {
			std::cout << "setSprinting is NULL" << std::endl;
			return;
		}

		if (g_env->ExceptionCheck()) {
			g_env->ExceptionDescribe();
			return;
		}

		g_env->CallVoidMethod(m_instance, methodID, sprinting);
	}

	void swingItem() {
		
		jmethodID methodID = forgeCache.FindMethodCache("EntityPlayerSP::swingItem");
		if (methodID == nullptr) {
			return;
		}

		g_env->CallVoidMethod(m_instance, methodID);

	}

};
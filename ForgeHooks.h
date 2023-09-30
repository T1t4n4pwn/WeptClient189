#pragma once

#include "Object.h"
#include "EntityPlayer.h"

class ForgeHooks : public Object {
public:
	using Object::Object;

	static void onEmptyLeftClick(EntityPlayer player) {
		
		jmethodID methodID = forgeCache.FindMethodCache("ForgeHooks::onEmptyLeftClick"); //
		if (methodID == 0) {
			return;
		}

		g_env->CallStaticVoidMethod(forgeCache.FindClassCache("net/minecraftforge/common/ForgeHooks"), methodID, player);
	}

};
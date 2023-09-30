#pragma once
#include "Object.h"
#include "ForgeCache.h"

class Mouse : public Object {
public:
	using Object::Object;

	static bool isButtonDown(int key) {
		
		jmethodID methodID = forgeCache.FindMethodCache("Mouse::isButtonDown");
		if (methodID == 0) {
			return 0;
		}

		bool value = g_env->CallStaticBooleanMethod(forgeCache.FindClassCache("org/lwjgl/input/Mouse"), methodID);

		return value;
	}


};
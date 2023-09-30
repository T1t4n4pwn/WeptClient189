#pragma once
#include "Object.h"
#include "ForgeCache.h"

class Timer : public Object {
public:
	using Object::Object;
	float getRenderPartialTicks() {
		jfieldID fieldID = forgeCache.FindFieldCache("Timer::renderPartialTicks");
		if (fieldID == 0) {
			return 0;
		}

		float value = g_env->GetFloatField(m_instance, fieldID);

		return value;
	}

};
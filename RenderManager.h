#pragma once
#include "Object.h"
#include "ForgeCache.h"

class RenderManager : public Object {
public:
	using Object::Object;

	double getRenderPosX() {
	
		jfieldID fieldID = forgeCache.FindFieldCache("RenderManager::renderPosX");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getRenderPosY() {

		jfieldID fieldID = forgeCache.FindFieldCache("RenderManager::renderPosY");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getRenderPosZ() {

		jfieldID fieldID = forgeCache.FindFieldCache("RenderManager::renderPosZ");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

};
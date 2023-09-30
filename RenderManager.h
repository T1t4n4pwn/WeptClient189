#pragma once
#include "Object.h"
#include "ForgeCache.h"

class RenderManager : public Object {
public:
	using Object::Object;
	Vector3 getRenderPos()
	{
		return Vector3{
			(float)(double)g_env->GetDoubleField(this->obj(), forgeCache.FindFieldCache("RenderManager::renderPosX")),
			(float)(double)g_env->GetDoubleField(this->obj(), forgeCache.FindFieldCache("RenderManager::renderPosY")),
			(float)(double)g_env->GetDoubleField(this->obj(), forgeCache.FindFieldCache("RenderManager::renderPosZ"))
		};
	}

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
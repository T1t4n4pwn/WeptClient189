#pragma once
#include "globals.h"
#include "Entity.h"

#include "ForgeCache.h"

class EntityLivingBase : public Entity {
public:
	using Entity::Entity;

	bool canEntityBeSeen(jobject entity)
	{
		return g_env->CallBooleanMethod(this->obj(), forgeCache.FindMethodCache("EntityLivingBase::canEntityBeSeen"), entity);
	}
	float getHealth() const {
		
		jmethodID methodID = forgeCache.FindMethodCache("EntityLivingBase::getHealth");
		if (methodID == 0) {
			return 0;
		}

		float health = g_env->CallFloatMethod(m_instance, methodID);

		return health;
	}

	bool isEntityAlive() const {
		jmethodID methodID = forgeCache.FindMethodCache("EntityLivingBase::isEntityAlive");
		if (methodID == 0) {
			return false;
		}

		bool alive = g_env->CallBooleanMethod(m_instance, methodID);

		return alive;
	}

	jfloat getMoveForward() const {
		jfieldID filedId = forgeCache.FindFieldCache("EntityLivingBase::moveForward");
		if (filedId == nullptr) {
			return 0;
		}

		jfloat value = g_env->GetFloatField(m_instance, filedId);

		return value;
	}

};
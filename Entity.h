#pragma once
#include "globals.h"
#include "ForgeCache.h"
#include "Object.h"

#include "AxisAlignedBB.h"

#include "Structures.h"

class Entity : public Object {
public:
	using Object::Object;
	Vector2 getAngles()
	{
		return Vector2(getRotationYaw(), getRotationPitch());
	}
	void setAngles(Vector2 angles)
	{
		g_env->SetFloatField(this->obj(), forgeCache.FindFieldCache("Entity::rotationYaw") , angles.X);
		g_env->SetFloatField(this->obj(), forgeCache.FindFieldCache("Entity::rotationPitch") , angles.Y);
	};
	bool isInvisible() const {
		jmethodID methodID = forgeCache.FindMethodCache("Entity::isInvisible");
		if (methodID == 0) {
			return false;
		}

		bool invisible = g_env->CallBooleanMethod(m_instance, methodID);

		return invisible;
	}

	double getPosX() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::posX");
		if (fieldId == 0) {
			return 0;
		}

		double posX = g_env->GetDoubleField(m_instance, fieldId);

		return posX;
	}

	double getPosY() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::posY");
		if (fieldId == 0) {
			return 0;
		}

		double posY = g_env->GetDoubleField(m_instance, fieldId);

		return posY;
	}

	double getPosZ() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::posZ");
		if (fieldId == 0) {
			return 0;
		}
		
		double posZ = g_env->GetDoubleField(m_instance, fieldId);

		return posZ;
	}

	Vector3 getPos() {

		return Vector3((float)getPosX(), (float)getPosY(), (float)getPosZ());
	}

	double getLastTickPosX() const {
		
		jfieldID fieldId = forgeCache.FindFieldCache("Entity::lastTickPosX");
		if (fieldId == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldId);

		return value;
	}

	double getLastTickPosY() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::lastTickPosY");
		if (fieldId == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldId);

		return value;
	}

	double getLastTickPosZ() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::lastTickPosZ");
		if (fieldId == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldId);

		return value;
	}

	int getTickExisted() {
		jfieldID fieldID = forgeCache.FindFieldCache("Entity::ticksExisted");
		if (fieldID == 0) {
			return 0;
		}

		int tickExisted = g_env->GetIntField(m_instance, fieldID);

		return tickExisted;
	}

	float getRotationYaw() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::rotationYaw");
		if (fieldId == 0) {
			return 0;
		}

		float rotationYaw = g_env->GetFloatField(m_instance, fieldId);

		return rotationYaw;
	}

	float getRotationPitch() const {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::rotationPitch");
		if (fieldId == 0) {
			return 0;
		}

		float rotationPitch = g_env->GetFloatField(m_instance, fieldId);

		return rotationPitch;
	}

	void setRotationYaw(float value) {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::rotationYaw");
		if (fieldId == 0) {
			return;
		}

		g_env->SetFloatField(m_instance, fieldId, value);

	}

	void setRotationPitch(float value) {

		jfieldID fieldId = forgeCache.FindFieldCache("Entity::rotationPitch");
		if (fieldId == 0) {
			return;
		}

		g_env->SetFloatField(m_instance, fieldId, value);

	}

	float getDistanceToEntity(Entity entity) const {
		
		jmethodID methodID = forgeCache.FindMethodCache("Entity::getDistanceToEntity");
		if (methodID == 0) {
			return 0;
		}

		float distance = g_env->CallFloatMethod(m_instance, methodID, entity);

		return distance;
	}

	float getHeight() {
		
		jfieldID fieldID = forgeCache.FindFieldCache("Entity::height");
		if (fieldID == 0) {
			return 0;
		}

		float value = g_env->GetFloatField(m_instance, fieldID);
		
		return value;
	}

	AxisAlignedBB getEntityBoundingBox() const {

		jmethodID methodID = forgeCache.FindMethodCache("Entity::getEntityBoundingBox");
		if (methodID == 0) {
			return AxisAlignedBB(0);
		}

		jobject obj = g_env->CallObjectMethod(m_instance, methodID);

		return AxisAlignedBB(obj);
	}

};
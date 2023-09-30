#pragma once

#include "Object.h"
#include "Entity.h"
#include "EnumFacing.h"

class PlayerControllerMP : public Object {
public:
	using Object::Object;


	void attackEntity(EntityPlayer player, Entity entity) {
		
		jmethodID methodID = forgeCache.FindMethodCache("PlayerControllerMP::attackEntity");
		if (methodID == 0) {
			return;
		}

		g_env->CallVoidMethod(m_instance, methodID, player, entity);

	}

	bool clickBlock(BlockPos loc, EnumFacing face) {
		
		jmethodID methodID = forgeCache.FindMethodCache("PlayerControllerMP::clickBlock");
		if (methodID == 0) {
			return false;
		}

		bool value = g_env->CallBooleanMethod(m_instance, methodID, loc, face);

		return value;
	}

};
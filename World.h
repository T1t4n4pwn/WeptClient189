#pragma once
#include "globals.h"
#include "Object.h"
#include <vector>

#include "BlockPos.h"

class World : public Object {
public:
	using Object::Object;

	std::vector<Entity> getLoadedEntityList() {
		std::vector<Entity> entityList;

		jmethodID mid = forgeCache.FindMethodCache("World::getLoadedEntityList");
		if (mid == 0) {
			return entityList;
		}

		jobject listObj = g_env->CallObjectMethod(m_instance, mid);
		if (listObj == 0) {
			return entityList;
		}
		
		jmethodID sizeMethod = forgeCache.FindMethodCache("List::size");
		jmethodID getMethod = forgeCache.FindMethodCache("List::get");

		if (sizeMethod == 0 || getMethod == 0) {
			return entityList;
		}

		int size = g_env->CallIntMethod(listObj, sizeMethod);

		for (size_t i = 0; i < size; i++)
		{
			jobject obj = g_env->CallObjectMethod(listObj, getMethod, i);

			if (obj == 0) {
				continue;
			}

			Entity crtEntity(obj);

			entityList.emplace_back(crtEntity);
		}
		
		return entityList;
	}

	bool isAirBlock(BlockPos block) {
		
		jmethodID methodID = forgeCache.FindMethodCache("World::isAirBlock");
		if (methodID == 0) {
			return false;
		}

		bool value = g_env->CallBooleanMethod(m_instance, methodID, block);

		return value;
	}

};
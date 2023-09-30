#pragma once
#include "globals.h"
#include "Object.h"
#include "Item.h"
class ItemStack : public Object {
public:
	using Object::Object;

	Item getItem() {

		jmethodID methodID = forgeCache.FindMethodCache("ItemStack::getItem");
		if (methodID == 0) {
			return Item(0);
		}

		jobject obj = g_env->CallObjectMethod(m_instance, methodID);

		return Item(obj);
	}

};
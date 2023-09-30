#pragma once
#include "globals.h"
#include "Object.h"
#include "ForgeCache.h"
#include <vector>

class ActiveRenderInfo : public Object{
public:
	using Object::Object;

	static Matrix getModelView() {

		Matrix matrix;

		jfieldID fieldID = forgeCache.FindFieldCache("ActiveRenderInfo::MODELVIEW");
		if (fieldID == 0) {
			return matrix;
		}

		jobject obj = g_env->GetStaticObjectField(forgeCache.FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), fieldID);
		if (obj == 0) {
			return matrix;
		}

		jmethodID methodID = forgeCache.FindMethodCache("FloatBuffer::get");
		if (methodID == 0) {
			return matrix;
		}

		for (size_t i = 0; i < 16; i++)
		{
			float var = g_env->CallFloatMethod(obj, methodID, i);
			matrix.Data[0][i] = var;
		}

		return matrix;
	}

	static Matrix getProjection() {

		Matrix matrix;

		jfieldID fieldID = forgeCache.FindFieldCache("ActiveRenderInfo::PROJECTION");
		if (fieldID == 0) {
			return matrix;
		}

		jobject obj = g_env->GetStaticObjectField(forgeCache.FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), fieldID);
		if (obj == 0) {
			return matrix;
		}

		jmethodID methodID = forgeCache.FindMethodCache("FloatBuffer::get");
		if (methodID == 0) {
			return matrix;
		}

		for (size_t i = 0; i < 16; i++)
		{
			float var = g_env->CallFloatMethod(obj, methodID, i);
			matrix.Data[0][i] = var;
		}

		return matrix;
	}

	static std::vector<int> getViewPort() {

		std::vector<int> result;

		jfieldID fieldID = forgeCache.FindFieldCache("ActiveRenderInfo::VIEWPORT");
		if (fieldID == 0) {
			return result;
		}

		jobject obj = g_env->GetStaticObjectField(forgeCache.FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), fieldID);
		if (obj == 0) {
			return result;
		}

		jmethodID methodID = forgeCache.FindMethodCache("IntBuffer::get");
		if (methodID == 0) {
			return result;
		}

		for (size_t i = 0; i < 16; i++)
		{
			int var = g_env->CallIntMethod(obj, methodID, i);
			result.push_back(var);
		}

		return result;
	}

};
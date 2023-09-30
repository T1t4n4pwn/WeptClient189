#pragma once
#include "globals.h"
#include "Object.h"
#include "utils.h"
#include "EntityPlayerSP.h"
#include "WorldClient.h"
#include "RenderManager.h"
#include "Timer.h"
#include "MovingObjectPosition.h"

#include "PlayerControllerMP.h"
#include "GuiScreen.h"
#include "GameSettings.h"

class Minecraft : public Object{
public:

	static jobject getMinecraft() {
		if (mc == 0) {
			jmethodID getMinecraft = forgeCache.FindMethodCache("Minecraft::getMinecraft");
			if (getMinecraft == nullptr) { return 0; }
			mc = g_env->CallStaticObjectMethod(forgeCache.FindClassCache("net/minecraft/client/Minecraft"), getMinecraft);
		}
		return mc;
	}

public:
	using Object::Object;

	EntityPlayerSP getPlayer() {
		
		jfieldID filedId = forgeCache.FindFieldCache("Minecraft::player");
		if (filedId == 0) {
			return EntityPlayerSP(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, filedId);
		
		return EntityPlayerSP(obj);
	}

	WorldClient getWorld() {

		jfieldID filedId = forgeCache.FindFieldCache("Minecraft::world");
		if (filedId == 0) {
			return WorldClient(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, filedId);

		return obj;
	}

	RenderManager getRenderManager() {

		jmethodID methodID = forgeCache.FindMethodCache("Minecraft::getRenderManager");

		if (methodID == 0) {
			return RenderManager(0);
		}

		jobject obj = g_env->CallObjectMethod(m_instance, methodID);

		return RenderManager(obj);
	}
	
	Timer getTimer() {
		jfieldID fieldID = forgeCache.FindFieldCache("Minecraft::timer");
		if (fieldID == 0) {
			return Timer(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, fieldID);
		
		return Timer(obj);
	}

	PlayerControllerMP getPlayerController() {
		
		jfieldID fieldID = forgeCache.FindFieldCache("Minecraft::playerController");
		if (fieldID == 0) {
			return PlayerControllerMP(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, fieldID);

		return obj;
	}

	GuiScreen getCurrentScreen() {
	
		jfieldID fieldID = forgeCache.FindFieldCache("Minecraft::currentScreen");
		if (fieldID == 0) {
			return GuiScreen(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, fieldID);

		return GuiScreen(obj);
	}

	MovingObjectPosition getObjectMouseOver() {
		jfieldID fieldID = forgeCache.FindFieldCache("Minecraft::objectMouseOver");
		if (fieldID == 0) {
			return MovingObjectPosition(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, fieldID);

		return MovingObjectPosition(obj);
	}

	void clickMouse() {

		jmethodID methodID = forgeCache.FindMethodCache("Minecraft::clickMouse");
		if (methodID == 0) {
			return;
		}

		g_env->CallVoidMethod(m_instance, methodID);

	}

	GameSettings getGameSettings() {

		jfieldID fieldID = forgeCache.FindFieldCache("Minecraft::gameSettings");
		if (fieldID == 0) {
			return GameSettings(0);
		}

		jobject obj = g_env->GetObjectField(m_instance, fieldID);

		return GameSettings(obj);
	}


private:

	static jobject mc;

};
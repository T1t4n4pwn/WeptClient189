#include "ForgeCache.h"
#include <Windows.h>
#include <VMProtectSDK.h>
ForgeCache forgeCache;

void ForgeCache::InitCache()
{
	VMProtectBegin("InitCache");

	int choice = MessageBoxA(0, "您注入的客户端是否有forge?", "是: forge模式 否:lunar模式", MB_YESNO);

	if (choice == IDYES) {
		InitForge();
	}
	else if (choice == IDNO) {
		InitLunar();
	}
	else {
	MessageBoxA(0, "用户关闭了选择框，即将退出", "Error", MB_ICONERROR);
	ExitProcess(0);
}
	

	VMProtectEnd();
}

jclass ForgeCache::FindClassCache(const std::string& key)
{

	std::map<std::string, jclass>::iterator iter = classCache.find(key);
	if (iter != classCache.end()) {
		return iter->second;
	}
	else {
		return 0;
	}

}

jmethodID ForgeCache::FindMethodCache(const std::string& key)
{

	std::map<std::string, jmethodID>::iterator iter = methodCache.find(key);
	if (iter != methodCache.end()) {
		return iter->second;
	}
	else {
		return 0;
	}

}

jfieldID ForgeCache::FindFieldCache(const std::string& key)
{

	std::map<std::string, jfieldID>::iterator iter = fieldCache.find(key);
	if (iter != fieldCache.end()) {
		return iter->second;
	}
	else {
		return 0;
	}

}

void ForgeCache::InitForge()
{
	classCache["java/util/List"] = g_env->FindClass("java/util/List");

	classCache["java/nio/FloatBuffer"] = g_env->FindClass("java/nio/FloatBuffer");
	classCache["java/nio/IntBuffer"] = g_env->FindClass("java/nio/IntBuffer");
	classCache["org/lwjgl/input/Mouse"] = g_env->FindClass("org/lwjgl/input/Mouse");
	classCache["java/lang/Enum"] = g_env->FindClass("java/lang/Enum");

	classCache["net/minecraft/client/Minecraft"] = ForgeFindClass("net/minecraft/client/Minecraft");
	classCache["net/minecraft/entity/EntityLivingBase"] = ForgeFindClass("net/minecraft/entity/EntityLivingBase");
	classCache["net/minecraft/client/entity/EntityPlayerSP"] = ForgeFindClass("net/minecraft/client/entity/EntityPlayerSP");
	classCache["net/minecraft/client/multiplayer/WorldClient"] = ForgeFindClass("net/minecraft/client/multiplayer/WorldClient");
	classCache["net/minecraft/client/multiplayer/PlayerControllerMP"] = ForgeFindClass("net/minecraft/client/multiplayer/PlayerControllerMP");
	classCache["net/minecraft/world/World"] = ForgeFindClass("net/minecraft/world/World");
	classCache["net/minecraft/entity/player/EntityPlayer"] = ForgeFindClass("net/minecraft/entity/player/EntityPlayer");
	classCache["net/minecraft/entity/Entity"] = ForgeFindClass("net/minecraft/entity/Entity");

	classCache["net/minecraft/util/AxisAlignedBB"] = ForgeFindClass("net/minecraft/util/AxisAlignedBB");
	classCache["net/minecraft/util/BlockPos"] = ForgeFindClass("net/minecraft/util/BlockPos");

	classCache["net/minecraft/client/renderer/ActiveRenderInfo"] = ForgeFindClass("net/minecraft/client/renderer/ActiveRenderInfo");
	classCache["net/minecraft/client/renderer/entity/RenderManager"] = ForgeFindClass("net/minecraft/client/renderer/entity/RenderManager");

	classCache["net/minecraft/util/MovingObjectPosition"] = ForgeFindClass("net/minecraft/util/MovingObjectPosition");
	classCache["net/minecraft/util/EnumFacing"] = ForgeFindClass("net/minecraft/util/EnumFacing");



	classCache["net/minecraft/util/Timer"] = ForgeFindClass("net/minecraft/util/Timer");

	classCache["net/minecraft/util/IChatComponent"] = ForgeFindClass("net/minecraft/util/IChatComponent");

	classCache["net/minecraft/client/settings/KeyBinding"] = ForgeFindClass("net/minecraft/client/settings/KeyBinding");
	classCache["net/minecraft/client/settings/GameSettings"] = ForgeFindClass("net/minecraft/client/settings/GameSettings");

	classCache["net/minecraft/item/ItemStack"] = ForgeFindClass("net/minecraft/item/ItemStack");
	classCache["net/minecraft/item/ItemSword"] = ForgeFindClass("net/minecraft/item/ItemSword");
	classCache["net/minecraft/item/ItemAxe"] = ForgeFindClass("net/minecraft/item/ItemAxe");

	std::map<std::string, jclass>::iterator iter;

	for (iter = classCache.begin(); iter != classCache.end(); iter++)
	{
		if (iter->second == 0) {
			MessageBoxA(0, "获取失败", iter->first.c_str(), 0);
			continue;
		}
		iter->second = (jclass)g_env->NewGlobalRef(iter->second);
	}

	methodCache["List::size"] = g_env->GetMethodID(FindClassCache("java/util/List"), "size", "()I");
	methodCache["List::get"] = g_env->GetMethodID(FindClassCache("java/util/List"), "get", "(I)Ljava/lang/Object;");
	methodCache["FloatBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/FloatBuffer"), "get", "(I)F");
	methodCache["IntBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/IntBuffer"), "get", "(I)I");
	methodCache["Enum::toString"] = g_env->GetMethodID(FindClassCache("java/lang/Enum"), "toString", "()Ljava/lang/String;");

	//methodCache["ForgeHooks::onEmptyLeftClick"] = g_env->GetStaticMethodID(FindClassCache("net/minecraftforge/common/ForgeHooks"), "onEmptyLeftClick", "(Lnet/minecraft/entity/player/EntityPlayer;)V");

	methodCache["Mouse::isButtonDown"] = g_env->GetStaticMethodID(FindClassCache("org/lwjgl/input/Mouse"), "isButtonDown", "(I)Z");

	methodCache["Minecraft::getMinecraft"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/Minecraft"), "func_71410_x", "()Lnet/minecraft/client/Minecraft;");

	methodCache["Minecraft::getRenderManager"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "func_175598_ae", "()Lnet/minecraft/client/renderer/entity/RenderManager;");

	methodCache["Minecraft::clickMouse"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "func_147116_af", "()V");

	methodCache["EntityPlayerSP::setSprinting"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "func_70031_b", "(Z)V");
	methodCache["EntityPlayerSP::swingItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "func_71038_i", "()V");

	methodCache["EntityPlayer::getName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70005_c_", "()Ljava/lang/String;");
	methodCache["EntityPlayer::getEyeHeight"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70047_e", "()F");
	methodCache["EntityPlayer::isPlayerSleeping"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70608_bn", "()Z");

	methodCache["EntityPlayer::getHeldItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70694_bm", "()Lnet/minecraft/item/ItemStack;");

	methodCache["EntityPlayer::getDisplayName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_145748_c_", "()Lnet/minecraft/util/IChatComponent;");

	methodCache["PlayerControllerMP::attackEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
	methodCache["PlayerControllerMP::clickBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "func_180511_b", "(Lnet/minecraft/util/BlockPos;Lnet/minecraft/util/EnumFacing;)Z");

	methodCache["World::getLoadedEntityList"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "func_72910_y", "()Ljava/util/List;");
	methodCache["World::isAirBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");

	methodCache["Entity::isInvisible"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_82150_aj", "()Z");
	methodCache["Entity::getDistanceToEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_70032_d", "(Lnet/minecraft/entity/Entity;)F");
	methodCache["Entity::getEntityBoundingBox"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_174813_aQ", "()Lnet/minecraft/util/AxisAlignedBB;");

	methodCache["EntityLivingBase::getHealth"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "func_110143_aJ", "()F");
	methodCache["EntityLivingBase::isEntityAlive"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "func_70089_S", "()Z");


	methodCache["MovingObjectPosition::getBlockPos"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "func_178782_a", "()Lnet/minecraft/util/BlockPos;");
	methodCache["IChatComponent::getFormattedText"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/IChatComponent"), "func_150254_d", "()Ljava/lang/String;");

	methodCache["KeyBinding::setKeyBindState"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_74510_a", "(IZ)V");
	methodCache["KeyBinding::onTick"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_74507_a", "(I)V");
	methodCache["KeyBinding::getKeyCode"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_151463_i", "()I");
	methodCache["KeyBinding::isKeyDown"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_151470_d", "()Z");

	methodCache["ItemStack::getItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/item/ItemStack"), "func_77973_b", "()Lnet/minecraft/item/Item;");

	std::map<std::string, jmethodID>::iterator methoditer;
	for (methoditer = methodCache.begin(); methoditer != methodCache.end(); methoditer++)
	{
		if (methoditer->second == 0) {
			MessageBoxA(0, "MethodID获取失败", methoditer->first.c_str(), 0);
			continue;
		}
	}


	fieldCache["Minecraft::player"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	fieldCache["Minecraft::world"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");

	fieldCache["Minecraft::timer"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71428_T", "Lnet/minecraft/util/Timer;");

	fieldCache["Minecraft::objectMouseOver"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
	fieldCache["Minecraft::playerController"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
	fieldCache["Minecraft::gameSettings"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");

	fieldCache["Minecraft::currentScreen"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");


	fieldCache["EntityLivingBase::moveForward"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "field_70701_bs", "F");

	fieldCache["Entity::posX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70165_t", "D");
	fieldCache["Entity::posY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70163_u", "D");
	fieldCache["Entity::posZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70161_v", "D");
	fieldCache["Entity::lastTickPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70142_S", "D");
	fieldCache["Entity::lastTickPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70137_T", "D");
	fieldCache["Entity::lastTickPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70136_U", "D");

	fieldCache["Entity::rotationYaw"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70177_z", "F");
	fieldCache["Entity::rotationPitch"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70125_A", "F");
	fieldCache["Entity::ticksExisted"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70173_aa", "I");

	fieldCache["Entity::height"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70131_O", "F");

	fieldCache["ActiveRenderInfo::MODELVIEW"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178812_b", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::PROJECTION"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178813_c", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::VIEWPORT"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178814_a", "Ljava/nio/IntBuffer;");

	fieldCache["AxisAlignedBB::minX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72340_a", "D");
	fieldCache["AxisAlignedBB::minY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72338_b", "D");
	fieldCache["AxisAlignedBB::minZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72339_c", "D");
	fieldCache["AxisAlignedBB::maxX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72336_d", "D");
	fieldCache["AxisAlignedBB::maxY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72337_e", "D");
	fieldCache["AxisAlignedBB::maxZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72334_f", "D");

	fieldCache["RenderManager::renderPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78725_b", "D");
	fieldCache["RenderManager::renderPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78726_c", "D");
	fieldCache["RenderManager::renderPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78723_d", "D");

	fieldCache["Timer::renderPartialTicks"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/Timer"), "field_74281_c", "F");

	fieldCache["MovingObjectPosition::typeOfHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	fieldCache["MovingObjectPosition::sideHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_178784_b", "Lnet/minecraft/util/EnumFacing;");
	fieldCache["MovingObjectPosition::entityHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_72308_g", "Lnet/minecraft/entity/Entity;");

	fieldCache["GameSettings::keyBindAttack"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "field_74312_F", "Lnet/minecraft/client/settings/KeyBinding;");
	fieldCache["GameSettings::keyBindUseItem"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "field_74313_G", "Lnet/minecraft/client/settings/KeyBinding;");


	std::map<std::string, jfieldID>::iterator fieldIter;
	for (fieldIter = fieldCache.begin(); fieldIter != fieldCache.end(); fieldIter++)
	{
		if (fieldIter->second == 0) {
			MessageBoxA(0, "获取失败", fieldIter->first.c_str(), 0);
			continue;
		}
	}
}

//未完成
void ForgeCache::InitVanilla()
{

	classCache["java/util/List"] = g_env->FindClass("java/util/List");

	classCache["java/nio/FloatBuffer"] = g_env->FindClass("java/nio/FloatBuffer");
	classCache["java/nio/IntBuffer"] = g_env->FindClass("java/nio/IntBuffer");
	classCache["org/lwjgl/input/Mouse"] = g_env->FindClass("org/lwjgl/input/Mouse");
	classCache["java/lang/Enum"] = g_env->FindClass("java/lang/Enum");

	classCache["net/minecraft/client/Minecraft"] = g_env->FindClass("ave");
	classCache["net/minecraft/entity/EntityLivingBase"] = g_env->FindClass("pr");
	classCache["net/minecraft/client/entity/EntityPlayerSP"] = g_env->FindClass("bew");
	classCache["net/minecraft/client/multiplayer/WorldClient"] = g_env->FindClass("bdb");
	classCache["net/minecraft/client/multiplayer/PlayerControllerMP"] = g_env->FindClass("bda");
	classCache["net/minecraft/world/World"] = g_env->FindClass("adm");
	classCache["net/minecraft/entity/player/EntityPlayer"] = g_env->FindClass("wn");
	classCache["net/minecraft/entity/Entity"] = g_env->FindClass("pk");

	classCache["net/minecraft/util/AxisAlignedBB"] = g_env->FindClass("aug");
	classCache["net/minecraft/util/BlockPos"] = g_env->FindClass("cj");

	classCache["net/minecraft/client/renderer/ActiveRenderInfo"] = g_env->FindClass("auz");
	classCache["net/minecraft/client/renderer/entity/RenderManager"] = g_env->FindClass("biu");

	classCache["net/minecraft/util/MovingObjectPosition"] = g_env->FindClass("auh");
	classCache["net/minecraft/util/EnumFacing"] = g_env->FindClass("cq");



	classCache["net/minecraft/util/Timer"] = g_env->FindClass("avl");

	classCache["net/minecraft/util/IChatComponent"] = g_env->FindClass("eu");

	classCache["net/minecraft/client/settings/KeyBinding"] = g_env->FindClass("avb");
	classCache["net/minecraft/client/settings/GameSettings"] = g_env->FindClass("avh");

	classCache["net/minecraft/item/ItemStack"] = g_env->FindClass("zx");
	classCache["net/minecraft/item/ItemSword"] = g_env->FindClass("aay");
	classCache["net/minecraft/item/ItemAxe"] = g_env->FindClass("yl");

	std::map<std::string, jclass>::iterator iter;

	for (iter = classCache.begin(); iter != classCache.end(); iter++)
	{
		if (iter->second == 0) {
			MessageBoxA(0, "获取失败", iter->first.c_str(), 0);
			continue;
		}
		iter->second = (jclass)g_env->NewGlobalRef(iter->second);
	}

	methodCache["List::size"] = g_env->GetMethodID(FindClassCache("java/util/List"), "size", "()I");
	methodCache["List::get"] = g_env->GetMethodID(FindClassCache("java/util/List"), "get", "(I)Ljava/lang/Object;");
	methodCache["FloatBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/FloatBuffer"), "get", "(I)F");
	methodCache["IntBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/IntBuffer"), "get", "(I)I");
	methodCache["Enum::toString"] = g_env->GetMethodID(FindClassCache("java/lang/Enum"), "toString", "()Ljava/lang/String;");

	methodCache["Mouse::isButtonDown"] = g_env->GetStaticMethodID(FindClassCache("org/lwjgl/input/Mouse"), "isButtonDown", "(I)Z");

	methodCache["Minecraft::getMinecraft"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/Minecraft"), "A", "()Lnet/minecraft/client/Minecraft;");

	methodCache["Minecraft::getRenderManager"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "func_175598_ae", "()Lnet/minecraft/client/renderer/entity/RenderManager;");

	methodCache["Minecraft::clickMouse"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "func_147116_af", "()V");

	methodCache["EntityPlayerSP::setSprinting"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "func_70031_b", "(Z)V");
	methodCache["EntityPlayerSP::swingItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "func_71038_i", "()V");

	methodCache["EntityPlayer::getName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70005_c_", "()Ljava/lang/String;");
	methodCache["EntityPlayer::getEyeHeight"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70047_e", "()F");
	methodCache["EntityPlayer::isPlayerSleeping"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70608_bn", "()Z");

	methodCache["EntityPlayer::getHeldItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_70694_bm", "()Lnet/minecraft/item/ItemStack;");

	methodCache["EntityPlayer::getDisplayName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "func_145748_c_", "()Lnet/minecraft/util/IChatComponent;");

	methodCache["PlayerControllerMP::attackEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
	methodCache["PlayerControllerMP::clickBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "func_180511_b", "(Lnet/minecraft/util/BlockPos;Lnet/minecraft/util/EnumFacing;)Z");

	methodCache["World::getLoadedEntityList"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "func_72910_y", "()Ljava/util/List;");
	methodCache["World::isAirBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");

	methodCache["Entity::isInvisible"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_82150_aj", "()Z");
	methodCache["Entity::getDistanceToEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_70032_d", "(Lnet/minecraft/entity/Entity;)F");
	methodCache["Entity::getEntityBoundingBox"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "func_174813_aQ", "()Lnet/minecraft/util/AxisAlignedBB;");

	methodCache["EntityLivingBase::getHealth"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "func_110143_aJ", "()F");
	methodCache["EntityLivingBase::isEntityAlive"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "func_70089_S", "()Z");


	methodCache["MovingObjectPosition::getBlockPos"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "func_178782_a", "()Lnet/minecraft/util/BlockPos;");
	methodCache["IChatComponent::getFormattedText"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/IChatComponent"), "func_150254_d", "()Ljava/lang/String;");

	methodCache["KeyBinding::setKeyBindState"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_74510_a", "(IZ)V");
	methodCache["KeyBinding::onTick"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_74507_a", "(I)V");
	methodCache["KeyBinding::getKeyCode"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_151463_i", "()I");
	methodCache["KeyBinding::isKeyDown"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "func_151470_d", "()Z");

	methodCache["ItemStack::getItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/item/ItemStack"), "func_77973_b", "()Lnet/minecraft/item/Item;");

	std::map<std::string, jmethodID>::iterator methoditer;
	for (methoditer = methodCache.begin(); methoditer != methodCache.end(); methoditer++)
	{
		if (methoditer->second == 0) {
			MessageBoxA(0, "MethodID获取失败", methoditer->first.c_str(), 0);
			continue;
		}
	}


	fieldCache["Minecraft::player"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	fieldCache["Minecraft::world"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");

	fieldCache["Minecraft::timer"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71428_T", "Lnet/minecraft/util/Timer;");

	fieldCache["Minecraft::objectMouseOver"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
	fieldCache["Minecraft::playerController"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
	fieldCache["Minecraft::gameSettings"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");

	fieldCache["Minecraft::currentScreen"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");


	fieldCache["EntityLivingBase::moveForward"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "field_70701_bs", "F");

	fieldCache["Entity::posX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70165_t", "D");
	fieldCache["Entity::posY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70163_u", "D");
	fieldCache["Entity::posZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70161_v", "D");
	fieldCache["Entity::lastTickPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70142_S", "D");
	fieldCache["Entity::lastTickPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70137_T", "D");
	fieldCache["Entity::lastTickPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70136_U", "D");

	fieldCache["Entity::rotationYaw"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70177_z", "F");
	fieldCache["Entity::rotationPitch"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70125_A", "F");
	fieldCache["Entity::ticksExisted"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70173_aa", "I");

	fieldCache["Entity::height"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "field_70131_O", "F");

	fieldCache["ActiveRenderInfo::MODELVIEW"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178812_b", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::PROJECTION"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178813_c", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::VIEWPORT"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "field_178814_a", "Ljava/nio/IntBuffer;");

	fieldCache["AxisAlignedBB::minX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72340_a", "D");
	fieldCache["AxisAlignedBB::minY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72338_b", "D");
	fieldCache["AxisAlignedBB::minZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72339_c", "D");
	fieldCache["AxisAlignedBB::maxX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72336_d", "D");
	fieldCache["AxisAlignedBB::maxY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72337_e", "D");
	fieldCache["AxisAlignedBB::maxZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "field_72334_f", "D");

	fieldCache["RenderManager::renderPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78725_b", "D");
	fieldCache["RenderManager::renderPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78726_c", "D");
	fieldCache["RenderManager::renderPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "field_78723_d", "D");

	fieldCache["Timer::renderPartialTicks"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/Timer"), "field_74281_c", "F");

	fieldCache["MovingObjectPosition::typeOfHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	fieldCache["MovingObjectPosition::sideHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_178784_b", "Lnet/minecraft/util/EnumFacing;");
	fieldCache["MovingObjectPosition::entityHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "field_72308_g", "Lnet/minecraft/entity/Entity;");

	fieldCache["GameSettings::keyBindAttack"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "field_74312_F", "Lnet/minecraft/client/settings/KeyBinding;");
	fieldCache["GameSettings::keyBindUseItem"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "field_74313_G", "Lnet/minecraft/client/settings/KeyBinding;");


	std::map<std::string, jfieldID>::iterator fieldIter;
	for (fieldIter = fieldCache.begin(); fieldIter != fieldCache.end(); fieldIter++)
	{
		if (fieldIter->second == 0) {
			MessageBoxA(0, "获取失败", fieldIter->first.c_str(), 0);
			continue;
		}
	}
}

void ForgeCache::InitLunar()
{

	setupClassLoader();


	classCache["java/util/List"] = FindClassByClassLoader("java/util/List");

	classCache["java/nio/FloatBuffer"] = FindClassByClassLoader("java/nio/FloatBuffer");
	classCache["java/nio/IntBuffer"] = FindClassByClassLoader("java/nio/IntBuffer");
	classCache["org/lwjgl/input/Mouse"] = FindClassByClassLoader("org/lwjgl/input/Mouse");
	classCache["java/lang/Enum"] = FindClassByClassLoader("java/lang/Enum");

	classCache["net/minecraft/client/Minecraft"] = FindClassByClassLoader("net/minecraft/client/Minecraft");
	classCache["net/minecraft/entity/EntityLivingBase"] = FindClassByClassLoader("net/minecraft/entity/EntityLivingBase");
	classCache["net/minecraft/client/entity/EntityPlayerSP"] = FindClassByClassLoader("net/minecraft/client/entity/EntityPlayerSP");
	classCache["net/minecraft/client/multiplayer/WorldClient"] = FindClassByClassLoader("net/minecraft/client/multiplayer/WorldClient");
	classCache["net/minecraft/client/multiplayer/PlayerControllerMP"] = FindClassByClassLoader("net/minecraft/client/multiplayer/PlayerControllerMP");
	classCache["net/minecraft/world/World"] = FindClassByClassLoader("net/minecraft/world/World");
	classCache["net/minecraft/entity/player/EntityPlayer"] = FindClassByClassLoader("net/minecraft/entity/player/EntityPlayer");
	classCache["net/minecraft/entity/Entity"] = FindClassByClassLoader("net/minecraft/entity/Entity");

	classCache["net/minecraft/util/AxisAlignedBB"] = FindClassByClassLoader("net/minecraft/util/AxisAlignedBB");
	classCache["net/minecraft/util/BlockPos"] = FindClassByClassLoader("net/minecraft/util/BlockPos");

	classCache["net/minecraft/client/renderer/ActiveRenderInfo"] = FindClassByClassLoader("net/minecraft/client/renderer/ActiveRenderInfo");
	classCache["net/minecraft/client/renderer/entity/RenderManager"] = FindClassByClassLoader("net/minecraft/client/renderer/entity/RenderManager");

	classCache["net/minecraft/util/MovingObjectPosition"] = FindClassByClassLoader("net/minecraft/util/MovingObjectPosition");
	classCache["net/minecraft/util/EnumFacing"] = FindClassByClassLoader("net/minecraft/util/EnumFacing");



	classCache["net/minecraft/util/Timer"] = FindClassByClassLoader("net/minecraft/util/Timer");

	classCache["net/minecraft/util/IChatComponent"] = FindClassByClassLoader("net/minecraft/util/IChatComponent");

	classCache["net/minecraft/client/settings/KeyBinding"] = FindClassByClassLoader("net/minecraft/client/settings/KeyBinding");
	classCache["net/minecraft/client/settings/GameSettings"] = FindClassByClassLoader("net/minecraft/client/settings/GameSettings");

	classCache["net/minecraft/item/ItemStack"] = FindClassByClassLoader("net/minecraft/item/ItemStack");
	classCache["net/minecraft/item/ItemSword"] = FindClassByClassLoader("net/minecraft/item/ItemSword");
	classCache["net/minecraft/item/ItemAxe"] = FindClassByClassLoader("net/minecraft/item/ItemAxe");

	std::map<std::string, jclass>::iterator iter;

	for (iter = classCache.begin(); iter != classCache.end(); iter++)
	{
		if (iter->second == 0) {
			MessageBoxA(0, "获取失败", iter->first.c_str(), 0);
			continue;
		}
		iter->second = (jclass)g_env->NewGlobalRef(iter->second);
	}

	methodCache["List::size"] = g_env->GetMethodID(FindClassCache("java/util/List"), "size", "()I");
	methodCache["List::get"] = g_env->GetMethodID(FindClassCache("java/util/List"), "get", "(I)Ljava/lang/Object;");
	methodCache["FloatBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/FloatBuffer"), "get", "(I)F");
	methodCache["IntBuffer::get"] = g_env->GetMethodID(FindClassCache("java/nio/IntBuffer"), "get", "(I)I");
	methodCache["Enum::toString"] = g_env->GetMethodID(FindClassCache("java/lang/Enum"), "toString", "()Ljava/lang/String;");

	//methodCache["ForgeHooks::onEmptyLeftClick"] = g_env->GetStaticMethodID(FindClassCache("net/minecraftforge/common/ForgeHooks"), "onEmptyLeftClick", "(Lnet/minecraft/entity/player/EntityPlayer;)V");

	methodCache["Mouse::isButtonDown"] = g_env->GetStaticMethodID(FindClassCache("org/lwjgl/input/Mouse"), "isButtonDown", "(I)Z");

	methodCache["Minecraft::getMinecraft"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/Minecraft"), "getMinecraft", "()Lnet/minecraft/client/Minecraft;");

	methodCache["Minecraft::getRenderManager"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "getRenderManager", "()Lnet/minecraft/client/renderer/entity/RenderManager;");

	methodCache["Minecraft::clickMouse"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/Minecraft"), "clickMouse", "()V");

	methodCache["EntityPlayerSP::setSprinting"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "setSprinting", "(Z)V");
	methodCache["EntityPlayerSP::swingItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/entity/EntityPlayerSP"), "swingItem", "()V");

	methodCache["EntityPlayer::getName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "getName", "()Ljava/lang/String;");
	methodCache["EntityPlayer::getEyeHeight"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "getEyeHeight", "()F");
	methodCache["EntityPlayer::isPlayerSleeping"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "isPlayerSleeping", "()Z");

	methodCache["EntityPlayer::getHeldItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "getHeldItem", "()Lnet/minecraft/item/ItemStack;");

	methodCache["EntityPlayer::getDisplayName"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/player/EntityPlayer"), "getDisplayName", "()Lnet/minecraft/util/IChatComponent;");

	methodCache["PlayerControllerMP::attackEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
	methodCache["PlayerControllerMP::clickBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/multiplayer/PlayerControllerMP"), "clickBlock", "(Lnet/minecraft/util/BlockPos;Lnet/minecraft/util/EnumFacing;)Z");

	methodCache["World::getLoadedEntityList"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "getLoadedEntityList", "()Ljava/util/List;");
	methodCache["World::isAirBlock"] = g_env->GetMethodID(FindClassCache("net/minecraft/world/World"), "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");

	methodCache["Entity::isInvisible"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "isInvisible", "()Z");
	methodCache["Entity::getDistanceToEntity"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "getDistanceToEntity", "(Lnet/minecraft/entity/Entity;)F");
	methodCache["Entity::getEntityBoundingBox"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/Entity"), "getEntityBoundingBox", "()Lnet/minecraft/util/AxisAlignedBB;");

	methodCache["EntityLivingBase::getHealth"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "getHealth", "()F");
	methodCache["EntityLivingBase::isEntityAlive"] = g_env->GetMethodID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "isEntityAlive", "()Z");


	methodCache["MovingObjectPosition::getBlockPos"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "getBlockPos", "()Lnet/minecraft/util/BlockPos;");
	methodCache["IChatComponent::getFormattedText"] = g_env->GetMethodID(FindClassCache("net/minecraft/util/IChatComponent"), "getFormattedText", "()Ljava/lang/String;");

	methodCache["KeyBinding::setKeyBindState"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "setKeyBindState", "(IZ)V");
	methodCache["KeyBinding::onTick"] = g_env->GetStaticMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "onTick", "(I)V");
	methodCache["KeyBinding::getKeyCode"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "getKeyCode", "()I");
	methodCache["KeyBinding::isKeyDown"] = g_env->GetMethodID(FindClassCache("net/minecraft/client/settings/KeyBinding"), "isKeyDown", "()Z");

	methodCache["ItemStack::getItem"] = g_env->GetMethodID(FindClassCache("net/minecraft/item/ItemStack"), "getItem", "()Lnet/minecraft/item/Item;");

	std::map<std::string, jmethodID>::iterator methoditer;
	for (methoditer = methodCache.begin(); methoditer != methodCache.end(); methoditer++)
	{
		if (methoditer->second == 0) {
			MessageBoxA(0, "MethodID获取失败", methoditer->first.c_str(), 0);
			continue;
		}
	}


	fieldCache["Minecraft::player"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	fieldCache["Minecraft::world"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");

	fieldCache["Minecraft::timer"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "timer", "Lnet/minecraft/util/Timer;");

	fieldCache["Minecraft::objectMouseOver"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
	fieldCache["Minecraft::playerController"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
	fieldCache["Minecraft::gameSettings"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");

	fieldCache["Minecraft::currentScreen"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/Minecraft"), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");


	fieldCache["EntityLivingBase::moveForward"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/EntityLivingBase"), "moveForward", "F");

	fieldCache["Entity::posX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "posX", "D");
	fieldCache["Entity::posY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "posY", "D");
	fieldCache["Entity::posZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "posZ", "D");
	fieldCache["Entity::lastTickPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "lastTickPosX", "D");
	fieldCache["Entity::lastTickPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "lastTickPosY", "D");
	fieldCache["Entity::lastTickPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "lastTickPosZ", "D");

	fieldCache["Entity::rotationYaw"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "rotationYaw", "F");
	fieldCache["Entity::rotationPitch"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "rotationPitch", "F");
	fieldCache["Entity::ticksExisted"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "ticksExisted", "I");

	fieldCache["Entity::height"] = g_env->GetFieldID(FindClassCache("net/minecraft/entity/Entity"), "height", "F");

	fieldCache["ActiveRenderInfo::MODELVIEW"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "MODELVIEW", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::PROJECTION"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "PROJECTION", "Ljava/nio/FloatBuffer;");
	fieldCache["ActiveRenderInfo::VIEWPORT"] = g_env->GetStaticFieldID(FindClassCache("net/minecraft/client/renderer/ActiveRenderInfo"), "VIEWPORT", "Ljava/nio/IntBuffer;");

	fieldCache["AxisAlignedBB::minX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "minX", "D");
	fieldCache["AxisAlignedBB::minY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "minY", "D");
	fieldCache["AxisAlignedBB::minZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "minZ", "D");
	fieldCache["AxisAlignedBB::maxX"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "maxX", "D");
	fieldCache["AxisAlignedBB::maxY"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "maxY", "D");
	fieldCache["AxisAlignedBB::maxZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/AxisAlignedBB"), "maxZ", "D");

	fieldCache["RenderManager::renderPosX"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "renderPosX", "D");
	fieldCache["RenderManager::renderPosY"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "renderPosY", "D");
	fieldCache["RenderManager::renderPosZ"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/renderer/entity/RenderManager"), "renderPosZ", "D");

	fieldCache["Timer::renderPartialTicks"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/Timer"), "renderPartialTicks", "F");

	fieldCache["MovingObjectPosition::typeOfHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	fieldCache["MovingObjectPosition::sideHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "sideHit", "Lnet/minecraft/util/EnumFacing;");
	fieldCache["MovingObjectPosition::entityHit"] = g_env->GetFieldID(FindClassCache("net/minecraft/util/MovingObjectPosition"), "entityHit", "Lnet/minecraft/entity/Entity;");

	fieldCache["GameSettings::keyBindAttack"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "keyBindAttack", "Lnet/minecraft/client/settings/KeyBinding;");
	fieldCache["GameSettings::keyBindUseItem"] = g_env->GetFieldID(FindClassCache("net/minecraft/client/settings/GameSettings"), "keyBindUseItem", "Lnet/minecraft/client/settings/KeyBinding;");


	std::map<std::string, jfieldID>::iterator fieldIter;
	for (fieldIter = fieldCache.begin(); fieldIter != fieldCache.end(); fieldIter++)
	{
		if (fieldIter->second == 0) {
			MessageBoxA(0, "获取失败", fieldIter->first.c_str(), 0);
			continue;
		}
	}
}

void ForgeCache::setupClassLoader()
{
	jclass c_Thread = g_env->FindClass("java/lang/Thread");
	jclass c_Map = g_env->FindClass("java/util/Map");
	jclass c_Set = g_env->FindClass("java/util/Set");
	jclass c_ClassLoader = g_env->FindClass("java/lang/ClassLoader");

	jmethodID mid_getAllStackTraces = g_env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
	jmethodID mid_keySet = g_env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
	jmethodID mid_toArray = g_env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
	jmethodID mid_getContextClassLoader = g_env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
	method_find_class = g_env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	jmethodID mid_currentThread = g_env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

	jobject obj_stackTracesMap = g_env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
	jobject obj_threadsSet = g_env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

	jobjectArray threads = (jobjectArray)g_env->CallObjectMethod(obj_threadsSet, mid_toArray);
	jint szThreads = g_env->GetArrayLength(threads);

	for (int i = 0; i < szThreads; i++)
	{
		jobject thread = g_env->GetObjectArrayElement(threads, i);
		jobject classLoaderObj = g_env->CallObjectMethod(thread, mid_getContextClassLoader);

		if (classLoaderObj) {

			jstring className = g_env->NewStringUTF("net.minecraft.client.Minecraft");
			jobject minecraftClass = g_env->CallObjectMethod(classLoaderObj, method_find_class, className);

			g_env->DeleteLocalRef(className);

			if (minecraftClass)
			{
				class_loader_obj = classLoaderObj;

				g_env->DeleteLocalRef(minecraftClass);

				break;
			}
		}

		g_env->DeleteLocalRef(thread);
	}

	g_env->DeleteLocalRef(threads);
	g_env->DeleteLocalRef(obj_stackTracesMap);
	g_env->DeleteLocalRef(obj_threadsSet);
	g_env->DeleteLocalRef(c_Thread);
	g_env->DeleteLocalRef(c_Map);
	g_env->DeleteLocalRef(c_Set);
	g_env->DeleteLocalRef(c_ClassLoader);
}

jclass ForgeCache::FindClassByClassLoader(const char* name)
{
	jstring className = g_env->NewStringUTF(name);
	jobject targetClass = g_env->CallObjectMethod(class_loader_obj, method_find_class, className);
	g_env->DeleteLocalRef(className);

	return (jclass)targetClass;
}


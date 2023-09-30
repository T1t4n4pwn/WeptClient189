#pragma once
#include "globals.h"
#include "Module.h"

#include "Minecraft.h"

#include "ClientUtils.h"
#include "TimerUtil.h"
#include "ForgeHooks.h"
#include "KeyBinding.h"

class AutoClicker : public IModule {
public:

	enum Mode {
		Bypass,
	};

	const char* desc[1]{ "Bypass" };

	NumberValue* cps = new NumberValue("CPS", 13, 1, 20);
	NumberValue* randomDelay = new NumberValue("RandomDelay", 30, 0, 300);
	BoolValue* weaponOnly = new BoolValue("WeaponOnly", true);
	Minecraft mc = Minecraft::getMinecraft();
	ModeValue* mode = new ModeValue("Mode", { Bypass }, desc, Bypass);

	AutoClicker() : IModule("AutoClicker", 0, 0, Category::COMBAT, 0) {
		addValue(BoolType, weaponOnly);
		addValue(IntType, cps);
		addValue(IntType, randomDelay);
		addValue(ListType, mode);
	}

	void onEnable() override {

	}

	void onUpdate() override {

		if (NullCheck()) {
			return;
		}

		if (!mc.getCurrentScreen().isInvalid())
		{
			return;
		}
		if (timer.isDelay(delay)) {
			//重置延迟计时器
			delay = std::round(1000 / cps->getValue());
			int random = getRandomDouble() * randomDelay->getValue();
			delay += random;
			timer.setLastMS();

			doClick();

		}

	}

	void doClick() {
		GameSettings settings = mc.getGameSettings();
		KeyBinding attackKeyBind = settings.getKeyBindAttack();
		KeyBinding rightKeyBind = settings.getKeyBindUseItem();



		if (mode->getValue() == Bypass) {

			if (Mouse::isButtonDown(0)) {

				if (weaponOnly->getValue() && !isPlayerHoldWeapon()) {
					return;
				}

				int attackKeyCode = attackKeyBind.getKeyCode();
				KeyBinding::setKeyBindState(attackKeyCode, true);
				KeyBinding::onTick(attackKeyCode);

				KeyBinding::setKeyBindState(attackKeyCode, false);
				KeyBinding::onTick(attackKeyCode);
				return;
			}



			if (rightKeyBind.isKeyDown()) {
			
				
				KeyBinding::onTick(rightKeyBind.getKeyCode());
				
				//std::cout << "你按了右键" << std::endl;
				
			}

		}




	}

	bool isPlayerHoldWeapon() {
		/*
		 if (mc.thePlayer.getHeldItem() == null) {
            return false;
        }
        final Item item = mc.thePlayer.getHeldItem().getItem();
        return item instanceof ItemSword || item instanceof ItemAxe;
		*/

		EntityPlayerSP player = mc.getPlayer();
		ItemStack stack = player.getHeldItem();
		if (stack.isInvalid()) {
			return false;
		}
		Item item = stack.getItem();
		jclass swordClass = forgeCache.FindClassCache("net/minecraft/item/ItemSword");


		
		//if (g_env->IsInstanceOf(item.obj(), swordClass) || g_env->IsInstanceOf(item.obj(), axeClass)) {
		//	return true;
		//}

		if (g_env->IsInstanceOf(item.obj(), swordClass)) {
			return true;
		}

		return false;
	}

	void LeftClick()
	{
		INPUT    Input = { 0 };
		// left down 
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		Input.mi.time = 0;
		::SendInput(1, &Input, sizeof(INPUT));
		Sleep(1);
		// left up
		::ZeroMemory(&Input, sizeof(INPUT));
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		Input.mi.time = 0;
		::SendInput(1, &Input, sizeof(INPUT));

	}

private:

	TimerUtil timer;
	int delay;

};
#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"

#include "ClientUtils.h"

class TestMod : public IModule {
public:

	BoolValue* wannaWatch = new BoolValue("WannaWatch", false);

	TestMod() : IModule("TestMod", 0, 0, Category::COMBAT, 0) {
		addValue(BoolType, wannaWatch);
	}

	void onUpdate() override {

		if (NullCheck()) {
			return;
		}
		
		Minecraft mc = Minecraft::getMinecraft();
		EntityPlayer player = mc.getPlayer();
		float x = player.getPosX();
		float y = player.getPosY();
		float z = player.getPosZ();

		std::cout << x << ":" << y << ":" << z << std::endl;
		/*std::vector<EntityPlayer> entityPlayer = GetPlayerList();

		
		for (size_t i = 0; i < entityPlayer.size(); i++)
		{
			std::string name = entityPlayer[i].getName();
			float health = entityPlayer[i].getHealth();

			if (wannaWatch->getValue()) {
				printf("Name: %s Health: %2f\n", name.c_str(), health);
			}

		}*/


	}

};
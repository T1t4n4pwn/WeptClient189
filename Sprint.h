#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"

#include "ClientUtils.h"

class Sprint : public IModule {
public:
	Sprint() : IModule("Sprint", 0, 0, Category::MOVEMENT, 0) {
		
	}

	void onUpdate() override {
		
		if (NullCheck()) {
			return;
		}

		Minecraft mc = Minecraft::getMinecraft();
		EntityPlayerSP player = mc.getPlayer();

		if (player.getMoveForward() > 0) {
			player.setSprinting(true);
		}

	}

};
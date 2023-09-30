#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"
#include "ClientUtils.h"
#include "ModuleManager.h"

class Teams : public IModule {
public:

	enum TeamMode {
		IDColor,
	};
	
	const char* desc[1]{ "IDColor" };

	ModeValue* mode = new ModeValue("Mode", { IDColor }, desc, IDColor);

	Teams() : IModule("Teams", 0, 0, Category::MISC, 0) {
		addValue(ListType, mode);
	}

	void onUpdate() override {
		
		if (NullCheck()) {
			return;
		}



	}

	static std::string getEntityIDColor(EntityPlayer entity) {

		std::string name = entity.getDisplayName().getFormattedText();
		if (name.find("§") != std::string::npos) {
			std::string color = name.substr(name.find("§") + 2, 1);
			return std::string("§").append(color);
		}

		return "null";
	}

	static bool isTeam(EntityPlayer entity) {
		//	func_145748_c_ ()Lnet/minecraft/util/text/ITextComponent; getDisplayName
		Minecraft mc = Minecraft::getMinecraft();
		EntityPlayer player = mc.getPlayer();
		ModuleManager* manager = ModuleManager::getInstance();
		IModule* mod = manager->getModuleByName("Teams");
		if (mod == nullptr) {
			return false;
		}

		if (!mod->isEnable()) {
			return false;
		}
		ModeValue* mode = nullptr;
		mode = (ModeValue*)mod->getValueObjByName("Mode");
		if (mode->getValue() == IDColor) {
			
			if (getEntityIDColor(entity).compare(getEntityIDColor(player)) == 0) {
				return true;
			}

		}

		return false;
	}


};
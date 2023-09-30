#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"

#include "ClientUtils.h"
#include "Mouse.h"

#include <wchar.h>

#include "Teams.h"

class AimBot : public IModule {
public:

	enum PriorityMode {
		Closest,
		Health
	};

	enum Mode {
		Rotation,
		MouseMove
	};

	const char* desc[2]{ "Closest", "Health" };
	const char* modeDesc[2]{ "Rotation", "MouseMove" };

	NumberValue* fov = new NumberValue("FOV", 90, 1, 180);
	FloatValue* yaw = new FloatValue("Yaw", 15, 0, 50);
	FloatValue* pitch = new FloatValue("Pitch", 15, 0, 50);
	FloatValue* range = new FloatValue("Range", 4.7, 0.1, 10);

	BoolValue* onClick = new BoolValue("onClick", true);

	ModeValue* priority = new ModeValue("Priority", { Closest, Health }, desc, Closest);

	ModeValue* mode = new ModeValue("Mode", { Rotation, MouseMove }, modeDesc, Rotation);

	BoolValue* debug = new BoolValue("Debug", 0);

	Minecraft mc = Minecraft::getMinecraft();

	AimBot() : IModule("AimBot", 0, 0, Category::COMBAT, 0) {
		addValue(BoolType, onClick);
		addValue(IntType, fov);
		addValue(FloatType, yaw);
		addValue(FloatType, pitch);
		addValue(FloatType, range);
		addValue(ListType, priority);
		addValue(ListType, mode);
		addValue(BoolType, debug);
	}

	EntityPlayer targetEntity = 0;

	void onEnable() override {

		IModule::onEnable();
	}

	boolean isPriority(EntityLivingBase entity) {
		return priority->getValue() == Closest && IsClosest(entity, targetEntity)
			|| priority->getValue() == Health && IsLowHealth(entity, targetEntity);
	}

	void updateTarget() {

		std::vector<EntityPlayer> playerList = GetPlayerList();
		Minecraft mc = Minecraft::getMinecraft();

		for (EntityPlayer player : playerList) {

			if (player.isInvalid()) {
				continue;
			}

			if (player.isInvisible()) {
				continue;
			}

			if (!player.isEntityAlive()) {
				continue;
			}

			if (g_env->IsSameObject(player.obj(), mc.getPlayer().obj())) {
				continue;
			}

			if (!IsInAttackFOV(player, fov->getValue())) {
				continue;
			}

			if (!IsInAttackRange(player, range->getValue())) {
				continue;
			}

			if (!isPriority(player)) {
				continue;
			}

			if (player.getHeight() <= 0.5) {
				continue;
			}

			if (player.isPlayerSleeping()) {
				continue;
			}

			if (Teams::isTeam(player)) {
				continue;
			}

			targetEntity = player;
			return;

		}

	}

	void onUpdate() override {

		if (NullCheck()) {
			return;
		}

		if (!mc.getCurrentScreen().isInvalid())
		{
			return;
		}

		updateTarget();

		if (onClick->getValue() && !(Mouse::isButtonDown(0) || KeyBoard::IsKeyPressed(VK_LBUTTON))) {
			return;
		}

		if (debug->getValue() && !targetEntity.isInvalid()) {
			printf("Name: %s | IsEntityAlive: %d | isInvisible: %d | tickExisted: %d\n", targetEntity.getName().c_str(), targetEntity.isEntityAlive(), targetEntity.isInvisible(), targetEntity.getTickExisted());
		}

		if (mode->getValue() == Rotation) {
			AssistFaceEntity(targetEntity, yaw->getValue(), pitch->getValue());
		}
		else if (mode->getValue() == MouseMove) {
			MoveMouseToEntity(targetEntity, yaw->getValue(), pitch->getValue());
		}

		targetEntity = 0;

	}

	void onDisable() override {
		targetEntity = 0;
		IModule::onDisable();
	}

};
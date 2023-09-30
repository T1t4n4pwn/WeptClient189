#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"

#include "ClientUtils.h"
#include "Mouse.h"

#include <wchar.h>
#include "Math.h"
#include "Teams.h"
class AimBot : public IModule {
public:

	

	//const char* desc[2]{ "Closest", "Health" };
	//const char* modeDesc[2]{ "Rotation", "MouseMove" };

	//NumberValue* fov = new NumberValue("FOV", 90, 1, 180);
	//FloatValue* yaw = new FloatValue("Yaw", 15, 0, 50);
	//FloatValue* pitch = new FloatValue("Pitch", 15, 0, 50);
	//FloatValue* range = new FloatValue("Range", 4.7, 0.1, 10);

	//BoolValue* onClick = new BoolValue("onClick", true);

	//ModeValue* priority = new ModeValue("Priority", { Closest, Health }, desc, Closest);

	//ModeValue* mode = new ModeValue("Mode", { Rotation, MouseMove }, modeDesc, Rotation);

	//BoolValue* debug = new BoolValue("Debug", 0);
	FloatValue* FovValue = new FloatValue("Fov", 35.0f,	 1, 360);
	FloatValue* AimDistanceValue = new FloatValue("Aim Distance", 4.f, 1.0f, 8.0f);
	FloatValue* SmoothValue = new FloatValue("Smooth", 15.f, 1.0f, 90.0f);
	FloatValue* AdaptiveOffsetValue = new FloatValue("Adaptive Offset", 3, 0.1f, 15.f);
	FloatValue* RandomYawValue = new FloatValue("RandomYaw Offset", 2, 0.0f, 10.0f);
	FloatValue* RandomPitchValue = new FloatValue("RandomPitch Offset", .075f, 0.0f, 1.0f);
	BoolValue* VisibilityCheckValue = new BoolValue("VisibilityCheck", true);
	BoolValue* AimKeyValue = new BoolValue("AimKey", true);
	BoolValue* AdaptiveValue = new BoolValue("Adaptive", true);
	BoolValue* AimAssistFeedbackValue = new BoolValue("AimAssistFeedback", true);
	BoolValue* FovCircleValue = new BoolValue("FovCircle", true);
	ModeValue* TargetPriorityValue = new ModeValue("TargetPriority", { Distance , Health , Crosshair }, targetPriorityList, Crosshair);
	Minecraft mc = Minecraft::getMinecraft();

	AimBot() : IModule("AimBot", 0, 0, Category::COMBAT, 0) {
		this->addValue(FloatType, FovValue);
		this->addValue(FloatType, AimDistanceValue);
		this->addValue(FloatType, SmoothValue);
		this->addValue(FloatType, AdaptiveOffsetValue);
		this->addValue(FloatType, RandomYawValue);
		this->addValue(FloatType, RandomPitchValue);
		this->addValue(BoolType, VisibilityCheckValue);
		this->addValue(BoolType, AimKeyValue);
		this->addValue(BoolType, AdaptiveValue);
		this->addValue(BoolType, AimAssistFeedbackValue);
		this->addValue(BoolType, FovCircleValue);
		this->addValue(ListType, TargetPriorityValue);
	}
	Vector3 data;
	Vector3 renderData;
	bool pitchInfluenced = false;

	enum TARGETMODE {
		Distance,
		Health,
		Crosshair
	};
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };

	void onEnable() override {

		IModule::onEnable();
	}

	
	
	void onUpdate() override {

		auto aimDistance = AimDistanceValue->getValue();
		auto aimKey = AimKeyValue->getValue();
		auto fov = FovValue->getValue();
		auto randomYaw = RandomYawValue->getValue();
		auto randomPitch = RandomPitchValue->getValue();
		auto adaptive = AdaptiveValue->getValue();
		auto adaptiveOffset = AdaptiveOffsetValue->getValue();
		auto smooth = SmoothValue->getValue();
		auto fovCircle = FovCircleValue->getValue();
		if (!this->isEnable()) return;
		if (NullCheck()) {
			return;
		}

		if (!mc.getCurrentScreen().isInvalid())
		{
			return;
		}
		if (Menu::Open) return;

		if ((aimKey && (!GetAsyncKeyState(VK_LBUTTON) && 1))) {
			this->data = Vector3();
			return;
		}

		auto thePlayer = mc.getPlayer();


		Vector3 pos = thePlayer.getPos();
		Vector3 headPos = thePlayer.getEyePos();
		Vector2 currentLookAngles = thePlayer.getAngles();



		EntityPlayer target;
		float finalDist = FLT_MAX;
		float finalDiff = 370;
		float finalHealth = FLT_MAX;

		float realAimDistance = aimDistance;

		// The code from here and below is kind of dog water, however it does the job.
		// The real math for the aim angles if you're interested is located in Math::getAngles()
		// fusion/src/base/util/math/Math.cpp
		auto randomFloat = [](float min, float max)
		{
			float f = (float)rand() / RAND_MAX;
			return min + f * (max - min);
		};


		for (EntityPlayer player : GetPlayerList())
		{
			if (!player.isInvalid()) continue;


			if (ModuleManager::getInstance()->getModuleByName("Team")->isEnable() && Teams::isTeam(player)) {
				continue;
			}

			if (player.getName().length() < 0) return;

			if (!g_env->IsSameObject(thePlayer.obj(), player.obj())) {
				if (!thePlayer.canEntityBeSeen(player.obj())) continue;

				float playerHeight = target.getHeight() - 0.1;


				Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.getPos() + Vector3(0, playerHeight, 0)).Invert());
				if (difference.X < 0) difference.X = -difference.X;
				if (difference.Y < 0) difference.Y = -difference.Y;
				Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.getPos()).Invert());
				if (differenceFoot.X < 0) differenceFoot.X = -differenceFoot.X;
				if (differenceFoot.X < 0) differenceFoot.Y = -differenceFoot.Y;

				float angleYaw = currentLookAngles.X - difference.X;

				Vector3 diff = thePlayer.getPos() - player.getPos();
				float dist = sqrt(pow(diff.X, 2) + pow(diff.Y, 2) + pow(diff.Z, 2));

				if (abs(difference.X <= fov) && dist <= realAimDistance)
				{
					float health = player.getHealth();
					switch (this->TargetPriorityValue->getValue())
					{
					case 1:
						if (finalHealth > health)
						{
							target = player;
							finalHealth = health;
						}
						break;

					case 2:
						if (finalDiff > difference.X)
						{
							target = player;
							finalDiff = difference.X;
						}
						break;
					default:
						if (finalDist > dist)
						{
							target = player;
							finalDist = (float)dist;
						}
					}
				}
			}
		}

		if (!target.obj()) {
			Vector3 null;
			data = null;
			return;
		}


		Vector3 ePos = target.getPos();
		Vector3 eLastPos = Vector3{ 
			(float)target.getLastTickPosX(),(float)target.getLastTickPosY(),(float)target.getLastTickPosZ() };

		float eHeight = target.getHeight() - 0.1;
		Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
		Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


		Vector2 anglesFoot = Math::getAngles(headPos, ePos);
		Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

		Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
		Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

		float offset = randomFloat(-randomYaw, randomYaw);
		if (adaptive) {
			if ((GetAsyncKeyState('D') & 0x8000) && !(GetAsyncKeyState('A') & 0x8000)) {
				offset -= adaptiveOffset;
			}

			if ((GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000)) {
				offset += adaptiveOffset;
			}
		}

		float targetYaw = currentLookAngles.X + ((difference.X + offset) / smooth);

		Vector3 renderPos = mc.getRenderManager().getRenderPos();
		float renderPartialTicks = mc.getTimer().getRenderPartialTicks();

		if (currentLookAngles.Y > anglesFoot.Y || currentLookAngles.Y < anglesHead.Y) {
			float targetPitchFoot = currentLookAngles.Y + (differenceFoot.Y / smooth);
			float targetPitchHead = currentLookAngles.Y + (difference.Y / smooth);

			float diffFoot = currentLookAngles.Y - targetPitchFoot;
			float diffHead = currentLookAngles.Y - targetPitchHead;
			diffFoot = diffFoot < 0 ? -diffFoot : diffFoot;
			diffHead = diffHead < 0 ? -diffHead : diffHead;

			float targetPitch;
			if (diffFoot > diffHead)
			{
				targetPitch = targetPitchHead;
				data = renderPos - Vector3(0, 0.21, 0) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
			}
			else
			{
				targetPitch = targetPitchFoot;
				data = renderPos - Vector3(0, 0.23, 0) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			}
			pitchInfluenced = true;
			targetPitch += randomFloat(-randomPitch, randomPitch);
			thePlayer.setAngles(Vector2(targetYaw, targetPitch));
		}
		else {
			data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			pitchInfluenced = false;
			thePlayer.setAngles(Vector2(targetYaw, currentLookAngles.Y + randomFloat(-randomPitch, randomPitch)));
		}

	}

	void onDisable() override {
		IModule::onDisable();
	}

};
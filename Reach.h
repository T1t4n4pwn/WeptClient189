#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"

#include "AxisAlignedBB.h"

#include "ClientUtils.h"
#include "TimerUtil.h"
class Reach : public IModule {
public:

	TimerUtil timer;
	FloatValue* range = new FloatValue("Range", 0.5, 0.1, 2);

	Reach() : IModule("Reach", 0, 0, Category::COMBAT, 0) {
		addValue(FloatType, range);
	}

	void onUpdate() {
		
		if (NullCheck()) {
			return;
		}

		Minecraft mc = Minecraft::getMinecraft();
		EntityPlayer player = mc.getPlayer();
		if (!timer.isDelay(20)) {
			return;
		}

		timer.setLastMS();

		float distance = range->getValue();

		std::vector<EntityPlayer> players = GetPlayerList();
		Vector2 localPlayerAngle(player.getRotationYaw(), player.getRotationPitch());
		Vector3 localPlayerPos(player.getPosX(), player.getPosY(), player.getPosZ());

		for (EntityPlayer& target : players)
		{
			if (player.isInvalid()) {
				continue;
			}

			if (g_env->IsSameObject(target.obj(), player.obj()))
			{
				continue;
			}

			AxisAlignedBB targetAABB = target.getEntityBoundingBox();
			BoundingBox targetBB = targetAABB.getBoundingBox();

			

			float hypothenuseDistance = (float)sqrt(pow((localPlayerPos - target.getPos()).X, 2) + pow((localPlayerPos - target.getPos()).Z, 2));

			if (distance > hypothenuseDistance)
				distance -= hypothenuseDistance;

			float difference = wrapDegrees(localPlayerAngle.X - getAngles(localPlayerPos, target.getPos()).X);

			if (std::abs(difference) > 180.0f)
				continue;

			float cos = std::cos(degToRadiants(getAngles(localPlayerPos, target.getPos()).X + 90.0f));
			float sin = std::sin(degToRadiants(getAngles(localPlayerPos, target.getPos()).X + 90.0f));
			float cosPitch = std::cos(degToRadiants(getAngles(localPlayerPos, target.getPos()).Y));
			float sinPitch = std::sin(degToRadiants(getAngles(localPlayerPos, target.getPos()).Y));

			float x = target.getPos().X - (cos * distance * cosPitch);
			float y = target.getPos().Y + (distance * sinPitch);
			float z = target.getPos().Z - (sin * distance * cosPitch);

			float entityWidth = 0.6f;
			float bbWidth = entityWidth / 2.0f;

			BoundingBox newBB{
				(double)x - bbWidth,
				(double)y,
				//targetBB.minY,
				(double)z - bbWidth,

				(double)x + bbWidth,
				(double)y + 2,
				//targetBB.maxY,
				(double)z + bbWidth
			};
			
			targetAABB.setBoundingBox(newBB);

		}

	}

};
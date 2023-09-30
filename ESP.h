#pragma once
#include "globals.h"
#include "Module.h"
#include "Minecraft.h"
#include "ClientUtils.h"
#include "ActiveRenderInfo.h"

#include <iostream>

#include <mutex>
#include <vector>
#include <deque>

class ESP : public IModule {
public:

	typedef struct RenderRequest {
		ImVec2 Pos;
		ImVec2 Rect;
		ImColor Color;
		int thickness;

		bool Valid;
		
		BoundingBox boundingBox;

		Vector4 w2sbb;

		RenderRequest& operator=(const RenderRequest& obj) {
			Pos = obj.Pos;
			Rect = obj.Rect;
			Color = obj.Color;
			thickness = obj.thickness;
			Valid = obj.Valid;

			boundingBox.minX = obj.boundingBox.minX;
			boundingBox.minY = obj.boundingBox.minY;
			boundingBox.minZ = obj.boundingBox.minZ;

			boundingBox.maxX = obj.boundingBox.maxX;
			boundingBox.maxY = obj.boundingBox.maxY;
			boundingBox.maxZ = obj.boundingBox.maxZ;

			w2sbb = obj.w2sbb;

			return *this;
		}
	};

	Minecraft mc = Minecraft::getMinecraft();
	
	FloatValue* offsetYaw = new FloatValue("OffsetYaw", 0, -100, 100);
	FloatValue* offsetPitch = new FloatValue("offsetPitch", 0, -100, 100);
	NumberValue* biliValue = new NumberValue("biliValue", 10, -100, 100);

	ESP() : IModule("ESP", 0, 0, Category::RENDER, 0) {
		requests.resize(100);
		addValue(FloatType, offsetYaw);
		addValue(FloatType, offsetPitch);
		addValue(IntType, biliValue);
	}

	void onUpdate() override {

		if (NullCheck()) {
			return;
		}
		
		std::vector<EntityPlayer> playerList = GetPlayerList();
		if (playerList.size() > requests.size()) {
			requests.resize(playerList.size());
		}
		for (int i = 0; i < playerList.size(); i++)
		{
			EntityPlayer entity = playerList[i];
			if (entity.isInvalid()) {
				requests[i].Valid = false;
				continue;
			}

			if (entity.isInvisible()) {
				requests[i].Valid = false;
				continue;
			}

			if (!entity.isEntityAlive()) {
				requests[i].Valid = false;
				continue;
			}

			if (g_env->IsSameObject(entity.obj(), mc.getPlayer().obj())) {
				requests[i].Valid = false;
				continue;
			}

			EntityPlayer player = mc.getPlayer();

			float distance = entity.getDistanceToEntity(player);

			if (distance == 0 || distance > 200) {
				requests[i].Valid = false;
				continue;
			}

			Vector3 localPlayerPos(player.getPosX(), player.getPosY(), player.getPosZ());
			float renderPartialTicks = mc.getTimer().getRenderPartialTicks();

			RenderManager renderManager = mc.getRenderManager();

			Vector3 renderPos(renderManager.getRenderPosX(), renderManager.getRenderPosY(), renderManager.getRenderPosZ());
			
			Vector3 vecOrign;
			Vector3 localVecOrign;
			vecOrign.X = renderPos.X - entity.getLastTickPosX() + (entity.getLastTickPosX() - entity.getPosX()) * renderPartialTicks;
			vecOrign.Y = renderPos.Y - entity.getLastTickPosY() + (entity.getLastTickPosY() - entity.getPosY()) * renderPartialTicks;
			vecOrign.Z = renderPos.Z - entity.getLastTickPosZ() + (entity.getLastTickPosZ() - entity.getPosZ()) * renderPartialTicks;
			
			localVecOrign.X = renderPos.X - player.getLastTickPosX() + (player.getLastTickPosX() - player.getPosX()) * renderPartialTicks;
			localVecOrign.Y = renderPos.Y - player.getLastTickPosY() + (player.getLastTickPosY() - player.getPosY()) * renderPartialTicks;
			localVecOrign.Z = renderPos.Z - player.getLastTickPosZ() + (player.getLastTickPosZ() - player.getPosZ()) * renderPartialTicks;

			vecOrign = vecOrign - localVecOrign;
			
			Vector2 screenPos(0, 0);

			Matrix modelMatrix = ActiveRenderInfo::getModelView();
			Matrix projectionMatrix = ActiveRenderInfo::getProjection();


			/*if(World2Screen(vecOrign, modelMatrix, projectionMatrix, gui.Window.Width, gui.Window.Height, screenPos)){


				float bili = biliValue->getValue() / distance;

				float width = bili * 100;
				float height = bili * 200;
				RenderRequest rectReq;
				rectReq.Pos = ImVec2(screenPos.X - offsetYaw->getValue(), screenPos.Y - offsetPitch->getValue());
				rectReq.Rect = ImVec2(width, height);
				rectReq.Color = ImColor(0, 255, 0);
				rectReq.thickness = 2;

				requests[i] = rectReq;

			}
			else {
				requests[i].Valid = false;
			}*/

			
		}


	}

	void onRender() override {

		
		for (size_t i = 0; i < requests.size(); i++)
		{
			if (!requests[i].Valid) {
				continue;
			}

			
			//gui.Rectangle(requests[i].Pos, requests[i].Rect.x, requests[i].Rect.y, requests[i].Color, requests[i].thickness);
		}

	}

private:
	
	std::vector<RenderRequest> requests;
	
};
#include "ClientUtils.h"
#include <math.h>

#include <Windows.h>

std::vector<EntityPlayer> GetPlayerList()
{
	std::vector<EntityPlayer> playerList;

	Minecraft mc = Minecraft::getMinecraft();
	if (mc.isInvalid()) {
		return playerList;
	}

	WorldClient world = mc.getWorld();
	if (world.isInvalid()) {
		return playerList;
	}

	std::vector<Entity> entityList = world.getLoadedEntityList();

	for (Entity entity : entityList)
	{
		if (g_env->IsInstanceOf(entity.obj(), forgeCache.FindClassCache("net/minecraft/entity/player/EntityPlayer"))) {

			EntityPlayer player(entity.obj());

			playerList.emplace_back(player);
		}
	}

	return playerList;
}

bool NullCheck()
{
	Minecraft mc = Minecraft::getMinecraft();
	if (mc.isInvalid()) {
		return true;
	}

	EntityPlayerSP localPlayer = mc.getPlayer();
	if (localPlayer.isInvalid()) {
		return true;
	}
	return false;
}

float wrapDegrees(float p_76142_0_) {
	p_76142_0_ = fmod(p_76142_0_, 360.0);

	if (p_76142_0_ >= 180.0F) {
		p_76142_0_ -= 360.0F;
	}

	if (p_76142_0_ < -180.0F) {
		p_76142_0_ += 360.0F;
	}

	return p_76142_0_;
}

float degToRadiants(float x)
{
	return x * 3.141592653589793 / 180.f;
}

float radiantsToDeg(float x)
{
	return x * 180.f / 3.141592653589793;
}

Vector2 getAngles(Vector3 pos, Vector3 pos1)
{
	double d_x = pos1.X - pos.X;
	double d_y = pos1.Y - pos.Y;
	double d_z = pos1.Z - pos.Z;

	double hypothenuse = sqrt(d_x * d_x + d_z * d_z);
	float yaw = radiantsToDeg(atan2(d_z, d_x)) - 90.f;
	float pitch = radiantsToDeg(-atan2(d_y, hypothenuse));

	return Vector2(yaw, pitch);
}

std::vector<float> GetRotationsNeeded(EntityPlayer entity)
{
	std::vector<float> result;

	if (entity.isInvalid()) {
		return result;
	}

	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayerSP player = mc.getPlayer();

	double diffX = entity.getPosX() - player.getPosX();
	double diffZ = entity.getPosZ() - player.getPosZ();
	double diffY = entity.getPosY() + entity.getEyeHeight() - (player.getPosY() + player.getEyeHeight());

	double dist = sqrt(diffX * diffX + diffZ * diffZ);

	float yaw = (float)(atan2(diffZ, diffX) * 180.0 / 3.141592653589793) - 90.0F;
	float pitch = (float)-(atan2(diffY, dist) * 180.0 / 3.141592653589793);

	result.push_back(player.getRotationYaw() + wrapDegrees(yaw - player.getRotationYaw()));
	result.push_back(player.getRotationPitch() + wrapDegrees(pitch - player.getRotationPitch()));

	return result;
}

int GetDistanceFromMouse(EntityPlayer entity)
{
	std::vector<float> neededRotations = GetRotationsNeeded(entity);

	if (neededRotations.size() == 2) {

		Minecraft mc = Minecraft::getMinecraft();
		EntityPlayer player = mc.getPlayer();

		float neededYaw = player.getRotationYaw() - neededRotations[0];
		float neededPitch = player.getRotationPitch() - neededRotations[1];
		float distanceFromMouse = sqrt(neededYaw * neededYaw + neededPitch * neededPitch * 2.0f);

		return (int)distanceFromMouse;
	}

	return -1;
}

bool IsInAttackFOV(EntityPlayer entity, int fov)
{
	return GetDistanceFromMouse(entity) <= fov;
}

bool IsInAttackRange(EntityLivingBase entity, float range)
{
	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayerSP player = mc.getPlayer();

	return entity.getDistanceToEntity(player) <= range;
}

bool IsClosest(EntityLivingBase entity, EntityLivingBase entityPriority)
{
	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayerSP player = mc.getPlayer();

	return entityPriority.isInvalid() || player.getDistanceToEntity(entity) < player.getDistanceToEntity(entityPriority);
}

bool IsLowHealth(EntityLivingBase entity, EntityLivingBase entityPriority)
{
	return entityPriority.isInvalid() || entity.getHealth() < entityPriority.getHealth();
}

float updateRotation(float current, float target, float speed)
{
	float var4 = wrapDegrees(target - current);
	if (var4 > speed) {
		var4 = speed;
	}
	if (var4 < -speed) {
		var4 = -speed;
	}
	return current + var4;
}

void AssistFaceEntity(EntityPlayer entity, float yaw, float pitch)
{
	if (entity.isInvalid()) {
		return;
	}

	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayerSP player = mc.getPlayer();

	double diffX = entity.getPosX() - player.getPosX();
	double diffZ = entity.getPosZ() - player.getPosZ();
	double yDifference;

	yDifference = entity.getPosY() + entity.getEyeHeight() - (
		player.getPosY() + player.getEyeHeight());



	double dist = sqrt(diffX * diffX + diffZ * diffZ);
	float rotationYaw = (float)(atan2(diffZ, diffX) * 180.0 / 3.14159265358979323846) - 90.0F;
	float rotationPitch = (float)-(atan2(yDifference, dist) * 180.0 / 3.14159265358979323846);

	if (yaw > 0) {
		player.setRotationYaw(updateRotation(player.getRotationYaw(), rotationYaw, yaw / 4));
		
	}
	if (pitch > 0) {
		player.setRotationPitch(updateRotation(player.getRotationPitch(), rotationPitch, pitch / 4));
	}
}

void MoveMouseToEntity(EntityPlayer entity, float yawSpeed, float pitchSpeed) {

	if (entity.isInvalid()) {
		return;
	}

	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayerSP player = mc.getPlayer();

	double diffX = entity.getPosX() - player.getPosX();
	double diffZ = entity.getPosZ() - player.getPosZ();
	double yDifference;

	yDifference = entity.getPosY() + entity.getEyeHeight() - (
		player.getPosY() + player.getEyeHeight());

	double dist = sqrt(diffX * diffX + diffZ * diffZ);
	float rotationYaw = (float)(atan2(diffZ, diffX) * 180.0 / 3.14159265358979323846) - 90.0F;
	float rotationPitch = (float)-(atan2(yDifference, dist) * 180.0 / 3.14159265358979323846);

	POINT cursor;
	GetCursorPos(&cursor);

	float yawDiff = wrapDegrees(player.getRotationYaw()) - wrapDegrees(rotationYaw);
	float pitchDiff = wrapDegrees(player.getRotationPitch()) - wrapDegrees(rotationPitch);

	//mouse_event(MOUSEEVENTF_MOVE, -wrapDegrees(yawDiff), -wrapDegrees(pitchDiff), 0, 0);
	mouse_event(MOUSEEVENTF_MOVE, updateRotation(0, -wrapDegrees(yawDiff), yawSpeed / 4), updateRotation (0, -wrapDegrees(pitchDiff), pitchSpeed / 4), 0, 0);
	
}


double getRandomDouble()
{
	std::random_device rd; // 使用随机设备获取种子
	std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
	std::uniform_real_distribution<double> dis(0.0, 1.0); // 使用均匀分布在0.0到1.0之间

	return dis(gen);
}


Vector4 Multiply(Vector4 vec, Matrix matrix)
{
	float* mat = (float*)matrix.Data;
	return Vector4(
		vec.X * mat[0] + vec.Y * mat[4] + vec.Z * mat[8] + vec.W * mat[12],
		vec.X * mat[1] + vec.Y * mat[5] + vec.Z * mat[9] + vec.W * mat[13],
		vec.X * mat[2] + vec.Y * mat[6] + vec.Z * mat[10] + vec.W * mat[14],
		vec.X * mat[3] + vec.Y * mat[7] + vec.Z * mat[11] + vec.W * mat[15]
	);
}

bool World2Screen(const Vector3& position, const Matrix& modelview_matrix, const Matrix& projection_matrix, int screen_width, int screen_height, Vector2& screenPos)
{

	Vector4 clipSpacePos = Multiply(Multiply(Vector4(position.X, position.Y, position.Z, 1.0f), modelview_matrix), projection_matrix);

	Vector3 ndcSpacePos = Vector3(clipSpacePos.X / clipSpacePos.W, clipSpacePos.Y / clipSpacePos.W, clipSpacePos.Z / clipSpacePos.W);

	// nPlane = -1, fPlane = 1
	if (ndcSpacePos.Z <= 1.0 || ndcSpacePos.Z >= 1.15)
	{
		return false;
	}
	Minecraft mc = Minecraft::getMinecraft();
	EntityPlayer player = mc.getPlayer();

	screenPos.X = ((ndcSpacePos.X + 1.0f) / 2.0f) * screen_width;
	screenPos.Y = ((1.0f - ndcSpacePos.Y) / 2.0f) * screen_height;

	return true;
}

bool WorldToScreen_NoMatrix(Vector2& screenPos, float  水平角度差, float 高低角度差, int screen_width, int screen_height)
{


	float 高低可视角度 = (float)((double)atan2(screen_height, screen_width) * 180 / 3.14159265358979323846);
	if (fabs(水平角度差) > 45 || fabs(高低角度差) > 高低可视角度)
	{
		return false;// 不在屏幕范围内
	}
	
	int 水平差 = (int)(tan(水平角度差 * 3.14159265358979323846 / 180) * ((screen_width) / 2));
	screenPos.X = (float)(screen_width / 2 + 水平差);

	int 高度差 = (int)(tan(高低角度差 * 3.14159265358979323846 / 180) * ((screen_width) / 2));
	screenPos.Y = (float)(screen_height / 2 + 高度差);

	return true;

}



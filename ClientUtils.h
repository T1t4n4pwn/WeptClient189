#pragma once
#include "globals.h"
#include "Minecraft.h"
#include "EntityPlayer.h"

#include "Structures.h"

#include <vector>
#include <random>

std::vector<EntityPlayer> GetPlayerList();

bool NullCheck();

std::vector<float> GetRotationsNeeded(EntityPlayer entity);

int GetDistanceFromMouse(EntityPlayer entity);

bool IsInAttackFOV(EntityPlayer entity, int fov);

bool IsInAttackRange(EntityLivingBase entity, float range);

bool IsClosest(EntityLivingBase entity, EntityLivingBase entityPriority);

bool IsLowHealth(EntityLivingBase entity, EntityLivingBase entityPriority);

float wrapDegrees(float p_76142_0_);

float degToRadiants(float x);

float radiantsToDeg(float x);

Vector2 getAngles(Vector3 pos, Vector3 pos1);

float updateRotation(float p_70663_1_, float p_70663_2_, float p_70663_3_);

void AssistFaceEntity(EntityPlayer entity, float yaw, float pitch);

void MoveMouseToEntity(EntityPlayer entity, float yawSpeed, float pitchSpeed);

double getRandomDouble();

Vector4 Multiply(Vector4 vec, Matrix matrix);

bool World2Screen(const Vector3& position, const Matrix& modelview_matrix, const Matrix& projection_matrix, int screen_width, int screen_height, Vector2& screenPos);
bool WorldToScreen_NoMatrix(Vector2& screenPos, float  水平角度差, float 高低角度差, int screen_width, int screen_height);


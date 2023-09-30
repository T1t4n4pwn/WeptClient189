#include "Math.h"

#include <cmath>

float Math::wrapAngleTo180(float angle)
{
	angle = std::fmod(angle, 360.0f);
	if (angle >= 180.0f) {
		angle -= 360.0f;
	}

	if (angle < -180.0f) {
		angle += 360.0f;
	}

	return angle;
}

Vector2 Math::vec_wrapAngleTo180(Vector2 angle)
{
	return Vector2{
		wrapAngleTo180(angle.X),
		wrapAngleTo180(angle.Y),
	};
}

float Math::coterminal(float angle) {
	return std::fmod(angle, 180) < 0 ? angle + 170 : angle;
}


float Math::magnitude(Vector3 v)
{
	return sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

Vector3 Math::crossProduct(Vector3 v1, Vector3 v2)
{
	return Vector3{
		v1.Y * v2.Z - v1.Z * v2.Y,
		v1.Z * v2.X - v1.X * v2.Z,
		v1.X * v2.Y - v1.Y * v2.X
	};
}

float Math::shortestDistance(Vector3 p, Vector3 a, Vector3 b)
{

	Vector3 ab{ b.X - a.X, b.Y - a.Y, b.Z - a.Z };
	Vector3 cp = crossProduct(
		Vector3{ p.X - a.X, p.Y - a.Y, p.Z - a.Z },
		ab
	);

	return magnitude(cp) / magnitude(ab);
}

Vector2 Math::getAngles(Vector3 pos, Vector3 pos1)
{
	double d_x = pos1.X - pos.X;
	double d_y = pos1.Y - pos.Y;
	double d_Z = pos1.Z - pos.Z;

	double hypothenuse = sqrt(d_x * d_x + d_Z * d_Z);
	float yaw = radiantsToDeg(atan2(d_Z, d_x)) - 90.f;
	float pitch = radiantsToDeg(-atan2(d_y, hypothenuse));

	return Vector2(yaw, pitch);
}

float Math::radiantsToDeg(float x)
{
	return x * 180.f / PI;
}

float Math::degToRadiants(float x)
{
	return x * PI / 180.f;
}


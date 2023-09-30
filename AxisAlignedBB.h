#pragma once
#include "Object.h"
#include "ForgeCache.h"

struct BoundingBox {
	double minX;
	double minY;
	double minZ;

	double maxX;
	double maxY;
	double maxZ;
};

class AxisAlignedBB : Object {
	using Object::Object;
public:
	double getMinX() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minX");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getMinY() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minY");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getMinZ() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minZ");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getMaxX() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxX");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getMaxY() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxY");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	double getMaxZ() {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxZ");
		if (fieldID == 0) {
			return 0;
		}

		double value = g_env->GetDoubleField(m_instance, fieldID);

		return value;
	}

	void setMinX(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minX");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	void setMinY(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minY");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	void setMinZ(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::minZ");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	void setMaxX(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxX");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	void setMaxY(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxY");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	void setMaxZ(double value) {
		jfieldID fieldID = forgeCache.FindFieldCache("AxisAlignedBB::maxZ");
		if (fieldID == 0) {
			return;
		}

		g_env->SetDoubleField(m_instance, fieldID, value);
	}

	BoundingBox getBoundingBox() {

		return BoundingBox{ getMinX(), getMinY(), getMinZ(), getMaxX(), getMaxY(), getMaxZ() };
	}

	void setBoundingBox(BoundingBox newBoundingBox) {
		setMinX(newBoundingBox.minX);
		setMinY(newBoundingBox.minY);
		setMinZ(newBoundingBox.minZ);

		setMaxX(newBoundingBox.maxX);
		setMaxY(newBoundingBox.maxY);
		setMaxZ(newBoundingBox.maxZ);
	}

};
#pragma once
#include "globals.h"

class Object {

public:

	Object() : m_instance(0) {}

	Object(const jobject instance) {
		m_instance = g_env->NewGlobalRef(instance);
	}

	Object(const Object& obj) {
		m_instance = g_env->NewGlobalRef(obj.m_instance);
	}

	Object& operator=(const Object& obj) {
		m_instance = g_env->NewGlobalRef(obj.m_instance);
		return *this;
	}

	~Object() {
		if (!isInvalid()) {
			g_env->DeleteGlobalRef(m_instance);
		}
	}

	jobject obj() const {
		return m_instance;
	}

	bool isInvalid() const {
		return m_instance == 0 || m_instance == (jobject)0xcdcdcdcd || g_env->IsSameObject(m_instance, 0);
	}

protected:

	jobject m_instance;

};
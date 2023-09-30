#pragma once
#include <iostream>
#include <chrono>

class TimerUtil {
	
	long long getCurrentTimestampMillis() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	}

public:

	bool isDelay(long long delay) {
		return (getCurrentTimestampMillis() - lastMS) >= delay;
	}

	void setLastMS() {
		lastMS = getCurrentTimestampMillis();
	}

private:

	long long lastMS;

};
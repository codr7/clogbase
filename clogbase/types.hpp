#pragma once

#include <chrono>

namespace clogbase {
	using namespace std::chrono;

	using Clock = system_clock;
	using Time = Clock::time_point;
}
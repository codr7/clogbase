#pragma once

#include <chrono>
#include "tcolumn.hpp"

namespace clogbase {
	using namespace std::chrono;
	using Time = system_clock::time_point;

	class TimeColumn : public TColumn<Time> {
	public:
		TimeColumn(const string& name);
	};
}
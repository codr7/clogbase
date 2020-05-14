#pragma once

#include "tcolumn.hpp"
#include "types.hpp"

namespace clogbase {
	class TimeColumn : public TColumn<Time> {
	public:
		TimeColumn(const string& name);
	};
}
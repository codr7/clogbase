#pragma once

#include "tcolumn.hpp"

namespace clogbase {
	class Int64Column : public TColumn<int64_t> {
	public:
		Int64Column(const string &name);
	};
}
#pragma once

#include "tcolumn.hpp"

namespace clogbase {
	class StringColumn : public TColumn<string> {
	public:
		StringColumn(const string &name);
	};
}
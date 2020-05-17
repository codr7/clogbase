#pragma once

#include "tcolumn.hpp"

namespace clogbase {
	const ColumnType<string>& string_type();

	class StringColumn : public TColumn<string> {
	public:
		StringColumn(const string &name);
	};
}
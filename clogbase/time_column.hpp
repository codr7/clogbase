#pragma once

#include "tcolumn.hpp"
#include "types.hpp"

namespace clogbase {
	const ColumnType<Time> &time_type();

	class TimeColumn : public TColumn<Time> {
	public:
		TimeColumn(const string& name);
	};
}
#pragma once

#include "tcolumn.hpp"
#include "types.hpp"

namespace clogbase {
	class TimeType : public ColumnType<Time> {
	public:
		Time load_value(File& in) const;
		void store_value(const Time& value, File& out) const;
	};

	const TimeType &time_type();

	class TimeColumn : public TColumn<Time> {
	public:
		TimeColumn(const string& name);
	};
}
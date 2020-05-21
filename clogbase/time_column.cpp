#include "time_column.hpp"

namespace clogbase {
	Time TimeType::load_value(File& in) const {
		return in.read_time();
	}

	void TimeType::store_value(const Time& value, File& out) const {
		out.write_time(value);
	}

	const TimeType& time_type() {
		static TimeType type;
		return type;
	}

	TimeColumn::TimeColumn(const string& name) : TColumn<Time>(name, time_type()) {
	}
}
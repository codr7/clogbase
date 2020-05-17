#include "time_column.hpp"

namespace clogbase {
	const ColumnType<Time>& time_type() {
		static ColumnType<Time> type;
		return type;
	}

	TimeColumn::TimeColumn(const string& name) : TColumn<Time>(name, time_type()) {
	}
}
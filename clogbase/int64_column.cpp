#include "int64_column.hpp"

namespace clogbase {
	const ColumnType<int64_t>& int64_type() {
		static ColumnType<int64_t> type;
		return type;
	}

	Int64Column::Int64Column(const string &name) : TColumn<int64_t>(name, int64_type()) {
	}

	Int64SetColumn::Int64SetColumn(const string& name) : SetColumn<int64_t>(name, int64_type()) {
	}
}
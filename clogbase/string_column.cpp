#include "string_column.hpp"

namespace clogbase {
	const ColumnType<string>& string_type() {
		static BasicType<string> type;
		return type;
	}

	StringColumn::StringColumn(const string& name) : TColumn<string>(name, string_type()) {
	}
}
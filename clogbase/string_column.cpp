#include "string_column.hpp"

namespace clogbase {
	StringColumn::StringColumn(const string& name) : TColumn<string>(name) {
	}
}
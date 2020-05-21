#include "string_column.hpp"

namespace clogbase {
	string StringType::load_value(File& in) const {
		return in.read_string();
	}

	void StringType::store_value(const string& value, File& out) const {
		out.write_string(value);
	}

	const StringType& string_type() {
		static StringType type;
		return type;
	}

	StringColumn::StringColumn(const string& name) : TColumn<string>(name, string_type()) {
	}
}
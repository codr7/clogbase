#include "int64_column.hpp"

namespace clogbase {
	int64_t Int64Type::load_value(File& in) const {
		return in.read_int64();
	}
	
	void Int64Type::store_value(const int64_t& value, File& out) const {
		out.write_int64(value);
	}

	const Int64Type& int64_type() {
		static Int64Type type;
		return type;
	}

	Int64Column::Int64Column(const string &name) : TColumn<int64_t>(name, int64_type()) {
	}

	Int64SetColumn::Int64SetColumn(const string& name) : SetColumn<int64_t>(name, int64_type()) {
	}
}
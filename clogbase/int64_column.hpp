#pragma once

#include "set_column.hpp"

namespace clogbase {
	const ColumnType<int64_t> &int64_type();

	class Int64Column : public TColumn<int64_t> {
	public:
		Int64Column(const string &name);
	};

	class Int64SetColumn : public SetColumn<int64_t> {
	public:
		Int64SetColumn(const string& name);
	};
}
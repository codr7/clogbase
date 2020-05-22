#pragma once

#include "set_column.hpp"
#include "vector_column.hpp"

namespace clogbase {
	class Int64Type: public ColumnType<int64_t> {
	public:
		int64_t load_value(File& in) const;
		void store_value(const int64_t& value, File& out) const;
	};

	const Int64Type &int64_type();

	class Int64Column : public TColumn<int64_t> {
	public:
		Int64Column(const string &name);
	};

	class Int64SetColumn : public SetColumn<int64_t> {
	public:
		Int64SetColumn(const string& name);
	};

	class Int64VectorColumn : public VectorColumn<int64_t> {
	public:
		Int64VectorColumn(const string& name);
	};
}
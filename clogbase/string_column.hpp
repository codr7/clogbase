#pragma once

#include "tcolumn.hpp"

namespace clogbase {
	class StringType : public ColumnType<string> {
	public:
		string load_value(File& in) const;
		void store_value(const string& value, File& out) const;
	};

	const StringType& string_type();

	class StringColumn : public TColumn<string> {
	public:
		StringColumn(const string &name);
	};
}
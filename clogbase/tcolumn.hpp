#pragma once

#include "column.hpp"
#include "column_type.hpp"
#include "file.hpp"

namespace clogbase {
	template <typename T>
	class TColumn : public Column {
	public:
		const ColumnType<T>& type;

		TColumn(const string& name, const ColumnType<T>& type);
		any load_value(File& in) const;
	};

	template <typename T>
	TColumn<T>::TColumn(const string& name, const ColumnType<T>& type) : Column(name), type(type) {
	}

	template <typename T>
	any TColumn<T>::load_value(File& in) const {
		return type.load_value(in);
	}
}
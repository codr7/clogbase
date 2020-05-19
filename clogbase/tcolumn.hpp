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
		any load_value(File& in) const override;
		void store_value(const any& value, File& out) const override;
		Order compare_values(const any& x, const any& y) const;
	};

	template <typename T>
	TColumn<T>::TColumn(const string& name, const ColumnType<T>& type) : Column(name), type(type) {
	}

	template <typename T>
	any TColumn<T>::load_value(File& in) const {
		return type.load_value(in);
	}

	template <typename T>
	void TColumn<T>::store_value(const any& value, File& out) const {
		type.store_value(any_cast<const T&>(value), out);
	}

	template <typename T>
	Order TColumn<T>::compare_values(const any& x, const any& y) const {
		return type.compare_values(any_cast<const T&>(x), any_cast<const T&>(y));
	}

}
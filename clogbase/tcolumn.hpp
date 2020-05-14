#pragma once

#include "column.hpp"
#include "file.hpp"

namespace clogbase {
	template <typename T>
	class TColumn : public Column {
	public:
		TColumn(const string& name);
		any load_value(File& in) const;
	};

	template <typename T>
	TColumn<T>::TColumn(const string& name) : Column(name) {
	}

	template <typename T>
	any TColumn<T>::load_value(File& in) const {
		T value;
		in.read(value);
		return value;
	}

}
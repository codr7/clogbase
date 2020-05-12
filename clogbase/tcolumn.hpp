#pragma once

#include "column.hpp"

namespace clogbase {
	template <typename T>
	class TColumn : public Column {
	public:
		TColumn(const string& name);
	};

	template <typename T>
	TColumn<T>::TColumn(const string& name) : Column(name) {
	}
}
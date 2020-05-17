#pragma once

#include <any>

#include "file.hpp"

namespace clogbase {
	using namespace std;

	template <typename T>
	class ColumnType {
	public:
		using Value = T;
		virtual any load_value(File& in) const;
	};

	template <typename T>
	any ColumnType<T>::load_value(File& in) const {
		T value;
		in.read(value);
		return value;
	}
}
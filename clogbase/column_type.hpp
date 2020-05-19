#pragma once

#include <any>

#include "file.hpp"

namespace clogbase {
	using namespace std;

	template <typename T>
	class ColumnType {
	public:
		virtual T load_value(File& in) const = 0;
		virtual void store_value(const T &value, File& out) const = 0;
	};

	template <typename T>
	class BasicType: public ColumnType<T> {
	public:
		T load_value(File& in) const override;
		void store_value(const T& value, File& out) const override;
	};

	template <typename T>
	T BasicType<T>::load_value(File& in) const {
		T value;
		in.read(value);
		return value;
	}

	template <typename T>
	void BasicType<T>::store_value(const T& value, File& out) const {
		out.write(value);
	}
}
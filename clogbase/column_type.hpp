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
		virtual Order compare_values(const T& x, const T& y) const;
	};

	template <typename T>
	Order ColumnType<T>::compare_values(const T& x, const T& y) const {
		if (x < y) {
			return Order::LT;
		}

		if (x > y) {
			return Order::GT;
		}

		return Order::EQ;
	}
}
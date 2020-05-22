#pragma once

#include <vector>

#include "tcolumn.hpp"

namespace clogbase {
	template <typename T>
	class VectorType : public ColumnType<vector<T>> {
	public:
		const ColumnType<T>& item_type;

		VectorType(const ColumnType<T>& item_type);
		vector<T> load_value(File& in) const override;
		void store_value(const vector<T>& value, File& out) const override;
	};

	template <typename T>
	VectorType<T>::VectorType(const ColumnType<T>& item_type) : item_type(item_type) {
	}

	template <typename T>
	vector<T> VectorType<T>::load_value(File& in) const {
		const auto size(in.read_int64());
		vector<T> value;

		for (int32_t i = 0; i < size; i++) {
			value.push_back(any_cast<T>(item_type.load_value(in)));
		}

		return value;
	}

	template <typename T>
	void VectorType<T>::store_value(const vector<T>& value, File& out) const {
		out.write_int64(value.size());

		for (const T& item : value) {
			item_type.store_value(item, out);
		}
	}

	template <typename T>
	const VectorType<T>& vector_type(const ColumnType<T>& item_type) {
		static VectorType<T> type(item_type);
		return type;
	}

	template <typename T>
	class VectorColumn : public TColumn<vector<T>> {
	public:
		VectorColumn(const string& name, const ColumnType<T>& type);
	};

	template <typename T>
	VectorColumn<T>::VectorColumn(const string& name, const ColumnType<T>& type) : TColumn<vector<T>>(name, vector_type(type)) {
	}
}
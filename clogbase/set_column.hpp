#pragma once

#include <set>

#include "tcolumn.hpp"

namespace clogbase {
	template <typename T>
	class SetType: public ColumnType<set<T>> {
	public:
		const ColumnType<T>& item_type;

		SetType(const ColumnType<T>& item_type);
		set<T> load_value(File& in) const override;
		void store_value(const set<T>& value, File& out) const override;
	};

	template <typename T>
	SetType<T>::SetType(const ColumnType<T>& item_type): item_type(item_type) {
	}

	template <typename T>
	set<T> SetType<T>::load_value(File& in) const {
		int32_t size;
		in.read(size);
		set<T> value;

		for (int32_t i = 0; i < size; i++) {
			value.insert(any_cast<T>(item_type.load_value(in)));
		}

		return value;
	}

	template <typename T>
	void SetType<T>::store_value(const set<T>& value, File& out) const {
		out.write(value.size());
		
		for (const T& item : value) {
			out.write(item);
		}
	}

	template <typename T>
	const SetType<T>& set_type(const ColumnType<T>& item_type) {
		static SetType<T> type(item_type);
		return type;
	}

	template <typename T>
	class SetColumn : public TColumn<set<T>> {
	public:
		SetColumn(const string& name, const ColumnType<T>& type);
	};

	template <typename T>
	SetColumn<T>::SetColumn(const string& name, const ColumnType<T>& type) : TColumn<set<T>>(name, set_type(type)) {
	}
}
#pragma once

#include <any>
#include <map> 

#include "tcolumn.hpp"

namespace clogbase {
	using namespace std;

	using RecordId = int64_t;

	class Record {
	public:
		template <typename T>
		const T& get(const TColumn<T> &column) const;

		template <typename T>
		T& get(const TColumn<T>& column);

		template <typename T, typename V>
		void set(const TColumn<T> &column, const V &value);
	private:
		map<const Column*, any> _fields;
	};

	template <typename T>
	const T& Record::get(const TColumn<T> &column) const {
		return any_cast<const T&>(_fields.at(&column));
	}

	template <typename T>
	T& Record::get(const TColumn<T>& column) {
		return any_cast<T&>(_fields.at(&column));
	}

	template <typename T, typename V>
	void Record::set(const TColumn<T> &column, const V& value) {
		_fields[&column] = T(value);
	}
}
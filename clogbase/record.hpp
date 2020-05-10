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
		const T& get(const TColumn<T> column) const;

		template <typename T>
		void set(const TColumn<T> column, const T &value) const;
	private:
		map<const Column*, any> _fields;
	};

	template <typename T>
	const T& Record::get(const TColumn<T> column) const {
		return _fields.at(&column);
	}

	template <typename T>
	void Record::set(const TColumn<T> column, const T& value) const {
		_fields[&column] = value;
	}
}
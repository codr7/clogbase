#pragma once

#include <any>
#include <map> 

#include "tcolumn.hpp"

namespace clogbase {
	using namespace std;

	using RecordId = int64_t;
	using Field = pair<const Column*, any>;

	class Table;

	class Record {
	public:
		using Fields = map<const Column*, any>;

		RecordId id(const Table& table) const;
		size_t size() const;
		Fields::const_iterator begin() const;
		Fields::const_iterator end() const;

		template <typename T>
		const T& get(const TColumn<T>& column) const;

		template <typename T>
		T& get(const TColumn<T>& column);

		const any& get_any(const Column& column) const;

		template <typename T, typename V>
		void set(const TColumn<T>& column, const V &value);

		void set_any(const Column& column, const any& value);
	private:
		Fields _fields;
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
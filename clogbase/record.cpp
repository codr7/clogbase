#include "record.hpp"
#include "table.hpp"

namespace clogbase {
	RecordId Record::id(const Table& table) const {
		return get(table.id);
	}

	size_t Record::size() const {
		return _fields.size();
	}

	Record::Fields::const_iterator Record::begin() const {
		return _fields.begin();
	}

	Record::Fields::const_iterator Record::end() const {
		return _fields.end();
	}

	const any& Record::get_any(const Column& column) const {
		return _fields.at(&column);
	}

	void Record::set_any(const Column& column, const any& value) {
		_fields[&column] = value;
	}
}
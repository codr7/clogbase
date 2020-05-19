#include "record.hpp"

namespace clogbase {
	size_t Record::size() const {
		return _fields.size();
	}

	Record::Fields::const_iterator Record::begin() const {
		return _fields.begin();
	}

	Record::Fields::const_iterator Record::end() const {
		return _fields.end();
	}
}
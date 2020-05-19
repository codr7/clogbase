#include "column.hpp"

namespace clogbase {
	Column::Column(const string& name) : _name(name) {
	}

	const string& Column::name() const {
		return _name;
	}
}
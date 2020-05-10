#include "table.hpp"

namespace clogbase {
	Table::Table(Root &root, const string& name): _root(root), _name(name) {
	}

	const string& Table::name() const {
		return _name;
	}
}
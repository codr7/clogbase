#include "root.hpp"

namespace clogbase {
	Root::Root(const fs::path& path) : _path(path) {
	}

	void Root::add_table(Table& table) {
		_tables.push_back(&table);
	}

}
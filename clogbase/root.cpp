#include "root.hpp"
#include "table.hpp"

namespace clogbase {
	Root::Root(const fs::path& path) : _path(path) {
	}

	void Root::add_table(Table& table) {
		_tables.push_back(&table);
	}

	void Root::open() {
		fs::create_directories(_path);
		
		for (auto t : _tables) {
			t->open();
		}
	}

	const fs::path& Root::path() const {
		return _path;
	}
}
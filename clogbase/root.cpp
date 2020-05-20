#include "root.hpp"
#include "table.hpp"

namespace clogbase {
	Root::Root(const fs::path& path) : _path(path) {
	}

	void Root::operator <<(Table& table) {
		_tables.push_back(&table);
	}

	void Root::open(const Time &max_time, bool read_only) {
		fs::create_directories(_path);
		
		for (auto t : _tables) {
			t->open(max_time, read_only);
		}
	}

	const fs::path& Root::path() const {
		return _path;
	}
}
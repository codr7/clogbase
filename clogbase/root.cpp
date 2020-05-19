#include "root.hpp"
#include "schema.hpp"

namespace clogbase {
	Root::Root(const fs::path& path) : _path(path) {
	}

	void Root::operator <<(Schema& schema) {
		_schemas.push_back(&schema);
	}

	void Root::open() {
		fs::create_directories(_path);
		
		for (auto s : _schemas) {
			s->open();
		}
	}

	const fs::path& Root::path() const {
		return _path;
	}
}
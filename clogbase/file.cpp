#include "file.hpp"

namespace clogbase {
	File::File(fs::path path) : _path(path) {
	}
	
	void File::open() {
		_stream.open(_path, fstream::in|fstream::out|fstream::binary);
	}
}
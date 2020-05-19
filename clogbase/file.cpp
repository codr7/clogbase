#include "file.hpp"

namespace clogbase {
	File::File(fs::path path) : _path(path) {
	}
	
	void File::open() {
		_stream.exceptions(fstream::failbit|fstream::badbit);
		_stream.open(_path, fstream::in|fstream::out|fstream::app|fstream::binary);
	}

	void File::seek(Offset offset) {
		_stream.seekg(offset);
	}

	File::Offset File::seek_eof() {
		_stream.seekp(0, fstream::end);
		return _stream.tellp();
	}


	bool File::eof() const {
		return _stream.eof();
	}

	void File::flush() {
		_stream.flush();
	}
}
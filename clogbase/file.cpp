#include "file.hpp"

namespace clogbase {
	File::File(fs::path path) : _path(path) {
	}
	
	void File::open(bool read_only) {
		_stream.exceptions(fstream::badbit);
		_stream.open(_path, read_only ? fstream::in | fstream::binary : fstream::in|fstream::out|fstream::app|fstream::binary);
	}

	void File::seek(Offset offset) {
		_stream.seekg(offset);
	}

	File::Offset File::seek_eof() {
		_stream.seekp(0, fstream::end);
		return _stream.tellp();
	}


	bool File::eof() {
		bool result(_stream.fail());
		_stream.clear();
		return result;
	}

	void File::flush() {
		_stream.flush();
	}
}
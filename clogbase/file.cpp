#include "file.hpp"

namespace clogbase {
	File::File(fs::path path) : _path(path) {
	}
	
	void File::open(bool read_only) {
		_stream.exceptions(fstream::badbit);
		const auto mode(read_only ? (fstream::in|fstream::binary) : (fstream::in|fstream::out|fstream::app|fstream::binary));
		_stream.open(_path, mode);
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

	int8_t File::read_int8() {
		return _stream.get();
	}

	int64_t File::read_int64() {
		const auto length(read_int8());

		if (_stream.fail()) {
			return -1;
		}

		string buffer;
		buffer.resize(length);
		_stream.read(buffer.data(), length);
		return static_cast<int64_t>(strtoimax(buffer.c_str(), NULL, 10));
	}

	string File::read_string() {
		const auto length(read_int64());

		if (_stream.fail()) {
			return "";
		}

		string out;
		out.resize(static_cast<const unsigned int>(length));
		_stream.read(out.data(), length);
		return out;
	}

	Time File::read_time() {
		const auto ms(read_int64());
		return Time(std::chrono::milliseconds(ms));
	}

	void File::write_int8(int8_t value) {
		_stream.put(value);
	}

	void File::write_int64(int64_t value) {
		const auto s(to_string(value));
		const auto length(static_cast<int8_t>(s.length()));
		write_int8(length);
		_stream.write(s.data(), length);
	}

	void File::write_string(const string& value) {
		const auto length(value.length());
		write_int64(length);
		_stream.write(value.data(), length);
	}

	void File::write_time(Time value) {
		write_int64(duration_cast<milliseconds>(value.time_since_epoch()).count());
	}
}
#pragma once

#include <cinttypes>
#include <filesystem>
#include <fstream>
#include <string>

#include "types.hpp"

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class File {
	public:
		using Offset = int64_t;

		File(fs::path path);
		void open();
		void seek(Offset offset);
		Offset seek_eof();
		bool eof();
		void flush();

		template <typename T>
		void read(T& value);

		template <>
		void read(int8_t& value);

		template <>
		void read(string& value);

		template <>
		void read(Time& value);

		template <typename T>
		void write(const T &value);
	
		template <>
		void write(const int8_t &value);

		template <>
		void write(const string& value);

		template <>
		void write(const Time& value);
	private:
		fs::path _path;
		fstream _stream;
	};

	template <typename T>
	void File::read(T& value) {
		int8_t length(-1);
		_stream >> length;
		
		if (!_stream.fail()) {
			string buffer;
			buffer.reserve(length);
			_stream.read(buffer.data(), length);
			value = static_cast<T>(strtoimax(buffer.c_str(), NULL, 10));
		}
	}

	template <>
	void File::read(int8_t& value) {
		_stream >> value;
	}

	template <>
	void File::read(string& value) {
		int32_t length(-1);
		read(length);

		if (!_stream.fail()) {
			value.reserve(length);
			_stream.read(value.data(), length);
		}
	}

	template <>
	void File::read(Time& value) {
		int64_t msecs(-1);
		read(msecs);
		value = Time(std::chrono::milliseconds(msecs));
	}

	template <typename T>
	void File::write(const T &value) {
		string s(to_string(value));
		auto length(static_cast<int8_t>(s.length()));
		_stream << length;
		_stream.write(s.data(), length);
	}

	template <>
	void File::write(const int8_t &value) {
		_stream << value;
	}

	template <>
	void File::write(const string& value) {
		auto length(value.length());
		write(length);
		_stream.write(value.data(), length);
	}

	template <>
	void File::write(const Time& value) {
		write(duration_cast<milliseconds>(value.time_since_epoch()).count());
	}
}
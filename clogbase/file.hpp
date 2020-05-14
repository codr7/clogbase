#pragma once

#include <filesystem>
#include <fstream>

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
		
		template <typename T>
		void read(T& value);

		template <>
		void read(int8_t& value);

		template <>
		void read(string& value);

		template <>
		void read(Time& value);
	private:
		fs::path _path;
		fstream _stream;
	};

	template <typename T>
	void File::read(T& value) {
		int8_t length(-1);
		_stream >> length;
		string digits;
		digits.reserve(length);
		_stream.read(digits.data(), length);
	}

	template <>
	void File::read(int8_t& value) {
		_stream >> value;
	}

	template <>
	void File::read(string& value) {
		int32_t length(-1);
		read(length);
		value.reserve(length);
		_stream.read(value.data(), length);
	}

	template <>
	void File::read(Time& value) {
		int64_t msecs(-1);
		read(msecs);
		value = Time(std::chrono::milliseconds(msecs));
	}
}
#pragma once

#include <cinttypes>
#include <filesystem>
#include <fstream>
#include <string>

#include "time.hpp"

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class File {
	public:
		using Offset = int64_t;

		File(fs::path path);
		void open(bool read_only);
		void seek(Offset offset);
		Offset seek_eof();
		bool eof();
		void flush();

		int8_t read_int8();
		int64_t read_int64();
		string read_string();
		Time read_time();

		void write_int8(int8_t value);
		void write_int64(int64_t value);
		void write_string(const string& value);
		void write_time(Time value);
	private:
		fs::path _path;
		fstream _stream;
	};
}
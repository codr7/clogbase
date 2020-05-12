#pragma once

#include <filesystem>
#include <fstream>

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class File {
	public:
		File(fs::path path);
		void open();
	private:
		fs::path _path;
		fstream _stream;
	};
}
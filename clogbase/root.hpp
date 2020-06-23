#pragma once

#include <filesystem>

#include "time.hpp"

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class Table;
	
	class Root {
	public:
		Root(const fs::path& path);
		void operator <<(Table& table);
		void open(Time max_time, bool read_only);
		const fs::path& path() const;
	private:
		fs::path _path;
		vector<Table*> _tables;
	};
}
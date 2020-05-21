#pragma once

#include <filesystem>

#include "types.hpp"

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
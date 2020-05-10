#pragma once

#include <filesystem>

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class Table;

	class Root {
	public:
		Root(const fs::path& path);
		void add_table(Table& table);
	private:
		fs::path _path;
		vector<Table*> _tables;
	};
}
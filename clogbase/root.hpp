#pragma once

#include <filesystem>

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class Table;
	
	class Root {
	public:
		Root(const fs::path& path);
		void operator <<(Table& table);
		void open();
		const fs::path& path() const;
	private:
		fs::path _path;
		vector<Table*> _tables;
	};
}
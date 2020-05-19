#pragma once

#include <filesystem>

namespace clogbase {
	using namespace std;
	namespace fs = filesystem;

	class Schema;
	
	class Root {
	public:
		Root(const fs::path& path);
		void operator <<(Schema& schema);
		void open();
		const fs::path& path() const;
	private:
		fs::path _path;
		vector<Schema*> _schemas;
	};
}
#pragma once

#include <any>
#include <string>

namespace clogbase {
	using namespace std;

	class File;

	class Column {
	public:
		const string name;

		Column(const string& name);
		virtual any load_value(File& in) const = 0;
		virtual void store_value(const any &value, File& out) const = 0;
	};
}
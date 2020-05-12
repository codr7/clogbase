#pragma once

#include <string>

namespace clogbase {
	using namespace std;

	class Column {
	public:
		const string name;

		Column(const string& name);
	};
}
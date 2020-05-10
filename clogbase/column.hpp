#pragma once

#include <string>

namespace clogbase {
	using namespace std;

	class Column {
	public:
		const string& name() const;
	private:
		string _name;
	};
}
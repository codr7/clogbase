#pragma once

#include <map>
#include <string>

#include "record.hpp"
#include "root.hpp"

namespace clogbase {
	using namespace std;

	class Table {
	public:
		Table(Root &root, const string& name);
		const string& name() const;
	private:
		using Offset = int64_t;

		Root& _root;
		string _name;
		map<string, const Column*> _columns;
		map<RecordId, Offset> _records;
	};
}
#pragma once

#include <map>
#include <string>

#include "file.hpp"
#include "int64_column.hpp"
#include "record.hpp"
#include "root.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	class Table {
	public:
		const string name;
		const Int64Column id;

		Table(Root &root, const string& name, initializer_list<const Column *> columns);
		void open();
		int64_t get_id();
		bool exists(const Record& record) const;
		void load(RecordId id, Record& record);
		void store(const Record& record, Context& context);
	private:
		using Offset = int64_t;

		map<string, const Column*> _columns;
		int64_t _next_id;
		map<RecordId, Offset> _records;
		File _key_file, _data_file;
	};
}
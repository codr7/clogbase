#pragma once

#include <map>
#include <string>

#include "abstract_index.hpp"
#include "file.hpp"
#include "int64_column.hpp"
#include "record.hpp"
#include "root.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	template <size_t KEY_SIZE>
	class Index;

	class Table {
	public:
		template <size_t KEY_SIZE>
		friend class Index;

		const Int64Column id;

		Table(Root &root, const string& name, initializer_list<const Column *> columns);
		void open(Time max_time, bool read_only);
		int64_t get_id();
		bool exists(const Record& record) const;
		bool load(RecordId id, Record& record) const;
		void store(const Record& record, Context& context);
	private:
		Root& _root;
		const string _name;
		set<AbstractIndex*> _indexes;
		map<string, const Column*> _columns;
		int64_t _next_id;
		map<RecordId, File::Offset> _records;
		File _key_file, _data_file;
	};
}
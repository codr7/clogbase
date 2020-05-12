#include <iterator> 
#include "table.hpp"

namespace clogbase {
	Table::Table(Root &root, const string& name, initializer_list<const Column*> columns):
		name(name),
		id(name + "_id"),
		_key_file(root.path() / fs::path(name + ".dat")),
		_data_file(root.path() / fs::path(name + ".key")) {

		transform(
			columns.begin(), columns.end(), 
			inserter(_columns, _columns.end()), 
			[](const Column* c) { return make_pair(c->name, c); });

		root.add_table(*this);
	}

	void Table::open() {
		_key_file.open();
		_data_file.open();
	}

	int64_t Table::get_id() {
		return ++_next_id;
	}

	bool Table::exists(const Record& record) const {
		return _records.find(record.get(id)) != _records.end();
	}

	void Table::load(RecordId id, Record& record) {
	}

	void Table::store(const Record& record, Context& context) {
	}
}
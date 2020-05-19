#include <iterator> 

#include "context.hpp"
#include "index.hpp"
#include "table.hpp"

namespace clogbase {
	Table::Table(Root &root, const string& name, initializer_list<AbstractIndex*> indexes, initializer_list<const Column*> columns):
		id(name + "_id"),
		_name(name),
		_indexes(indexes),
		_key_file(root.path() / fs::path(name + ".cti")),
		_data_file(root.path() / fs::path(name + ".ctd")) {

		transform(
			columns.begin(), columns.end(), 
			inserter(_columns, _columns.end()), 
			[](const Column* c) { return make_pair(c->name(), c); });

		root << *this;
	}

	void Table::open() {
		_key_file.open();
		_data_file.open();

		for (;;) {
			RecordId id;
			_key_file.read(id);
			
			if (_key_file.eof()) {
				break;
			}

			File::Offset offset;
			_key_file.read(offset);

			_records[id] = offset;
			_next_id = max(_next_id, id);
		}
	}

	int64_t Table::get_id() {
		return ++_next_id;
	}

	bool Table::exists(const Record& record) const {
		return _records.find(record.get(id)) != _records.end();
	}

	bool Table::load(RecordId id, Record& record) const {
		auto found(_records.find(id));
		
		if (found == _records.end()) {
			return false;
		}

		File& f(const_cast<Table*>(this)->_data_file);
		f.seek(found->second);
		int8_t column_count(-1);
		f.read(column_count);
		
		for (int8_t i(0); i < column_count; i++) {
			string column_name;
			f.read(column_name);
			auto column(_columns.find(column_name));
			
			if (column == _columns.end()) {
				continue;
			}

			column->second->load_value(f);
		}

		return true;
	}

	void Table::store(const Record& record, Context& context) {
		context << [record, this](Context &context) {
			unique_ptr<Record> prev;
			const auto id(record.get(id));

			if (_records.find(id) != _records.end()) {
				prev.reset(new Record());
				load(id, *prev);

				for (auto ix: _indexes) {
					ix->remove(*prev, id, context);
				}
			}

			const auto offset(_data_file.seek_eof());
			_data_file.write(record.size());

			for (const Field& f : record) {
				auto& c(*f.first);
				_data_file.write(c.name());
				c.store_value(f.second, _data_file);
			}

			_data_file.flush();
			_key_file.write(id);
			_key_file.write(offset);
			_key_file.flush();
			_records[id] = offset;

			for (auto ix: _indexes) {
				ix->add(record, id, context);
			}
		};
	}
}
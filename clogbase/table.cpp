#include <iterator> 

#include "context.hpp"
#include "index.hpp"
#include "table.hpp"

namespace clogbase {
	Table::Table(Root &root, const string& name, initializer_list<const Column*> columns):
		id(name + "_id"),
		_root(root),
		_name(name),
		_key_file(root.path() / fs::path(name + ".cti")),
		_data_file(root.path() / fs::path(name + ".ctd")) {

		transform(
			columns.begin(), columns.end(), 
			inserter(_columns, _columns.end()), 
			[](const Column* c) { return make_pair(c->name(), c); });

		root << *this;
	}

	void Table::open(Time max_time, bool read_only) {
		_key_file.open(read_only);
		_data_file.open(read_only);

		for (;;) {
			const auto time(_key_file.read_time());

			if (_key_file.eof()) {
				break;
			}

			if (time >= max_time) {
				_key_file.seek_eof();
				break;
			}

			const RecordId id(_key_file.read_int64());
			const File::Offset offset(_key_file.read_int64());
			_records[id] = offset;
			_next_id = max(_next_id, id);
		}

		for (auto ix : _indexes) {
			ix->open(max_time, read_only);
		}
	}

	int64_t Table::get_id() {
		return ++_next_id;
	}

	Table::Iterator Table::begin() const {
		return _records.begin();
	}

	Table::Iterator Table::end() const {
		return _records.end();
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
		int8_t column_count(f.read_int8());

		for (int8_t i(0); i < column_count; i++) {
			const auto column_name(f.read_string());
			const auto found(_columns.find(column_name));

			if (found == _columns.end()) {
				continue;
			}

			const auto& c(*found->second);
			record.set_any(c, c.load_value(f));
		}

		record.set(this->id, id);
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
					ix->remove(*prev, context);
				}
			}

			const auto offset(_data_file.seek_eof());
			_data_file.write_int8(static_cast<int8_t>(record.size()-1));

			for (const Field& f : record) {
				const auto c(f.first);
				
				if (c == &this->id) {
					continue;
				}

				_data_file.write_string(c->name());
				c->store_value(f.second, _data_file);
			}

			_data_file.flush();
			_key_file.write_time(Clock::now());
			_key_file.write_int64(id);
			_key_file.write_int64(offset);
			_key_file.flush();
			_records[id] = offset;

			for (auto ix: _indexes) {
				ix->add(record, context);
			}
		};
	}
}
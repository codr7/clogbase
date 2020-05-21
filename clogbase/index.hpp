#pragma once

#include <array> 
#include <functional>
#include <map>
#include <sstream>

#include "abstract_index.hpp"
#include "file.hpp"
#include "record.hpp"
#include "root.hpp"
#include "table.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	template <size_t KEY_SIZE>
	class Index: public AbstractIndex {
	public:
		using Key = array<any, KEY_SIZE>;
		using Records = multimap<Key, RecordId, function<bool(const Key&, const Key&)>>;
		using Iterator = typename Records::const_iterator;

		Index(Table &table, const string& name, array<string, KEY_SIZE> columns);
		const string& name() const override;
		void open(Time max_time, bool read_only) override;
		Order compare_keys(const Key& x, const Key& y) const;
		Iterator end() const;

		template <typename...T>
		Iterator lower_bound(T...values) const;
		
		void add(const Record& record, Context& context) override;
		void remove(const Record& record, Context& context) override;
	private:
		Table& _table;
		const string _name;
		array<const Column*, KEY_SIZE> _columns;
		Records _records;
		File _file;
	};

	template <size_t KEY_SIZE>
	Index<KEY_SIZE>::Index(Table &table, const string& name, array<string, KEY_SIZE> columns) :
		_table(table),
		_name(name),
		_records([this](const Key& x, const Key& y) { return compare_keys(x, y) == Order::LT; }),
		_file(table._root.path() / fs::path(name + ".cid")) {
		transform(
			columns.begin(), columns.end(),
			_columns.begin(),
			[&table](const string & c) { return table._columns.find(c)->second; });

		table._indexes.insert(this);
	}

	template <size_t KEY_SIZE>
	const string& Index<KEY_SIZE>::name() const {
		return _name;
	}

	template <size_t KEY_SIZE>
	void Index<KEY_SIZE>::open(Time max_time, bool read_only) {
		_file.open(read_only);

		for (;;) {
			const auto time(_file.read_time());

			if (_file.eof()) {
				break;
			}

			if (time >= max_time) {
				_file.seek_eof();
				break;
			}

			Key key;
			
			for (size_t i = 0; i < KEY_SIZE; i++) {
				key[i] = _columns[i]->load_value(_file);
			}

			const RecordId id(_file.read_int64());

			if (id < 0) {
				for (auto i(_records.find(key)); i != _records.end() && compare_keys(i->first, key) == Order::EQ; i++) {
					if (i->second == -id) {
						_records.erase(i);
						break;
					}
				}
			}
			else {
				_records.insert(make_pair(key, id));
			}
		}
	}

	template <size_t KEY_SIZE>
	Order Index<KEY_SIZE>::compare_keys(const Key& x, const Key& y) const {
		for (size_t i = 0; i < KEY_SIZE; i++) {
			switch (_columns[i]->compare_values(x[i], y[i])) {
			case Order::LT:
				return Order::LT;
			case Order::GT:
				return Order::GT;
			}
		}

		return Order::EQ;
	}

	template <size_t KEY_SIZE>
	typename Index<KEY_SIZE>::Iterator Index<KEY_SIZE>::end() const {
		return _records.end();
	}

	template <size_t KEY_SIZE>
	template <typename...T>
	typename Index<KEY_SIZE>::Iterator Index<KEY_SIZE>::lower_bound(T...values) const {
		return _records.lower_bound(Key{ values... });
	}

	template <size_t KEY_SIZE>
	void Index<KEY_SIZE>::add(const Record& record, Context& context) {
		Key key;
		transform(_columns.begin(), _columns.end(), key.begin(), [&record](auto c) { return record.get_any(*c); });
		const RecordId id(record.id(_table));

		context << [this, key, id](Context& context) {
			_file.write_time(Clock::now());

			for (size_t i = 0; i < KEY_SIZE; i++) {
				_columns[i]->store_value(key[i], _file);
			}

			_file.write_int64(id);
			_file.flush();
			_records.insert(make_pair(key, id));
		};
	}

	template <size_t KEY_SIZE>
	void Index<KEY_SIZE>::remove(const Record &record, Context& context) {
		Key key;
		transform(_columns.begin(), _columns.end(), key.begin(), [&record](auto c) { return record.get_any(*c); });
		const RecordId id(record.id(_table));

		context << [this, key, id](Context& context) {
			for (auto i(_records.find(key)); i != _records.end() && compare_keys(i->first, key) == Order::EQ; i++) {
				if (i->second == id) {
					_file.write_time(Clock::now());

					for (size_t i = 0; i < KEY_SIZE; i++) {
						_columns[i]->store_value(key[i], _file);
					}

					_file.write_int64(-id);
					_file.flush();
					_records.erase(i);
					break;
				}
			}
		};
	}
}
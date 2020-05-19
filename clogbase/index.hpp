#pragma once

#include <array> 
#include <functional>
#include <map>
#include <sstream>

#include "abstract_index.hpp"
#include "file.hpp"
#include "record.hpp"
#include "root.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	template <size_t KEY_SIZE>
	class Index: public AbstractIndex {
	public:
		using Key = array<any, KEY_SIZE>;

		Index(Root& root, const string& name, array<const Column*, KEY_SIZE> columns);
		const string& name() const override;
		void open();
		Order compare_keys(const Key& x, const Key& y) const;
		void add(const Record& record, RecordId id, Context& context) override;
		void remove(const Record& record, RecordId id, Context& context) override;
	private:
		const string _name;
		array<const Column*, KEY_SIZE> _columns;
		multimap<Key, RecordId, function<bool (const Key&, const Key&)>> _records;
		File _file;
	};

	template <size_t KEY_SIZE>
	Index<KEY_SIZE>::Index(Root& root, const string& name, array<const Column*, KEY_SIZE> columns) :
		_name(name),
		_columns(columns),
		_records([this](const Key& x, const Key& y) { return compare_keys(x, y) == Order::LT; }),
		_file(root.path() / fs::path(name + ".cid")) {
		root << *this;
	}

	template <size_t KEY_SIZE>
	const string& Index<KEY_SIZE>::name() const {
		return _name;
	}

	template <size_t KEY_SIZE>
	void Index<KEY_SIZE>::open() {
		_file.open();

		for (;;) {
			Key key;
			key[0] = _columns[0]->load_value(_file);
			
			if (_file.eof()) {
				break;
			}

			for (size_t i = 1; i < KEY_SIZE; i++) {
				key[i] = _columns[i]->load_value(_file);
			}

			RecordId id;
			_file.read(id);

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
	void Index<KEY_SIZE>::add(const Record& record, RecordId id, Context& context) {
		Key key;

		for (size_t i = 0; i < KEY_SIZE; i++) {
			key[i] = record.get(*_columns[i]);
		}

		context << [this, key, id](Context& context) {
			for (size_t i = 0; i < KEY_SIZE; i++) {
				_columns[i]->store_value(key[i], _file);
			}

			_file.write(id);
			_records.insert(make_pair(key, id));
		};
	}

	template <size_t KEY_SIZE>
	void Index<KEY_SIZE>::remove(const Record &record, RecordId id, Context& context) {
		Key key;

		for (size_t i = 0; i < KEY_SIZE; i++) {
			key[i] = record.get(*_columns[i]);
		}

		context << [this, key, id](Context& context) {
			for (auto i(_records.find(key)); i != _records.end() && compare_keys(i->first, key) == Order::EQ; i++) {
				if (i->second == id) {
					for (size_t i = 0; i < KEY_SIZE; i++) {
						_columns[i]->store_value(key[i], _file);
					}

					_file.write(-id);
					_records.erase(i);
					break;
				}
			}
		};
	}
}
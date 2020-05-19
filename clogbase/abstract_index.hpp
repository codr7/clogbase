#pragma once

#include "record.hpp"
#include "schema.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	class AbstractIndex : public Schema {
	public:
		virtual const string& name() const = 0;
		virtual void add(const Record& record, RecordId id, Context& context) = 0;
		virtual void remove(const Record& record, RecordId id, Context& context) = 0;
	};
}
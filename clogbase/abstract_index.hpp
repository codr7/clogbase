#pragma once

#include "record.hpp"

namespace clogbase {
	using namespace std;

	class Context;

	class AbstractIndex {
	public:
		virtual const string& name() const = 0;
		virtual void open(Time max_time, bool readonly) = 0;
		virtual void add(const Record& record, Context& context) = 0;
		virtual void remove(const Record& record, Context& context) = 0;
	};
}
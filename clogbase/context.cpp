#include "context.hpp"

namespace clogbase {
	Context::Context(Context* parent) : parent(parent) {
	}

	Context::~Context() {
		commit();
	}

	void Context::commit() {
		if (parent) {
			copy(_actions.begin(), _actions.end(), back_inserter(parent->_actions));
		}
		else {
			for (auto& a : _actions) {
				a();
			}
		}

		_actions.clear();
	}

	void Context::rollback() {
		_actions.clear();
	}
}

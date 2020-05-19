#include "context.hpp"

namespace clogbase {
	Context::Context(Context* parent) : parent(parent) {
	}

	Context::~Context() {
		commit();
	}

	void Context::operator <<(Action action) {
		_actions.push_back(action);
	}

	void Context::commit() {
		if (parent) {
			move(_actions.begin(), _actions.end(), back_inserter(parent->_actions));
			_actions.clear();
		}
		else {
			while (!_actions.empty()) {
				_actions.front()(*this);
				_actions.pop_front();
			}
		}
	}

	void Context::rollback() {
		_actions.clear();
	}
}

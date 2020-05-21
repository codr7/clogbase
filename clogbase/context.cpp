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
			vector<Action> todo;
			move(_actions.begin(), _actions.end(), back_inserter(todo));
			_actions.clear();

			for (const Action &a: todo) {
				a(*this);
				commit();
			}
		}
	}

	void Context::rollback() {
		_actions.clear();
	}
}

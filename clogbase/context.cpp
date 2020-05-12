#include "context.hpp"

namespace clogbase {
	Context::Context(Context* parent) : parent(parent) {
	}

	Context::~Context() {
		commit();
	}

	void Context::commit() {
		if (parent) {
		}
	}
}

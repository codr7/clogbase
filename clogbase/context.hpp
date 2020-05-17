#pragma once

#include <functional>
#include <vector>

namespace clogbase {
	using namespace std;

	using Action = function<void()>;

	class Context {
	public:
		Context* const parent;

		Context(Context* prev = nullptr);
		~Context();
		void commit();
		void rollback();
	private:
		vector<Action> _actions;
	};
}
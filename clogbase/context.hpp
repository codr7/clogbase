#pragma once

#include <functional>
#include <vector>

namespace clogbase {
	using namespace std;

	class Context {
	public:
		using Action = function<void(Context &)>;
		Context* const parent;

		Context(Context* prev = nullptr);
		~Context();
		
		void operator <<(Action action);
		void commit();
		void rollback();
	private:
		vector<Action> _actions;
	};
}
#pragma once

namespace clogbase {
	class Context {
	public:
		Context const* parent;

		Context(Context* prev = nullptr);
		~Context();
		void commit();
	};
}
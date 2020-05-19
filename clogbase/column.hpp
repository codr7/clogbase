#pragma once

#include <any>
#include <string>

namespace clogbase {
	using namespace std;

	class File;

	enum class Order {LT = -1, EQ = 0, GT = 1};

	class Column {
	public:
		Column(const string& name);
		const string& name() const;
		virtual any load_value(File& in) const = 0;
		virtual void store_value(const any &value, File& out) const = 0;
		virtual Order compare_values(const any& x, const any& y) const = 0;
	private:
		const string _name;
	};
}
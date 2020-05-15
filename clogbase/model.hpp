#pragma once

#include "record.hpp"

namespace clogbase {
    class Context;
    class Table;

    class Model : public Record {
    public:
        Table& table;
        
        Model(Table& table);
        int64_t id() const;
        virtual void store(Context& context);
    };
}
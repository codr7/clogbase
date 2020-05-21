#include "model.hpp"
#include "table.hpp"

namespace clogbase {
    Model::Model(Table& table): table(table) {
    }

    int64_t Model::id() const {
        return get(table.id);
    }

    bool Model::load(RecordId id) {
        return table.load(id, *this);
    }

    void Model::store(Context& context) {
        table.store(*this, context);
    }
}
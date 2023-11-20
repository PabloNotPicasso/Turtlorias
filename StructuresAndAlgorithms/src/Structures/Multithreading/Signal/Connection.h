#pragma once

#include "Slot.h"

namespace Multithreading {

using ConnectionId = size_t;
template<typename Slot>
class Connection {
public:
    Slot slot;
    const ConnectionId connectionId;

    static Connection makeConnection(const Slot& slot)
    {
        return Connection{slot, ++nextConnectionId};
    }

private:
    static ConnectionId nextConnectionId;
};

template<typename Slot>
ConnectionId Connection<Slot>::nextConnectionId = 0;

} // namespace Multithreading
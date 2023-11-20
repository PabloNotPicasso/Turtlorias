#pragma once

#include "Connection.h"
#include "Slot.h"

#include <functional>
#include <list>

namespace Multithreading {

template<typename... Args>
class Signal {
public:
    using SlotT = Slot<Args...>;
    using ConnectionT = Connection<SlotT>;

public:
    Signal() = default;
    virtual ~Signal() = default;

    void operator()(Args... args)
    {
        invoke(args...);
    }

    void invoke(Args... args)
    {
        for (auto [slot, slotId] : m_connections) {
            std::invoke(slot, std::forward<Args>(args)...);
        }
    }

    SimpleCallback simpleBind(Args&&... args)
    {
        // ? copy of args
        return [args..., this]() { this->invoke(args...); };
    }

    ConnectionId connect(SlotT slot)
    {
        auto connection = Connection<SlotT>::makeConnection(slot);
        m_connections.push_back(connection);
        return connection.connectionId;
    }
    void disconnect(ConnectionId connectionId)
    {
        m_connections.remove_if([connectionId](const ConnectionT& connection) {
            return connectionId == connection.connectionId;
        });
    }
    void disconnectAll()
    {
        m_connections.clear();
    }

    size_t num_slots() const
    {
        return m_connections.size();
    }

private:
    /**
     * m_connections operations:
     *  - add
     *  - errase
     *  - save sequence
     *  - for(auto slot : m_connections)
     */
    std::list<ConnectionT> m_connections;
};

} // namespace Multithreading
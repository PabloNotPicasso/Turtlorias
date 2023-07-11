#include "Adapter.h"

#include "3rdParty.h"

Adapter::Adapter() = default;
Adapter::Adapter(Adapter&& other) = default;
Adapter& Adapter::operator=(Adapter&& other) = default;
Adapter::~Adapter() = default;

void Adapter::useOrigin()
{
    pimple->f();
}

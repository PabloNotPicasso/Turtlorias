#include "Any.h"
#include <bits/stdc++.h>

using namespace std;

namespace Structures {

Any::Any() : ind(typeid(nullptr)) { ptr = nullptr; }

Any::~Any() { reset(); }

void Any::reset() {
  if (ind.hash_code() == typeid(int).hash_code()) {
    delete static_cast<int *>(ptr);
  } else if (ind.hash_code() == typeid(string).hash_code()) {
    delete static_cast<string *>(ptr);
  }
  ptr = nullptr;
}

} // namespace Structures
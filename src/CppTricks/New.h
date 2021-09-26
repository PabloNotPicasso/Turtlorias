#pragma once
#include <functional>

// Object allocation and construction
template <typename T> T *createObject() { return new T; }

// Object allocation and construction with noexcept
// std::nothrow param turning new to noexcept
// On bad_alloc  - returns 0
template <typename T> T *createObjectNoExcept() { return new (std::nothrow) T; }

// Object memory allocation, without construction
template <typename T> T *allocateObjectMemory() {
  return (T *)::operator new(sizeof(T));
}

// Object construction on allocated memory ptr
template <typename T> T *constructObject(T *ptr) { return new (ptr) T; }

// Set function to call on bad_alloc
void setBadAllocHandler(std::function<void()> noMemoryCallback) {
  using newHandler = std::new_handler;
  newHandler *handler = noMemoryCallback.target<newHandler>();
  std::set_new_handler(*handler);
}

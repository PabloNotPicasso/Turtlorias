#pragma once
#include <functional>

namespace Structures {

template <typename ObjectType> class SharedPtr {
public:
  SharedPtr(
      ObjectType *ptr = nullptr, std::function<void(ObjectType *)> deleter =
                                     [](ObjectType *obj) { delete obj; });
  SharedPtr(const SharedPtr &to_copy);
  ~SharedPtr();

  SharedPtr &operator=(const SharedPtr &to_copy);

  ObjectType *get() const;

  void reset();

private:
  void try_to_delete();

private:
  ObjectType *m_ptr;
  size_t *m_cnt;
  std::function<void(ObjectType *)> m_deleter;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
template <typename ObjectType>
SharedPtr<ObjectType>::SharedPtr(ObjectType *ptr,
                                 std::function<void(ObjectType *)> deleter)
    : m_ptr(ptr), m_cnt(new size_t(ptr != nullptr)), m_deleter(deleter) {}

template <typename ObjectType>
SharedPtr<ObjectType>::SharedPtr(const SharedPtr &to_copy) {
  m_ptr = to_copy.get();
  m_cnt = to_copy.m_cnt;
  (*m_cnt)++;
}

template <typename ObjectType>
SharedPtr<ObjectType> &
SharedPtr<ObjectType>::operator=(const SharedPtr &to_copy) {
  m_ptr = to_copy.get();
  m_cnt = to_copy.m_cnt;
  (*m_cnt)++;
  return *this;
}

template <typename ObjectType> ObjectType *SharedPtr<ObjectType>::get() const {
  return m_ptr;
}

template <typename ObjectType> void SharedPtr<ObjectType>::SharedPtr::reset() {
  try_to_delete();
}

template <typename ObjectType> SharedPtr<ObjectType>::~SharedPtr() {
  try_to_delete();
}

template <typename ObjectType> void SharedPtr<ObjectType>::try_to_delete() {
  --(*m_cnt);
  if (*m_cnt == 0) {
    m_deleter(m_ptr);
  } else {
    m_cnt = new size_t(0);
  }
  m_ptr = nullptr;
}

} // namespace Structures

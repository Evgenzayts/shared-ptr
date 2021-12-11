// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#ifndef TEMPLATE_MY_SHAREDPTR_H
#define TEMPLATE_MY_SHAREDPTR_H

#include <atomic>
#include <iostream>

template <typename T>
class My_SharedPtr {
 private:
  T* _ptr;
  std::atomic_uint* my_resources;

 public:
  My_SharedPtr();
  explicit My_SharedPtr(T* ptr);
  My_SharedPtr(const My_SharedPtr& r);
  My_SharedPtr(My_SharedPtr&& r) noexcept ;

  auto operator=(const My_SharedPtr& r) -> My_SharedPtr&;
  auto operator=(My_SharedPtr&& r)  noexcept -> My_SharedPtr&;

  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(My_SharedPtr& r);
  [[nodiscard]] auto use_count() const -> size_t;

  ~My_SharedPtr();
};


template <typename T>
My_SharedPtr<T>::My_SharedPtr() {
  _ptr = nullptr;
  my_resources = nullptr;
}

template <typename T>
My_SharedPtr<T>::My_SharedPtr(T* ptr)
    : _ptr(ptr) {
  my_resources = new std::atomic_uint(1);
}

template <typename T>
My_SharedPtr<T>::My_SharedPtr(const My_SharedPtr& r) {
  _ptr = r._ptr;
  my_resources = r.my_resources;
  ++(*my_resources);
}

template <typename T>
My_SharedPtr<T>::My_SharedPtr(My_SharedPtr&& r) noexcept {
  _ptr = r._ptr;
  my_resources = r.my_resources;
  r._ptr = nullptr;
  r.my_resources = nullptr;
}

template <typename T>
auto My_SharedPtr<T>::operator=(const My_SharedPtr& r) -> My_SharedPtr& {
  if (&r == this)
    return *this;

  this->~My_SharedPtr();
  _ptr = r._ptr;
  my_resources = r.my_resources;
  ++(*my_resources);
  return *this;
}

template <typename T>
auto My_SharedPtr<T>::operator=(My_SharedPtr&& r) noexcept -> My_SharedPtr&{
  if (&r == this)
    return *this;

  this->~My_SharedPtr();
  _ptr = r._ptr;
  my_resources = r.my_resources;
  r._ptr = nullptr;
  r.my_resources = nullptr;
  return *this;
}

template <typename T>
My_SharedPtr<T>::operator bool() const {
  return _ptr != nullptr;
}

template <typename T>
auto My_SharedPtr<T>::operator*() const -> T& {
  return *_ptr;
}

template <typename T>
auto My_SharedPtr<T>::operator->() const -> T* {
  return _ptr;
}

template <typename T>
auto My_SharedPtr<T>::get() -> T* {
  return _ptr;
}

template <typename T>
void My_SharedPtr<T>::reset() {
  *this = My_SharedPtr();
}

template <typename T>
void My_SharedPtr<T>::reset(T *ptr) {
  *this = My_SharedPtr(ptr);
}

template <typename T>
void My_SharedPtr<T>::swap(My_SharedPtr &r) {
  if (&r == this)
    return;

  std::swap(_ptr, r._ptr);
  std::swap(my_resources, r.my_resources);
}

template <typename T>
auto My_SharedPtr<T>::use_count() const -> size_t {
  return static_cast<size_t>(*my_resources);
}

template <typename T>
My_SharedPtr<T>::~My_SharedPtr() {
  if (!my_resources)
    return;
  --(*my_resources);
  if (*my_resources == 0) {
    delete _ptr;
    delete my_resources;
  }
  _ptr = nullptr;
  my_resources = nullptr;
}

#endif  // TEMPLATE_MY_SHAREDPTR_H

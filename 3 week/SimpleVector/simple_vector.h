#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(){
	  size = 0;
	  capacity = size;
	  storage = new T[size];
	  storage = nullptr;
  }
  explicit SimpleVector(size_t size_r)
  : size(size_r),
	capacity(size_r)
  {
	  storage = new T[size];
  }
  ~SimpleVector(){
	  delete[] storage;
  }

  T& operator[](size_t index){
	  return *(storage + index);
  }

  T* begin(){
	  return (storage);
  }
  T* end(){
	  return (storage + size);
  }

  const T* begin() const{
	  return (storage);
  }
  const T* end() const{
	  return (storage + size);
  }

  size_t Size() const{
	  return size;
  }
  size_t Capacity() const{
	  return capacity;
  }
  void PushBack(const T& value){
	  if (Size() == 0){
		  storage = new T[++capacity];
	  }
	  else
	  if (Size() == Capacity()){
		  T* temporal = storage;
		  double_my_memory();
		  for (size_t i = 0; i < size; i++){
			  *(storage + i) = *(temporal + i);
		  }
		  delete[] temporal;
	  }

	  *(storage + size) = value;
	  size++;
  }

private:
  size_t capacity = 0;
  size_t size = 0;
  T* storage;

  void double_my_memory(){
	  capacity *= 2;
	  storage = new T[capacity];
  }
};


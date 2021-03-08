#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  if (freed.empty()){
		  T* obj = new T;
		  allocated.insert(obj);
		  return obj;
	  }
	 return allocate();
  }

  T* TryAllocate(){
	  if (freed.empty()){
		  return nullptr;
	  }
	  return allocate();
  }

  void Deallocate(T* object){
	  auto find_res = allocated.find(object);
	  if (allocated.end() == find_res){
		  throw invalid_argument("");
	  }
	  else {
		  allocated.erase(object);
		  freed.push(object);
	  }

  }

  ~ObjectPool(){
	  for (auto& it : allocated){
		  delete it;
	  }

	  while (!freed.empty()){
		  delete freed.front();
		  freed.pop();
	  }
  }

private:
  set<T*> allocated;
  queue<T*> freed;

  T* allocate(){
	T* obj = freed.front();
	freed.pop();
	allocated.insert(obj);
	return obj;
  }

};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}

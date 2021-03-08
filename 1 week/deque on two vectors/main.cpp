//#include "test_runner.h"

#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque{
public:
	Deque() {}
	bool Empty() const {
		if (backs.empty() && fronts.empty())
			return true;
		return false;
	}

	int Size() const {
		return (backs.size() + fronts.size());
	}

	T& operator[](size_t index){
		if (index >= fronts.size()){
			return backs[index - fronts.size()];
		}
	return fronts[fronts.size() - 1 - index];
	}

	const T& operator[](size_t index) const{
		if (index >= fronts.size()){
			return backs[index - fronts.size()];
		}
	return fronts[fronts.size() - 1 - index];
	}

	T& Front() {
		 return fronts.empty() ? backs.front() : fronts.back();
	}

	const T& Front() const{
	  return fronts.empty() ? backs.front() : fronts.back();
	}

	T& Back() {
		return backs.empty() ? fronts.front() : backs.back();
	}

	const T& Back() const{
		return backs.empty() ? fronts.front() : backs.back();
	}

	void PushFront(T t){
		fronts.push_back(t);
	}

	void PushBack(T t){
		backs.push_back(t);
	}

	T& At(size_t index){
	if (Size() < static_cast<int>(index)) {
		throw out_of_range("Check you index, dude");
	}
	if (index >= fronts.size()){
			return backs[index - fronts.size()];
		}
	return fronts[fronts.size() - 1 - index];
	}

	const T& At(size_t index) const{
	if (Size() < index) {
		throw out_of_range("Check you index, dude");
	}
	if (index >= fronts.size()){
		return backs[index - fronts.size()];
		}
	return fronts[fronts.size() - 1 - index] ;
	}

private:
	vector<T> backs, fronts;
};


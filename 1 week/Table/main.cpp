#include "test_runner.h"

#include <vector>
#include <tuple>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template<typename T>
class Table{
public:
	Table(size_t r, size_t c)
	: row(r),
	  column(c)
	{
		vector<vector<T>> tmp (row, vector<T>(column));
		storage = tmp;
	}

	pair<size_t, size_t> Size() const {
		if (!storage.empty() && !storage[0].empty())
			return make_pair(row,  column);
		return make_pair(0, 0);
	}

	void Resize(size_t r, size_t c)
	{
		row = r;
		column = c;
		storage.resize(row);
		for (size_t i = 0; i < row; i++){
			storage[i].resize(column);
		}
	}

	 const vector<T>& operator [] (size_t i) const {
	    return storage[i];
	  }

	  vector<T>& operator [] (size_t i) {
	    return storage[i];
	  }


private:
	size_t row, column;
	vector<vector<T>> storage;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}

#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  ostringstream output;

  if (true)
              PRINT_VALUES(output, 5, "red belt");
          else
              PRINT_VALUES(output, 5, "red belt");
  cout << output.str();
}

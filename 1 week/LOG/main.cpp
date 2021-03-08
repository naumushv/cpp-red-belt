#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }
  bool get_logline(){ return log_line;}
  bool get_logfile(){ return log_file;}
  void add(string& s){  os << s;}
  void Log(const string message){
//	  ostringstream oo(message);
	  os << message;
  }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) { \
	ostringstream mes;															\
	if (logger.get_logline() && logger.get_logfile()) 							\
		mes << __FILE__ << ":" << __LINE__ << " " << message << endl;			\
	else if (logger.get_logline())												\
		mes << "Line " << __LINE__ << " " << message << endl;					\
	else if (logger.get_logfile())												\
		mes << __FILE__ << " " << message << endl;								\
	else mes << message << "\n";												\
	logger.Log(mes.str());														\
}

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");
//  cout << "cout : " << logs.str() << endl;

  l.SetLogFile(true);
  LOG(l, "hello");
//  cout << "cout : " << logs.str() << endl;

  l.SetLogLine(true);
  LOG(l, "hello");
//  cout << "cout : " << logs.str() << endl;

  l.SetLogFile(false);
  LOG(l, "hello");
//  cout << "cout : " << logs.str() << endl;

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:12 hello\n";
  expected += "Line 16 hello\n";
//  cout << "cout expected: " << expected << endl;
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}

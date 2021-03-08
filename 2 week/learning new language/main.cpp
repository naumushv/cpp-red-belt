//#include "profiler.h"
//#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class Learner {
 private:
  vector<string> out;
  set<string> dict;
  bool latest = 0;

 public:
  int Learn(const vector<string>& words) {
    int newWords = dict.size();
	for (const auto& word : words) {
		dict.insert(word);
    }

    newWords = dict.size() - newWords;
    if (newWords > 0) latest = false;
    return newWords;
  }

  const vector<string>& KnownWords() {
	if (!latest){
		out.assign(dict.begin(), dict.end());
		latest = true;
	}
	return out;
  }
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}

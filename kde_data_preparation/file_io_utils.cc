#include <string>
#include <fstream>
#include <algorithm>

#include "file_io_utils.h"

using namespace std;

void tokenize(const string &line, vector<string> &result, string delims) {

  result.clear();

  for (auto bit = line.begin();;) {
    auto eit = find_first_of(bit, line.end(), delims.begin(), delims.end());

    // invariant at this line: 
    // 1. bit points to the start of the next token. 
    // 2. eit points to one past the end of the next token. 
    if (bit == eit) {
      result.push_back("");
    } else {
      result.push_back(string(bit, eit));
    }

    if (eit == line.end()) {
      break;
    } else {
      bit = eit + 1;
    }
  }
}

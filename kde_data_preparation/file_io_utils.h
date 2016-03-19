#ifndef _FILE_IO_UTILS_H_
#define _FILE_IO_UTILS_H_

#include <fstream>
#include <string>
#include <vector>

// given a string (`line`) delimited with some set of characters (`delims`), 
// extract and store each token in `result` in the order they are encountered.
void tokenize(const std::string &line, 
              std::vector<std::string> &result, 
              std::string delims);

#endif

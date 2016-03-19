#include <algorithm>

#include "file_io_utils.h"
#include "NumericCsvReader.h"

NumericCsvReader::NumericCsvReader(const std::string &fname) 
  : NumericCsvReader(fname, ",") {}

NumericCsvReader::NumericCsvReader(
    const std::string &fname, const std::string &delims) : delims_(delims) {

  file_.open(fname);
  if (!file_.is_open()) {
    std::string msg = "Could not open " + fname + ". ";
    throw std::ios_base::failure(msg);
  }

  std::getline(file_, title_);
  std::vector<std::string> col_names;
  tokenize(title_, col_names, delims_);

  curr_values_.resize(col_names.size());
  for (size_t i = 0; i < col_names.size(); ++i) { 
    key_map_[col_names[i]] = i; 
  }
}

bool NumericCsvReader::getline() {

  if (!std::getline(file_, curr_line_)) { return false; } 

  // TODO: can make this more efficient
  std::vector<std::string> col_values;
  tokenize(curr_line_, col_values, delims_);
  for (size_t i = 0; i < col_values.size(); ++i) {
    curr_values_[i] = std::stod(col_values[i]);
  }

  return true;
}

NumericCsvReader::~NumericCsvReader() {
  file_.close();
}


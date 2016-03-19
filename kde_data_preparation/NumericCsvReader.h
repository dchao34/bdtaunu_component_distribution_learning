#ifndef _NUMERICCSVREADER_H_
#define _NUMERICCSVREADER_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

class NumericCsvReader {

  public: 
    NumericCsvReader() = default;
    NumericCsvReader(const NumericCsvReader&) = delete;
    NumericCsvReader(NumericCsvReader&&) = default;
    ~NumericCsvReader();

    NumericCsvReader(const std::string &fname);
    NumericCsvReader(const std::string &fname, const std::string &delims);

    bool getline();

    double& operator[](const std::string&);
    const double& operator[](const std::string&) const;

    const std::string& title() const;
    const std::string& curr_line() const;

  private:
    std::ifstream file_;
    std::string delims_;

    std::string title_;
    std::string curr_line_;

    std::vector<double> curr_values_;
    std::unordered_map<std::string, size_t> key_map_;

};

inline const double& NumericCsvReader::operator[](const std::string &k) const {
  return curr_values_[key_map_.at(k)];
}

inline double& NumericCsvReader::operator[](const std::string &k) {
  return const_cast<double&>(static_cast<const NumericCsvReader&>(*this)[k]);
}

inline const std::string& NumericCsvReader::title() const { return title_; }
inline const std::string& NumericCsvReader::curr_line() const { return curr_line_; }

#endif

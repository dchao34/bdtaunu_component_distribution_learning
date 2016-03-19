#include <iostream>
#include "NumericCsvReader.h"

int main() {
  NumericCsvReader reader("generic.csv");
  while (reader.getline()) {
    reader.getline();
    /*std::cout << reader["rf_useopt_score"] << " ";
    std::cout << reader["event_weight"] << " ";
    std::cout << reader["mc_evttype"] << " ";
    std::cout << std::endl;
    */
  }
  return 0;
}

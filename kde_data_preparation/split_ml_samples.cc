#include <random>
#include <string>
#include <fstream>

#include "NumericCsvReader.h"

int main(int argc, char **argv) {

  std::string data_in_fname("generic.csv");
  std::string train_out_fname("generic.train.csv");
  std::string test_out_fname("generic.test.csv");
  double test_proportion = 0.714;

  std::ofstream train_fout(train_out_fname);
  std::ofstream test_fout(test_out_fname);
  NumericCsvReader reader(data_in_fname);

  train_fout << reader.title() << std::endl;
  test_fout << reader.title() << std::endl;

  std::mt19937 e;
  std::uniform_real_distribution<> d;
  while (reader.getline()) {
    if (d(e) < reader["event_weight"] * test_proportion) {
      test_fout << reader.curr_line() << std::endl;
    } else {
      train_fout << reader.curr_line() << std::endl;
    }
  }

  return 0;
}

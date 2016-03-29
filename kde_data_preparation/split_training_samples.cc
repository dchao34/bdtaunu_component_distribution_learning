#include <random>
#include <string>
#include <fstream>

#include "NumericCsvReader.h"

int main(int argc, char **argv) {

  std::string in_fname("downloaded.train.csv");
  std::string train_bw_out_fname("downloaded.bw.train.csv");
  std::string train_alpha_out_fname("downloaded.alpha.train.csv");
  double scale = 1.0;

  std::ofstream train_bw_fout(train_bw_out_fname);
  std::ofstream train_alpha_fout(train_alpha_out_fname);
  NumericCsvReader reader(in_fname);

  train_bw_fout << reader.title() << std::endl;
  train_alpha_fout << reader.title() << std::endl;

  std::random_device rd;
  std::mt19937 e(rd());
  std::uniform_real_distribution<> d;
  while (reader.getline()) {
    if (d(e) < reader["event_weight"] * scale) {
      train_alpha_fout << reader.curr_line() << std::endl;
    } else {
      train_bw_fout << reader.curr_line() << std::endl;
    }
  }

  return 0;
}

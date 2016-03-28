#include <random>
#include <string>
#include <fstream>
#include <cstdlib>

#include "NumericCsvReader.h"

void print_usage() {
  std::cout << "usage: ";
  std::cout << "./prepare_training_data_format <mc_evttype> ";
  std::cout << "[dither? 1 or 0] [down sample proportion] " << std::endl;
}

int main(int argc, char **argv) {

  int mc_evttype = 0;
  bool do_dither = false;
  double down_sample = 1.0;
  if (argc == 4) {
    mc_evttype = atoi(argv[1]);
    do_dither = atoi(argv[2]);
    down_sample = atof(argv[3]);
  } else if (argc == 3) {
    mc_evttype = atoi(argv[1]);
    do_dither = atoi(argv[2]);
    down_sample = 1.0;
  } else if (argc == 2) {
    mc_evttype = atoi(argv[1]);
    do_dither = false;
    down_sample = 1.0;
  } else {
    print_usage();
    return 1;
  }

  double dither_precision = 1e-3;

  std::string in_fname("bw.train.csv");
  std::string out_fname = "evttype" + std::to_string(mc_evttype) + ".train.csv";

  std::random_device rd;
  std::mt19937 e(rd());
  std::uniform_real_distribution<> d, d_dith(-0.5, 0.5);

  NumericCsvReader reader(in_fname);
  std::ofstream fout(out_fname);

  double dither1 = 0.0, dither2 = 0.0;
  while (reader.getline()) {

    if (static_cast<int>(reader["mc_evttype"]) != mc_evttype) { continue; }
    if (d(e) > down_sample) { continue; }

    if (do_dither) { dither1 = d_dith(e); dither2 = d_dith(e); }

    fout << reader["rf_useopt_score"] + dither1*dither_precision << " ";
    fout << reader["rf_dvsdstar_sigmc_score"]  + dither2*dither_precision << " ";
    fout << reader["event_weight"] << " ";
    fout << std::endl;

  }

  return 0;

}

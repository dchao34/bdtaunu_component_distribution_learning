#include <random>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include <boost/program_options.hpp>

#include "NumericCsvReader.h"

namespace po = boost::program_options;

void prepare_data_format(const po::variables_map &vm);

int main(int argc, char **argv) {

  try {

    // define program options 
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration options");
    config.add_options()
        ("in_fname", po::value<std::string>(), "input file. this is typically a file downloaded using "
                                               "`download_(train|test)_data.sql`. ")
        ("out_fname", po::value<std::string>(), "output file name. formatted for kernel desnity estimation.  ")

        ("filter_mc_evttype", po::value<bool>(), "if true, consider only input records with "
                                                 "the specified `mc_evttype`. else consider all records. ")
        ("mc_evttype_file_prefix", po::value<std::string>()->default_value("evttype"), 
                                                 "file prefix when filter_mc_evttype is true. ")
        ("mc_evttype", po::value<int>()->default_value(0), "`mc_evttype` to consider. active only when "
                                                           "`filter_mc_evttype` is true. ")

        ("use_event_weight", po::value<bool>(), "if true, use the event_weight provided. else set to 1.0. ")

        ("do_dither", po::value<bool>()->default_value(true), "whether to dither the data. ")
        ("dither_precision", po::value<double>()->default_value(1e-3), "dither precision. ")

        ("down_sample", po::value<double>()->default_value(1.0), "down sample proportion. ")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("config_file", po::value<std::string>(), "name of a configuration file. ")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config);

    po::options_description visible;
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("config_file", -1);

    // parse program options and configuration file
    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
          options(cmdline_options).positional(p).run(), vm);
    notify(vm);

    if (vm.count("help") || !vm.count("config_file")) {
      std::cout << std::endl;
      std::cout << "Usage: prepare_data_format [options] config_fname" << std::endl;
      std::cout << visible << "\n";
      return 0;
    }

    std::ifstream fin(vm["config_file"].as<std::string>());
    if (!fin) {
      std::cout << "cannot open config file: ";
      std::cout << vm["config_file"].as<std::string>() << std::endl;
      return 0;
    }

    store(parse_config_file(fin, config_file_options), vm);
    notify(vm);

    prepare_data_format(vm);

  } catch(std::exception& e) {

    std::cerr << "error: " << e.what() << "\n";
    return 1;

  } catch(...) {

    std::cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;


}

void prepare_data_format(const po::variables_map &vm) {

  // read configuration parameters
  std::string in_fname = vm["in_fname"].as<std::string>();
  std::string out_fname = vm["out_fname"].as<std::string>();

  bool filter_mc_evttype = vm["filter_mc_evttype"].as<bool>();
  std::string mc_evttype_file_prefix = vm["mc_evttype_file_prefix"].as<std::string>();
  int mc_evttype = vm["mc_evttype"].as<int>();

  bool do_dither = vm["do_dither"].as<bool>();
  double dither_precision = vm["dither_precision"].as<double>();
  double down_sample = vm["down_sample"].as<double>();

  bool use_event_weight = vm["use_event_weight"].as<bool>();

  // setup utilities and parameters
  std::random_device rd;
  std::mt19937 e(rd());
  std::uniform_real_distribution<> down_sampler, ditherer(-0.5, 0.5);
  
  if (filter_mc_evttype) { 
    out_fname = 
      mc_evttype_file_prefix + std::to_string(mc_evttype) + "." + out_fname; 
  }

  // main procedure
  NumericCsvReader reader(in_fname);
  std::ofstream fout(out_fname);
  fout << std::setprecision(12) << std::fixed;

  double dither_x = 0.0, dither_y = 0.0;
  while (reader.getline()) {

    // filter by mc_evttype if requested
    if (filter_mc_evttype && 
        static_cast<int>(reader["mc_evttype"]) != mc_evttype) { continue; }

    // down sample
    if (down_sampler(e) > down_sample) { continue; }

    // dither the data
    if (do_dither) { dither_x = ditherer(e); dither_y = ditherer(e); }

    // write output
    fout << reader["rf_useopt_score"] + dither_x*dither_precision << " ";
    fout << reader["rf_dvsdstar_sigmc_score"]  + dither_y*dither_precision << " ";
    
    if (use_event_weight) {
      fout << reader["event_weight"] << " ";
    } else {
      fout << "1.0 ";
    }
    fout << std::endl;

  }
}

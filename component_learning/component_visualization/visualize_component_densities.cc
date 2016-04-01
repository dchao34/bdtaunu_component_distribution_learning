#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

#include <KernelDensity.h>

#include <utils/visualization_utils.h>

namespace {
  using KernelType = bbrcit::EpanechnikovProductKernel2d<float>;
  using KernelDensityType = bbrcit::KernelDensity<2,KernelType,double>;
  using KdtreeType = KernelDensityType::KdtreeType;
  using DataPointType = KernelDensityType::DataPointType;
}

// construct (adapted) kernel density using data in `fname`
KernelDensityType construct_kernel_density(
  std::vector<DataPointType> points, double alpha, 
  double pilot_bandwidth_x, double pilot_bandwidth_y, 
  double adapt_bandwidth_x, double adapt_bandwidth_y, 
  double rel_tol, double abs_tol, 
  int leaf_max, int block_size) {

  KernelDensityType kde(std::move(points), leaf_max);
  kde.kernel().set_bandwidths(pilot_bandwidth_x, pilot_bandwidth_y);
  kde.adapt_density(alpha, rel_tol, abs_tol, block_size);
  kde.kernel().set_bandwidths(adapt_bandwidth_x, adapt_bandwidth_y);

  return kde;
}


int main(int argc, char **argv) {

#ifdef __CUDACC__
  cudaSetDevice(0);
#endif
  double rel_tol = 1e-6, abs_tol = 1e-8;
  int leaf_max = 32768;
  int gpu_block_size = 128;

  std::chrono::high_resolution_clock::time_point start_total, end_total;
  start_total = std::chrono::high_resolution_clock::now();

  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double> elapsed;

  std::cout << "+ reading data \n" << std::endl;
  std::vector<DataPointType> reference_points 
    = read_2dpoints<DataPointType>("data/evttype1.bw.train.csv");

  std::cout << "+ constructing kde " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde = 
    construct_kernel_density(reference_points, 
                             0.5, 0.0032, 0.036, 0.0038, 0.059, 
                             rel_tol, abs_tol, leaf_max, gpu_block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "+ evaluating kde over grid" << std::endl;
  double start_x = -0.005, end_x = 0.11; int steps_x = 100;
  double start_y = -0.05, end_y = 1.05; int steps_y = 100;
  std::vector<DataPointType> grid2d;
  generate_2dgrid(grid2d, start_x, end_x, steps_x,
                          start_y, end_y, steps_y);

  start = std::chrono::high_resolution_clock::now();
  kde.eval(grid2d, rel_tol, abs_tol, leaf_max);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  running time: " << elapsed.count() << " s. \n" << std::endl;

  std::cout << "+ writing files for matplotlib. \n" << std::endl;
  std::ofstream fout;
  fout.open("scatter.csv");
  write_2dscatter_data(fout, reference_points);
  fout.close();

  fout.open("kde2d.csv");
  write_2dgrid_values(fout, grid2d, start_x, end_x, steps_x,
                                    start_y, end_y, steps_y);
  fout.close();

  std::cout << "+ done. \n" << std::endl;
  end_total = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "  total running time: " << elapsed.count() << " s. \n" << std::endl;


  return 0;

}


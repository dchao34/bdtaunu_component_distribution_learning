#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include <KernelDensity.h>

namespace {
  using KernelType = bbrcit::EpanechnikovProductKernel2d<float>;
  using KernelDensityType = bbrcit::KernelDensity<2,KernelType,double>;
  using DataPointType = KernelDensityType::DataPointType;
  double rel_tol = 1e-6;
  double abs_tol = 1e-8;
}

template<typename PointT>
std::vector<PointT> read_data2d(const std::string &fname) {
  std::vector<PointT> points;
  std::ifstream fin(fname);
  double x, y, w;
  while (fin >> x >> y >> w) {
    points.push_back({{x, y}, {w}});
  }
  return points;
}

KernelDensityType::KdtreeType
construct_query_tree(const std::string fname, int leaf_max) {
  std::vector<DataPointType> points = 
    read_data2d<DataPointType>(fname);
  KernelDensityType::KdtreeType qtree(std::move(points), leaf_max);
  return qtree;
}

KernelDensityType
construct_kernel_density(
    const std::string fname, int leaf_max, 
    double pilot_bandwidth_x, double pilot_bandwidth_y, 
    double adapt_bandwidth_x, double adapt_bandwidth_y, 
    double alpha, int block_size) {
  std::vector<DataPointType> points = 
    read_data2d<DataPointType>(fname);

  KernelDensityType kde(std::move(points), leaf_max);
  kde.kernel().set_bandwidths(pilot_bandwidth_x, pilot_bandwidth_y);
  kde.adapt_density(alpha, rel_tol, abs_tol, block_size);
  kde.kernel().set_bandwidths(adapt_bandwidth_x, adapt_bandwidth_y);
  return kde;
}

template <int D> 
class PointEvalResults {

  public: 
    static constexpr int dim() { return D; }

    friend std::ostream& operator<<(
        std::ostream &os, const PointEvalResults<D> &p) {
      for (size_t i = 0; i < D; ++i) { 
        os << p[i] << " ";
      }
      return os;
    }

  public: 
    PointEvalResults() : eval_(D, 0.0) {}
    PointEvalResults(const PointEvalResults<D>&) = default;
    PointEvalResults(PointEvalResults<D>&&) = default;
    ~PointEvalResults() = default;
    PointEvalResults& operator=(const PointEvalResults<D>&) = default;
    PointEvalResults& operator=(PointEvalResults<D>&&) = default;

    const double& operator[](size_t i) const {
      return eval_.at(i);
    }
    double& operator[](size_t i) {
      return const_cast<double&>(
          static_cast<const PointEvalResults<D>&>(*this)[i]);
    }

  private:
    std::vector<double> eval_;
};

template<int D>
void copy_results(
    const KernelDensityType::KdtreeType &qtree, 
    std::vector<PointEvalResults<D>> &results, 
    size_t c) {

  if (qtree.size() != results.size()) {
    throw std::out_of_range(
        "result vector should have length equivalent "
        "to the number of points in the query tree. ");
  }

  for (size_t i = 0; i < results.size(); ++i) {
    results[i][c] = qtree.points()[i].attributes().value();
  }

}


int main() {

  std::chrono::high_resolution_clock::time_point start_total, end_total;
  std::chrono::duration<double> elapsed_total;

  start_total = std::chrono::high_resolution_clock::now();

  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double, std::milli> elapsed;

  int leaf_max = 32768;
  int block_size = 128;
  double alpha = 0.5;

  std::cout << "+ building query tree. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType::KdtreeType qtree = 
    construct_query_tree("data/alpha.train.csv", leaf_max);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;



  std::vector<PointEvalResults<5>> eval_results(qtree.size());

  std::cout << "+ building evttype1 kde. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde1 = 
    construct_kernel_density(
        "data/evttype1.bw.train.csv", leaf_max, 
        0.003, 0.036, 0.0032, 0.068, alpha, block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;

  std::cout << "+ evaluating evttype1 kde over queries. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  kde1.eval(qtree, rel_tol, abs_tol, block_size);
  copy_results(qtree, eval_results, 0);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;




  std::cout << "+ building evttype2 kde. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde2 = 
    construct_kernel_density(
        "data/evttype2.bw.train.csv", leaf_max, 
        0.0032, 0.03, 0.0023, 0.055, alpha, block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;

  std::cout << "+ evaluating evttype2 kde over queries. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  kde2.eval(qtree, rel_tol, abs_tol, block_size);
  copy_results(qtree, eval_results, 1);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;




  std::cout << "+ building evttype3 kde. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde3 = 
    construct_kernel_density(
        "data/evttype3.bw.train.csv", leaf_max, 
        0.00048, 0.03, 0.000518, 0.055, alpha, block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;

  std::cout << "+ evaluating evttype3 kde over queries. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  kde3.eval(qtree, rel_tol, abs_tol, block_size);
  copy_results(qtree, eval_results, 2);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;





  std::cout << "+ building evttype4 kde. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde4 = 
    construct_kernel_density(
        "data/evttype4.bw.train.csv", leaf_max, 
        0.00041, 0.025, 0.00032, 0.048, alpha, block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;

  std::cout << "+ evaluating evttype4 kde over queries. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  kde4.eval(qtree, rel_tol, abs_tol, block_size);
  copy_results(qtree, eval_results, 3);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;





  std::cout << "+ building evttype5 kde. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  KernelDensityType kde5 = 
    construct_kernel_density(
        "data/evttype5.bw.train.csv", leaf_max, 
        0.00005, 0.025, 0.000028, 0.055, alpha, block_size);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;

  std::cout << "+ evaluating evttype5 kde over queries. " << std::endl;
  start = std::chrono::high_resolution_clock::now();
  kde5.eval(qtree, rel_tol, abs_tol, block_size);
  copy_results(qtree, eval_results, 4);
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start; 
  std::cout << "  running time: " << elapsed.count() << " ms. \n" << std::endl;




  std::cout << "+ writing results. \n" << std::endl;
  std::ofstream fout("results.csv");
  for (size_t i = 0; i < eval_results.size(); ++i) {
    fout << eval_results[i] << std::endl;
  }


  end_total = std::chrono::high_resolution_clock::now();
  elapsed_total = end_total - start_total;
  std::cout << "=> total running time: " << elapsed_total.count() << " s. \n" << std::endl;

  return 0;
}

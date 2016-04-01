#include <vector>
#include <cmath>
#include <ostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <utility>

template<typename PointT>
std::vector<PointT> read_2dpoints(const std::string &fname) {

  // open file
  std::ifstream fin(fname);
  if (!fin) {
    throw std::ios_base::failure("cannot open file " + fname + ". ");
  }

  // populate points
  std::vector<PointT> points;
  double x1 = 0.0, x2 = 0.0, w = 1.0;
  while (fin >> x1 >> x2 >> w) {
    points.push_back({{x1,x2}, {w}});
  }

  return points;

}

template<typename PointT>
bool ReverseExactLexicoLess(const PointT &lhs, const PointT &rhs) {
  int i = 0; while (i < lhs.dim() && lhs[lhs.dim()-i-1] == rhs[lhs.dim()-i-1]) { ++i; }
  return i != lhs.dim() && lhs[lhs.dim()-i-1] < rhs[lhs.dim()-i-1];
}


template <typename PointT>
void generate_2dgrid(std::vector<PointT> &grid, 
                     double start_x, double end_x, int steps_x,
                     double start_y, double end_y, int steps_y) {
  
  grid.clear();

  double delta_x = (end_x-start_x)/steps_x;
  double delta_y = (end_y-start_y)/steps_y;
  for (int j = 0; j <= steps_y; ++j) {
    for (int i = 0; i <= steps_x; ++i) {
      grid.push_back({{start_x+i*delta_x, start_y+j*delta_y}});
    }
  }

  return;
}


template<typename PointT>
void write_2dgrid_values(std::ostream &os, std::vector<PointT> &point_values,
                         double start_x, double end_x, int steps_x, 
                         double start_y, double end_y, int steps_y) {

  std::sort(point_values.begin(), point_values.end(), ReverseExactLexicoLess<PointT>);
  std::vector<double> values(point_values.size());
  for (size_t i = 0; i < point_values.size(); ++i) {
    values[i] = point_values[i].attributes().value();
  }
  write_2dgrid_values(os, static_cast<const std::vector<double>>(values), 
                      start_x, end_x, steps_x, start_y, end_y, steps_y);
}


inline 
void write_2dgrid_values(std::ostream &os, std::vector<double> &values,
                         double start_x, double end_x, int steps_x, 
                         double start_y, double end_y, int steps_y) {
  write_2dgrid_values(os, static_cast<const std::vector<double>>(values), 
                      start_x, end_x, steps_x, start_y, end_y, steps_y);
}


template<typename PointT>
void write_2dscatter_data(std::ostream &os, const std::vector<PointT> &data) {
  for (const auto &p : data) { os << p[0] << " " << p[1] << std::endl; }
}

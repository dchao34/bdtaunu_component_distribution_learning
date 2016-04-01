#ifndef __VISUALIZATION_UTILS_H__
#define __VISUALIZATION_UTILS_H__

#include <vector>
#include <ostream>
#include <string>
#include <utility>

// read weighted 2d points from file `fname`. each row is corresponds to 
// a point. the last column is the weight; otherwise, the value in column `i`
// is the value of coodinate `i`. 
template<typename PointT>
std::vector<PointT> read_2dpoints(const std::string &fname);

// returns true if lhs < rhs reverse lexicographically
template<typename PointT>
bool ReverseExactLexicoLess(const PointT &lhs, const PointT &rhs);

// generate a 2-dimensional grid of points. 
template <typename PointT>
void generate_2dgrid(std::vector<PointT> &grid, 
                     double start_x, double end_x, int steps_x,
                     double start_y, double end_y, int steps_y);

// write 2-dimensional values attached to grid points generated using
// a call to `generate_2dgrid(...)` with arguments `(start|end|steps)_(x|y)`.
void write_2dgrid_values(std::ostream &os, const std::vector<double> &values,
                         double start_x, double end_x, int steps_x, 
                         double start_y, double end_y, int steps_y);
template<typename PointT>
void write_2dgrid_values(std::ostream &os, std::vector<PointT> &point_values,
                         double start_x, double end_x, int steps_x, 
                         double start_y, double end_y, int steps_y);


// write 2-dimensional points in `data` to output stream `os`. 
// each row corresponds to a single point whose value in the 
// `i`th dimension corresponds to the value in column `i`. 
template<typename PointT>
void write_2dscatter_data(std::ostream &os, const std::vector<PointT> &data);


#include "visualization_utils_impl.h"

#endif

#ifndef SENSITIVITY_UTILS_H__
#define SENSITIVITY_UTILS_H__

#include <vector>
#include <ostream>
#include <string>
#include <utility>

// read weighted 2d points from file `fname`. each row is corresponds to 
// a point. the last column is the weight; otherwise, the value in column `i`
// is the value of coodinate `i`. 
template<typename PointT>
std::vector<PointT> read_2dpoints(const std::string &fname);


#include "sensitivity_utils_impl.h"

#endif

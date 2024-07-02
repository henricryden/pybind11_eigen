#pragma once
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>

template<typename T, int rank> void modifyTensor(Eigen::Tensor<T, rank>& tensor, const T val);

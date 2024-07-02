#include <advancedRecon.h>
#include <iostream>
template<typename T, int rank>
void modifyTensor(Eigen::Tensor<T, rank>& tensor, const T val) {
    tensor.template chip<0>(0).setConstant(val);
    return;
}

template void modifyTensor<float, 3>(Eigen::Tensor<float, 3>& tensor, float val);
template void modifyTensor<float, 4>(Eigen::Tensor<float, 4>& tensor, float val);

using Scalar = std::complex<float>;
template void modifyTensor<CplxScalar, 3>(Eigen::Tensor<CplxScalar, 3>& tensor, CplxScalar val);
template void modifyTensor<CplxScalar, 4>(Eigen::Tensor<CplxScalar, 4>& tensor, CplxScalar val);
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>
#include <advancedRecon.h>

template<typename T, int rank>
Eigen::Tensor<T, rank> generateTensor(std::array<Eigen::Index, rank> sizes) {
    Eigen::Tensor<T, rank> out(sizes);
    out.setRandom();
    return out;
}

int main() {
    constexpr int rank = 3;
    
    Eigen::Tensor<float, rank> B = generateTensor<float, rank>({2,3,4});

    std::cout << "tensor:\n" << B << std::endl;

    modifyTensor(B, 2.9f);
    std::cout << "Modified tensor:\n" << B << std::endl;
    return 0;
}

#include <iostream>
#include <complex>
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "pybind11/eigen/matrix.h"
#include "pybind11/eigen/tensor.h"

#include <advancedRecon.h>

namespace py = pybind11;
using Scalar = float;
using CplxScalar = std::complex<Scalar>;


template <typename T, int rank>
Eigen::Tensor<T, rank> numpyToTensor(py::array_t<T> array) {
    // Request a buffer descriptor from the NumPy array
    py::buffer_info buf = array.request();
    
    for (int i = 0; i < 10; i++) {
       // std::cout << "numpy[" << i << "] = " << array(i) << std::endl;
    }
    
    if (buf.ndim != rank) {
        std::ostringstream oss;
        oss << "Invalid rank: " << buf.ndim << ". Rank must be " << rank << ".";
        throw std::runtime_error(oss.str());
    }
    if (buf.itemsize != sizeof(T)) {
        std::ostringstream oss;
        oss << "Invalid item size: " << buf.itemsize << ". Item size must be " << sizeof(T) << ".";
        throw std::runtime_error(oss.str());
    }

    for (const auto el : buf.strides) {
        std::cout << "stride " << el << std::endl;
    }
    
    // Prepare dimensions
    std::array<Eigen::Index, rank> dimensions;
    for (int i = 0; i < rank; ++i) {
        dimensions[i] = buf.shape[i];
    }

    // Map the data
    T* ptr = static_cast<T*>(buf.ptr);
    std::cout << "pointer is " << ptr << " with itemsize " << buf.itemsize << std::endl;
    Eigen::TensorMap<Eigen::Tensor<T, rank>> tensor(ptr, dimensions);
    
    // Copy the data to an Eigen Tensor
    Eigen::Tensor<T, rank> out = tensor;
    
    return out;
}


template<typename T, int rank>
py::array_t<T> tensorToNumpy(const Eigen::Tensor<T, rank>& tensor) {
    std::array<ssize_t, rank> shape;
    std::array<ssize_t, rank> strides;

    for (int i = 0; i < rank; ++i) {
        shape[i] = tensor.dimension(i);
    }

    ssize_t stride = sizeof(T);
    for (int i = rank - 1; i >= 0; --i) {
        strides[i] = stride;
        stride *= tensor.dimension(i);
    }

    return py::array_t<T>(shape, strides, tensor.data());
}

py::array_t<CplxScalar> fancyFunction(py::array_t<CplxScalar> numpyArray) {
    // Copy input to Eigen Tensor
    Eigen::Tensor<CplxScalar, 3> someTensor = numpyToTensor<CplxScalar, 3>(numpyArray);
    
    // Do something with it, perhaps fancier than this...
    using namespace std::complex_literals;
    modifyTensor(someTensor, 1.0f + 2.6if);
    
    // Convert back to numpy and return. No copy.
    py::array_t<CplxScalar> out = tensorToNumpy(someTensor);
    return out;
}


PYBIND11_MODULE(advanced_recon_py, m) {
    m.doc() = "Here are some advanced reconstruction routines";

    m.def("fancyFunction", &fancyFunction, "Separate fat water");

}

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
Eigen::Tensor<T, rank, Eigen::ColMajor> numpyToTensor(py::array_t<T, py::array::c_style | py::array::forcecast> array) {
    // Request a buffer descriptor from the NumPy array
    py::buffer_info buf = array.request();
    
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
    
    // Create an Eigen::Tensor with the same dimensions as the NumPy array
    Eigen::DSizes<Eigen::DenseIndex, rank> dimensions;
    Eigen::array<Eigen::DenseIndex, rank> strides;
    Eigen::array<int, rank> shuffles;
    for (int i = 0; i < rank; ++i) {
        dimensions[i] = buf.shape[i];
        strides[i] = buf.strides[i] / sizeof(T);
        shuffles[i] = rank - 1 - i;
    }
    Eigen::Tensor<T, rank, Eigen::ColMajor> out(dimensions);

    // Copy data from NumPy array to Eigen::Tensor using a map
    T* ptr = static_cast<T*>(buf.ptr);
    Eigen::TensorMap<Eigen::Tensor<T, rank, Eigen::RowMajor>> map(ptr, dimensions);
    out = map.shuffle(shuffles).swap_layout();

    return out;
}

template <typename T, int rank>
py::array_t<T> tensorToNumpy(const Eigen::Tensor<T, rank, Eigen::ColMajor>& tensor) {
    // Get the dimensions of the tensor
    const auto& dims = tensor.dimensions();
    
    // Create a vector to hold the shape for NumPy
    std::vector<ssize_t> shape(rank);
    std::vector<ssize_t> strides(rank);
    
    // Calculate the strides and total size
    ssize_t total_size = 1;
    for (int i = rank - 1; i >= 0; --i) {
        shape[i] = dims[i];
        strides[i] = total_size * sizeof(T);
        total_size *= dims[i];
    }

    // Create a NumPy array
    py::array_t<T> numpy_array(shape, strides);

    // Get a pointer to the NumPy array's data
    auto buf = numpy_array.request();
    T* ptr = static_cast<T*>(buf.ptr);

    // Create an Eigen::TensorMap of the NumPy data (as RowMajor)
    Eigen::TensorMap<Eigen::Tensor<T, rank, Eigen::RowMajor>> numpy_tensor(ptr, dims);

    // Create shuffling array
    Eigen::array<int, rank> shuffle;
    for (int i = 0; i < rank; ++i) {
        shuffle[i] = rank - 1 - i;
    }

    // Copy data from Eigen tensor to NumPy array, with layout conversion
    numpy_tensor = tensor.shuffle(shuffle).swap_layout();

    return numpy_array;
}


py::array_t<Scalar> fancyFunction(py::array_t<Scalar> numpyArray, Scalar value) {
    // Copy input to Eigen Tensor
    Eigen::Tensor<Scalar, 3> someTensor = numpyToTensor<Scalar, 3>(numpyArray);
    
    // Do something with it, perhaps fancier than this...
    modifyTensor(someTensor, value);
    
    // Convert back to numpy and return. Makes a copy.
    py::array_t<Scalar> out = tensorToNumpy(someTensor);
    return out;
}


PYBIND11_MODULE(advanced_recon_py, m) {
    m.doc() = "Here are some advanced reconstruction routines";

    m.def("fancyFunction", &fancyFunction, "Manipulate a numpy array", py::arg("numpyArray"), py::arg("value"));

}

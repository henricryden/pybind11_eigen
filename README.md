# pybind11 with Eigen
## Overview
This repository demonstrates how to integrate C++ code with NumPy using  [pybind11](https://pybind11.readthedocs.io) and [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) tensors.

The repository has a Dockerfile and uses cmake.



## Get started


#### 1. Clone this repository
```
git clone https://github.com/henricryden/pybind11_eigen.git
```

#### 2. Build the Docker image
```
cd pybind11_eigen/docker
docker build . -t pybind11_eigen
```

#### 3. Start a container
```
docker run -v <PATH_TO_THIS_REPO>:/code/ --rm -it --hostname pybind11_eigen --workdir /code pybind11_eigen
```

#### 4. Build the source (terminal should prefix with `(pybind-310) root@pybind11_eigen:/code#`):

```
mkdir build
cd build
cmake ../src
make
exit
```

#### 5. Try the python wrapper
```
python ./python_project/test_wrapper.py
```


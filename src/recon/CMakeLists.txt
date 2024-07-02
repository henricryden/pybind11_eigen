add_library(advancedRecon STATIC advancedRecon.cpp)
target_link_libraries(advancedRecon PUBLIC Eigen3::Eigen)

if(PY_WRAPPERS)
    pybind11_add_module(advanced_recon_py advancedRecon_py.cpp)
    target_link_libraries(advanced_recon_py PUBLIC pybind11::module advancedRecon)
endif()
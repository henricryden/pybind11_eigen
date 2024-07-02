add_library(advancedRecon STATIC advancedRecon.cpp)
target_link_libraries(advancedRecon PUBLIC Eigen3::Eigen)

if(PY_WRAPPERS)
    pybind11_add_module(advanced_recon_py advancedRecon_py.cpp)
    set_target_properties(advanced_recon_py PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../python_project/extern/_impl)

    target_link_libraries(advanced_recon_py PUBLIC pybind11::module advancedRecon)
endif()
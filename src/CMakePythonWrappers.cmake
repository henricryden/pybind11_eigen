
set(PY_VERSION "3.10" CACHE STRING "Python version for wrappers")
set(PY_ENV_PATH "/opt/micromamba/envs/pybind-${PY_VERSION}" CACHE STRING "Python environment path")

if(PY_WRAPPERS)
  set(Python3_ROOT_DIR -${PY_VERSION})
  set(Python_EXECUTABLE ${Python3_ROOT_DIR}/bin/python)
  find_package(Python3 ${PY_VERSION} EXACT COMPONENTS Interpreter Development)

  execute_process(
      COMMAND ${Python3_ROOT_DIR}/bin/python -m pybind11 --includes # ->  something like "/opt/micromamba/envs/pybind-310/include/python3.10; /opt/micromamba/envs/pybind-310/lib/python3.10/site-packages/pybind11/include"
      OUTPUT_VARIABLE INCLUDE_PYBIND
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  execute_process(
      COMMAND python${PY_VERSION}-config --includes # -> something like "/usr/include/python3.10"
      OUTPUT_VARIABLE INCLUDE_PYCONFIG
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(CMAKE_POSITION_INDEPENDENT_CODE ON) # fPIC

  cmake_print_variables(Python3_SITELIB Python_EXECUTABLE DPython3_EXECUTABLE INCLUDE_PYCONFIG)
  find_package(pybind11 CONFIG REQUIRED HINTS "${Python3_SITELIB}")

  set(INCLUDE_PYBIND ${INCLUDE_PYCONFIG} ${INCLUDE_PYBIND} )
  cmake_print_variables(INCLUDE_PYBIND)
endif()


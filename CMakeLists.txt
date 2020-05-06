cmake_minimum_required(VERSION 3.9)
project(aff)
set(PYBIND11_CPP_STANDARD -std=c++11)
set(CMAKE_CXX_FLAGS "-Wall -O3 -mtune=native -march=native")

find_package(PkgConfig)

set(Python_ADDITIONAL_VERSIONS 3.7)

find_package(PythonInterp)
if(NOT PYTHONINTERP_FOUND)
    message(FATAL_ERROR "Unable to find PythonInterp")
endif()

pkg_check_modules(PYTHON python-3.7)
if(PYTHON_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    link_directories(${PYTHON_LIBRARY_DIRS})
    message("PYTHON_INCLUDE_DIRS: ${PYTHON_INCLUDE_DIRS}")
    message("PYTHON_LIBRARY_DIRS: ${PYTHON_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "Unable to find Python")
endif()

find_package(pybind11 REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(./ffstream_cpp)
include_directories(../../dim_reduction/streaming-vis-pca)


pybind11_add_module(ipca_aff_cpd_cpp SHARED ./ffstream_cpp/utils.cpp ./ffstream_cpp/detector.cpp ./ffstream_cpp/fff.cpp ./ffstream_cpp/aff.cpp ./ffstream_cpp/affcd.cpp ../../dim_reduction/streaming-vis-pca/inc_pca.cpp ipca_aff_cpd.cpp ipca_aff_cpd_wrap.cpp)


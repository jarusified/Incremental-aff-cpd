## C++ Library and Python Module for An incremental PCA-based change point detection (CPD) with adaptive forgetting factor for multivariate streaming data

This CPD algorithm is developed with the ideas of PCA-based CPD [1] and CPD with adaptive forgetting factor (AFF) [2]. Also, we have improved the detection by applying incremental PCA instead of ordinary PCA.
For more details, please refer to Kesavan et al., "A Visual Analytics Framework for Reviewing Streaming Performance Data", 2020. 

[1] A. Qahtan, B. Alharbi, S. Wang, and X. Zhang,
A PCA-Based Change Detection Framework for Multidimensional Data Streams,
In Proc. ACM SIGKDD, pp.935--944, 2015.

[2] D. A. Bodenham and N. M. Adams, Continuous monitoring for changepoints in data
streams using adaptive estimation, Statistics and Computing, vol. 27, no. 5,
pp.1257--1270, 2017.

-----

Requirements
-----
* C++11 compiler, Python3, Eigen3, Pybind11, Numpy

* Note: Tested on macOS Mojave and Ubuntu 18.0.4 LTS.

Setup
-----
#### Mac OS with Homebrew
* Install libraries

    `brew install python3`

    `brew install pybind11`

    `pip3 install numpy`

* Build with cmake

    `mv /path/to/directory-of-CmakeLists.txt`

    `cmake .`

    `make`

* This generates a shared library, "ipca_aff_cpd_cpp.xxxx.so" (e.g., ipca_aff_cpd_cpp.cpython-37m-darwin.so).

* Install the modules with pip3.

    `pip3 install .`

#### Linux (tested on Ubuntu 18.0.4 LTS)
* Install libraries

    `sudo apt update`

    `sudo apt install libeigen3-dev`

    `sudo apt install python3-pip python3-dev`

    `pip3 install pybind11`

    `pip3 install numpy`

* Move to 'ipca_aff_cpd' directory then compile with:

    ``c++ -O3 -Wall -mtune=native -march=native -shared -std=c++11 -I/usr/include/eigen3/ -I./ffstream_cpp -I../../dim_reduction/streaming-vis-pca -fPIC `python3 -m pybind11 --includes` ./ffstream_cpp/utils.cpp ./ffstream_cpp/detector.cpp ./ffstream_cpp/fff.cpp ./ffstream_cpp/aff.cpp ./ffstream_cpp/affcd.cpp ../../dim_reduction/streaming-vis-pca/inc_pca.cpp ipca_aff_cpd.cpp ipca_aff_cpd_wrap.cpp -o ipca_aff_cpd_cpp`python3-config --extension-suffix` ``

* This generates a shared library, "ipca_aff_cpd_cpp.xxxx.so" (e.g., pca_aff_cpd_cpp.cpython-37m-x86_64-linux-gnu.so).

* Install the modules with pip3.

    `pip3 install .`

Usage
-----
* With Python3
    * Import the installed module from python (e.g., `from ipca_aff_cpd import IPCAAFFCPD`). See sample.py for examples.

* With C++
    * Include header files (ipca_aff_cpd.hpp) in C++ code with cpp files (ipca_aff_cpd.cpp).

******

## How to Cite
Please, cite:    
Suraj P. Kesavan, Takanori Fujiwara, Jianping Kelvin Li, Caitlin Ross, Misbah Mubarak, Christopher D. Carothers, Robert B. Ross, and Kwan-Liu Ma, "A Visual Analytics Framework for Reviewing Streaming Performance Data".
In Proceedings of of IEEE Pacific Visualization Symposium (PacificVis), forthcoming.

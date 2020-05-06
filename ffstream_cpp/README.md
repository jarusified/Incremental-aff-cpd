## Adaptive estimation using forgetting factor.

A python wrapper for ffstream library (R: https://github.com/cran/ffstream)

Some alternative method is available in python.

1. E-divisive: In R package "ecp": https://cran.r-project.org/web/packages/ecp/index.html. R package is available by using rpy2. But, currently rpy2 doesn't work with macOS Mojave.

2. Ruptures: https://github.com/deepcharles/ruptures

    
Requirements
-----
* C++11 compiler, Python3, Pybind11, 

* Note: Tested on macOS Mojave and Ubuntu 18.0.4 LTS.

Setup
-----
#### Mac OS with Homebrew
* Install libraries

    `brew install python3`

    `brew install pybind11`

#### Linux (tested on Ubuntu 18.0.4 LTS)
* Install libraries

    `sudo apt update`

    `sudo apt install libeigen3-dev`

    `sudo apt install python3-pip python3-dev`

    `pip3 install pybind11`

    `pip3 install numpy`

    
* This generates a shared library, "inc_pca_cpp.xxxx.so" (e.g., inc_pca_cpp.cpython-37m-darwin.so).

* If you want to run sample.py in this directory. You need to install additional libraries.

    `pip3 install matplotlib`

    `pip3 install sklearn`


Compile
-------
    
   #### Linux
    
    c++ -O3 -Wall -shared -std=c++11  -fPIC `python3 -m pybind11 --includes` aff.cpp aff_wrap.cpp -o aff_cpp `python3-config --extension-suffix` 

   #### Mac OS X

    c++ -O3 -Wall -shared -std=c++11  -fPIC -undefined dynamic_lookup `python3 -m pybind11 --includes` aff.cpp aff_wrap.cpp -o aff_cpp`python3-config --extension-suffix` 

* After compiling, a shared library, "aff_cpp.so" is generated. If not in correct format, rename the binary to "aff_cpp.so".

* The library can be loaded using

    `` import aff_cpp``
    
* If you want to run sample.py in this directory. You need to install additional libraries.

    `sudo apt install python3-tk`

    `pip3 install matplotlib`

    `pip3 install sklearn`

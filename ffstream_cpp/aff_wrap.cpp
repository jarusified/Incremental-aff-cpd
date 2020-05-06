#include <pybind11/pybind11.h>

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include "affcd.hpp"
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(aff_cpp, m) {
  m.doc() = R"pbdoc(
         Adaptive CPD estimation with a forgetting factor
        -----------------------
    )pbdoc";

  py::class_<AFFChangeDetector>(m, "AFF")
      .def(py::init<double const, double const, int const>())
      // .def("insert", &AFFChangeDetector::processVectorSave)
      // .def("checkIfChange", &AFFChangeDetector::checkIfChange)
      .def("update", &AFFChangeDetector::update)
      // .def("get_change_detected", &AFFChangeDetector::getChangeDetected)
      //.def("updateScaled", &AFFChangeDetector::updateScaled)
      .def("params", &AFFChangeDetector::print);

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}

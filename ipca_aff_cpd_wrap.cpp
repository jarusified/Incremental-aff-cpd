#include "ipca_aff_cpd.hpp"

#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(ipca_aff_cpd_cpp, m) {
  m.doc() = "Adaptive forgetting factor CPD with PCA";
  py::class_<IPCAAFFCPD>(m, "IPCAAFFCPD")
      .def(py::init<double const, double const, int const, double const>())
      .def("feed_predict", &IPCAAFFCPD::feedPredict)
      .def("feed", &IPCAAFFCPD::feed)
      .def("feed_with_pca_result_return", &IPCAAFFCPD::feedWithPCAResultReturn)
      .def("predict", &IPCAAFFCPD::predict);
}

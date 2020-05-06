#ifndef IPCAAFFCPD_HPP
#define IPCAAFFCPD_HPP

#include "affcd.hpp"
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Eigenvalues"
#include "inc_pca.hpp"

class IPCAAFFCPD : public AFFChangeDetector {
public:
  IPCAAFFCPD(double const alpha, double const eta = 0.01,
            int const burnInLength = 10, double incPCAForgettingFactor = 1.0);
  bool feedPredict(Eigen::RowVectorXd const &newTimePoint);
  void feed(Eigen::RowVectorXd const &newTimePoint);
  bool predict();

  // useIncPCA, adjustSign are for comparison of results for the paper
  double feedWithPCAResultReturn(Eigen::RowVectorXd const &newTimePoint,
                                 bool const &useIncPCA = true,
                                 bool const &adjustSign = true);

private:
  IncPCA incPCA;
  std::vector<Eigen::RowVectorXd> storedTimePointsForIncPCA;
  bool beforeFirstPartialFit = true;
  Eigen::MatrixXd prevComponents;
  Eigen::VectorXd signFlips;
  Eigen::MatrixXd pca(Eigen::RowVectorXd const &timePoint,
                      Eigen::Index const nComponents);
  Eigen::VectorXd signFlipInComponents(Eigen::MatrixXd const &prevComponents,
                                       Eigen::MatrixXd const &currComponents);
};

#endif // IPCAAFFCPD_HPP

#include "ipca_aff_cpd.hpp"

#include <iostream>

IPCAAFFCPD::IPCAAFFCPD(double const alpha, double const eta,
                     int const burnInLength, double incPCAForgettingFactor)
    : AFFChangeDetector(alpha, eta, burnInLength) {
  incPCA = IncPCA(1, incPCAForgettingFactor);
  signFlips = Eigen::VectorXd::Constant(1, 1.0);
}

bool IPCAAFFCPD::feedPredict(Eigen::RowVectorXd const &newTimePoint) {
  feed(newTimePoint);
  return predict();
}

double
IPCAAFFCPD::feedWithPCAResultReturn(Eigen::RowVectorXd const &newTimePoint,
                                   bool const &useIncPCA,
                                   bool const &adjustSign) {
  if (storedTimePointsForIncPCA.size() < 2) {
    storedTimePointsForIncPCA.push_back(newTimePoint);
  } else {
    beforeFirstPartialFit = false;
    Eigen::MatrixXd twoNewTimePoints(2, newTimePoint.size());
    for (Eigen::Index i = 0; i < 2; ++i) {
      twoNewTimePoints.row(i) = storedTimePointsForIncPCA[i];
    }
    incPCA.partialFit(twoNewTimePoints);
    // Eigen::MatrixXd incPCA.getComponents();
    storedTimePointsForIncPCA.clear();
  }

  Eigen::MatrixXd pcaResult;
  if (beforeFirstPartialFit) {
      // using pca is too slow when the vector is large
      // pcaResult = pca(newTimePoint, 1); // normal PCA

      // instead providing average should provide the same result
      pcaResult = Eigen::MatrixXd::Ones(newTimePoint.size(), 1);
      pcaResult /= double(newTimePoint.size());
  } else if (!useIncPCA) {
    pcaResult = pca(newTimePoint, 1); // normal PCA
  } else {
    pcaResult = incPCA.transform(newTimePoint);
    Eigen::MatrixXd currentComponents = incPCA.getComponents();

    if (adjustSign) {
      Eigen::VectorXd signFlipsBetweenPrevAndCurr =
          signFlipInComponents(prevComponents, currentComponents);
      // peform sign flip
      for (Eigen::Index i = 0, n = signFlipsBetweenPrevAndCurr.size(); i < n;
           ++i) {
        signFlips(i) *= signFlipsBetweenPrevAndCurr(i);
        pcaResult.row(i) = pcaResult.row(i) * signFlips(i);
      }
    }

    prevComponents = currentComponents;
  }

  double singleValAfterPCA = pcaResult(0, 0);

  update(singleValAfterPCA);

  return singleValAfterPCA;
}

void IPCAAFFCPD::feed(Eigen::RowVectorXd const &newTimePoint) {
  feedWithPCAResultReturn(newTimePoint);
}

bool IPCAAFFCPD::predict() { return getChangeDetected(); }

Eigen::MatrixXd IPCAAFFCPD::pca(Eigen::RowVectorXd const &timePoint,
                               Eigen::Index const nComponents) {
  Eigen::RowVectorXd meanX =
      Eigen::RowVectorXd::Constant(timePoint.size(), timePoint.mean());
  Eigen::RowVectorXd adjustX = timePoint - meanX;
  Eigen::MatrixXd XX = adjustX.transpose() * adjustX;
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(XX);

  Eigen::MatrixXd Y =
      (adjustX * es.eigenvectors().leftCols(nComponents)).real();

  prevComponents = es.eigenvectors().leftCols(nComponents).real();

  return Y;
}

Eigen::VectorXd
IPCAAFFCPD::signFlipInComponents(Eigen::MatrixXd const &prevComponents,
                                Eigen::MatrixXd const &currComponents) {
  Eigen::Index n = std::min(prevComponents.cols(), currComponents.cols());
  Eigen::VectorXd result(n);

  for (Eigen::Index i = 0; i < n; ++i) {
    Eigen::VectorXd prevComp = prevComponents.col(i);
    Eigen::VectorXd currComp = currComponents.col(i);
    // take dot product to calculate a sign of cosine similarity
    double dotProduct = prevComp.adjoint() * currComp;
    if (dotProduct >= 0.0) {
      result(i) = 1.0;
    } else {
      result(i) = -1.0;
    }
  }

  return result;
}

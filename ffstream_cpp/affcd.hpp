#include "detector.hpp"
#include "fff.hpp"
#include "aff.hpp"
#include "utils.hpp"
#include <vector>
#include <list>

//only needed for change detection version
// NOTE: Change from v0.1.5, now INIT_SCALEFACTOR is 1.
const double INIT_SCALEFACTOR = 1.0;
const double DEFAULT_SCALEFACTOR = 1.0;
const double ZERO_SCALEFACTOR = 0.0;
//Needs to be strictly larger than 1
const int BL_TOO_SMALL = 1;

//add BL
class AFFChangeDetector : public Detector{
public:
  AFFChangeDetector(double); // alpha (eta is default value)
  AFFChangeDetector(double, double, int); //alpha, eta, BL

  double getAlpha();
  double getLambda();
  double getLderiv();
  bool getChangeDetected();

  void print();
  void update(double);
  void processVector(std::vector<double>);
  std::tuple<std::vector<bool>, std::vector<int>, std::vector<double>> processVectorSave(std::vector<double>);

  //this function is only here for testing
  void checkIfChange();
        
  //getters and setters for use with Rcpp
  double getAFFxbar();
  void setAFFxbar(double);
private:
  AFF aff;
  double alpha;
  void stopBurnIn();
  double scaleFactor;  //this is 1/sigmahat, and scales eta
};

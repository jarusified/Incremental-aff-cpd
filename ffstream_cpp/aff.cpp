#include "aff.hpp"
#include "fff.hpp"
#include<iostream>

using namespace std;

//default constructor
AFF::AFF(): FFF(),
            eta(INIT_ETA),
            Omega(INIT_OMEGA),
            Delta(INIT_DELTA), 
            xbarDeriv(INIT_XBAR_DERIV),
            Lderiv(INIT_L_DERIV){}

//constructor when eta is specified
//aff2 <- new(AFF, 0.01)
AFF::AFF(double eta_) : FFF(),
                        eta(eta_),
                        Omega(INIT_OMEGA),
                        Delta(INIT_DELTA),
                        xbarDeriv(INIT_XBAR_DERIV),
                        Lderiv(INIT_L_DERIV){}

//print: show the fields
void AFF::print(){
  cout << "AFF contents: " << std::endl;
  cout << "lambda: " << lambda << std::endl;
  cout << "xbar: " << getXbar() << std::endl;
  cout << "eta: " << eta << std::endl;
}

//the simple update mechanism
void AFF::update(double obs){
    //Lderiv must be computed first, since it uses values from
    //xbar_old
    computeLderiv(obs);
    updateOmega();
    updateDelta();
    //FFF version of updating - is the same
    //FFF::update(obs);
    FFF::update(obs);
    //now update lambda
    computeXbarDeriv();
    updateLambda(1.0);
}


//the simple update mechanism
void AFF::updateScaled(double obs, double scaleFactor){
    //Lderiv must be computed first, since it uses values from
    //xbar_old
    computeLderiv(obs);
    updateOmega();
    updateDelta();
    //FFF version of updating - is the same
    //FFF::update(obs);
    FFF::update(obs);
    //now update lambda
    computeXbarDeriv();
    //no need to check value of scaleFactor here
    updateLambda(scaleFactor);
}

void AFF::updateOmega(){
    //here w is w_old
    Omega = lambda * Omega + w;
}

void AFF::updateDelta(){
    //here m is m_old
    Delta = lambda * Delta + m;
}

void AFF::computeXbarDeriv(){
    //here all indices are'new'
    xbarDeriv = (Delta - getXbar() * Omega) / w;
    //same as:
    //xbarDeriv = (Delta * w - m * Omega) / (w*w);
}

void AFF::computeLderiv(double obs){
    Lderiv = 2 * (getXbar() - obs) * xbarDeriv;
}

//These functions are only used in this class

//make sure lambda is in bounds
void AFF::checkInBoundsLambda(){
// better:?
//     lambda = (lambda < LAMBDA_MAX) ? LAMBDA_MIN : lambda;
//     lambda = (lambda > LAMBDA_MAX) ? LAMBDA_MAX : lambda;
    if (lambda < LAMBDA_MIN)
        lambda = LAMBDA_MIN;
    else if (lambda > LAMBDA_MAX)
        lambda = LAMBDA_MAX;
}

//scale factor is 1/sigmahat
void AFF::updateLambda(double scaleFactor){
    lambda = lambda - eta * scaleFactor * Lderiv;
    checkInBoundsLambda();
}

//getters just for testing
double AFF::getLambda(){
    return lambda;
}

double AFF::getXbar(){
    return xbar;
}

double AFF::getS2(){
    return s2;
}

double AFF::getOmega(){
    return Omega;
}

double AFF::getDelta(){
    return Delta;
}

double AFF::getXbarDeriv(){
    return xbarDeriv;
}

double AFF::getLderiv(){
    return Lderiv;
}

void AFF::processVector(std::vector<double> vec){
    for (int i=0; i < vec.size(); i++){
        update(vec[i]);
    }
}
 
std::vector<double> AFF::processVectorSave(std::vector<double> vec){
    std::vector<double> lambdasave(vec.size());
    for (int i=0; i < vec.size(); i++){
        update(vec[i]);
        lambdasave[i] = lambda;
    }
    return lambdasave;
}

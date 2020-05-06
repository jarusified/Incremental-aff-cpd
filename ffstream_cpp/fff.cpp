#include "fff.hpp"
#include <iostream>

using namespace std;

//default constructor 
FFF::FFF() : lambda(LAMBDA_NO_FORGETTING), 
                m(INIT_M),
                w(INIT_W),
                xbar(INIT_XBAR),
                s2(INIT_S2),
                u(INIT_U),
                v(INIT_V) { }

//consturctor with lambda specified
FFF::FFF(double lambda_) : lambda(lambda_), 
                            m(INIT_M),
                            w(INIT_W),
                            xbar(INIT_XBAR),
                            s2(INIT_S2),
                            u(INIT_U),
                            v(INIT_V) { } 


//the simple update mechanism
void FFF::update(double obs){
    updateM(obs);
    updateW();
    //order is important - need to update w first
    updateU();
    //v updated now in S2 update
    //updateVFromUAndW();
    //need to update s2 BEFORE xbar
    updateS2(obs);
    
    //need to update xbar AFTER s2
    //could use updateXbar, and then don't need m...
    //computeXbar();
    updateXbar(obs);
}

//update m
void FFF::updateM(double obs){
    m = lambda*m + obs;
}

//update w
void FFF::updateW(){
    w = lambda*w + 1;
}

//get xbar
void FFF::computeXbar(){
    if (w > 0){
        xbar = m/w;
    }
}

//stable update of xbar
void FFF::updateXbar(double obs){
    double winv = 1/w;
    xbar = (1 - winv)*xbar + winv*obs;
}

//stable update of xbar
void FFF::setXbar(double xbar_){
    xbar = xbar_;
}

//update u
void FFF::updateU(){
    //here w = w_new
	double a = (w-1)/w;
	double b = 1/w;
    //this is better than using cmath.pow
	u = a*a*u + b*b;
}

//w(1-u) = v
void FFF::updateVFromUAndW(){
    v = w*(1-u);
}

//make this more numerically stable?
//dividing by vnew earlier...
void FFF::updateS2(double obs){
    //NB: make sure using xbarOLD    
    double vold = v;
    updateVFromUAndW();
    //now updating s2
    //check w > 1, because it affects computation of s2
    if (w > 1){
        double frac = (w - 1)/(w*v);
        if (v > 0){
            //not using square
            s2 = (lambda*vold/v)*s2 + frac*(xbar-obs)*(xbar-obs);
        }
    }
}

//print: show the fields
void FFF::print(){
  cout << "FFF contents: " << std::endl;
  cout << "lambda: " << lambda << std::endl;
  cout << "xbar: " << xbar << std::endl;
}

//print: show the fields
void FFF::printHeader(int header){
    if (header!=0){
      cout << "Estimator: " << std::endl;
    } else {
      cout << "FFF contents: " << std::endl;
    }
    cout << "lambda: " << lambda << std::endl;
    cout << "xbar: " << xbar << std::endl;
}

//print: show the fields
void FFF::printAll(){
  cout << "FFF contents: " << std::endl;
  cout << "lambda: " << lambda << std::endl;
  cout << "xbar: " << xbar << std::endl;
  cout << "s2: " << s2 << std::endl;
  cout << "m: " << m << std::endl;
  cout << "w: " << w << std::endl;
  cout << "u: " << u << std::endl;
  cout << "v: " << v << std::endl;
}


//constructor with arguments
void FFF::reset(){
    xbar=INIT_XBAR;
    s2=INIT_S2;
    m=INIT_M;
    w=INIT_W;
    u=INIT_U;
    v=INIT_V;
}


//getter
double FFF::getLambda(){
    return xbar;
}

//getter
double FFF::getXbar(){
    return xbar;
}

//getter
double FFF::getS2(){
    return s2;
}

//getter
double FFF::getW(){
    return w;
}

//getter
double FFF::getU(){
    return u;
}

//getter
double FFF::getV(){
    return v;
}

void FFF::processVector(std::vector<double> vec){
    for (int i=0; i < vec.size(); i++){
        update(vec[i]);
    }
}

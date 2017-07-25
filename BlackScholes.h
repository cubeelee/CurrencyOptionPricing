#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#define PI 3.14159265359
#define E 2.7182818284

#include <math.h>

using namespace std; 

double normdist(const double &x)
{
    double prob;

    if (x == 0)
    {
        prob=0.5;
    }
    else
    {
        double m = 1.0/(sqrt(double(2) * PI));
        double t = 1 / (double(1) + 0.2316419 * fabs(x));
        t *= m * exp(-0.5 * pow(x,2))*(0.31938153   + t * (-0.356563782 + t* (1.781477937  + t * (-1.821255978 + t * 1.330274429))));
        if (x >= 0)
        {
            prob = 1.0 - t;
        }
        else
        {
            prob = t;
        }
    }
    return prob;
}

double BlackScholes(const double &vol, const double &strike, const double &spot, 
const double &r, const double &rf, const double &tau){
     
       return normdist((log(spot/strike)+((r-rf)-pow(vol,2.0)/2.0)*tau)/(vol*sqrt(tau)))/pow(E,r*tau);
       
};



#endif

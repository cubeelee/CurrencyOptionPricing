#ifndef MONTECARLO_H
#define MONTECARLO_H
#define E 2.7182818284

#include <math.h>
#include "BoxMuller.h" 

double MonteCarlo(const double &strike, const double &spot, const double &r, const double &rf, 
const double &vol, const double &tau, const int &N){
      
      double result = 0.0;
      
      for(int i=0;i<N; i++){
          if(spot*pow(E, (r-rf-pow(vol,2.0)/2.0)*tau+vol*sqrt(tau)*MT_genrand_std_normal())>strike)
          result += 1.0;      
      }
      
      return result/(pow(E,r*tau)*double(N));
      
       
       
}


#endif

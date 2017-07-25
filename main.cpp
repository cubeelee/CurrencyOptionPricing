#include <cstdlib>
#include <iostream>
#include <string> 

#include "data.h"
#include "ReadFile.h" 
#include "BlackScholes.h"
#include "BT.h"
#include "BoxMuller.h"
#include "MonteCarlo.h"

using namespace std;

int main(int argc, char *argv[])
{
    string EuroFile = "euro.csv";
    string LiborFile = "libor.csv";
    double r, rf; 
    double vol = GetVol(EuroFile); 
    GetInterestRate(LiborFile, r, rf);
     
    /********Calculating Option Price************/ 
    cout << "Black Scholes Option Price: "<<endl;
    cout << BlackScholes(vol, strike, spot, r, rf, tau)<<endl;
    BT option(vol, r,rf,strike, M, spot,tau,'C');
    cout << "Binomial Tree Option Price: " <<endl;
    cout << option.Value()<< endl;
    cout << "Monte Carlo Simulation Option Price: "<<endl;
    cout << MonteCarlo(strike, spot, r, rf, vol, tau, N)<< endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

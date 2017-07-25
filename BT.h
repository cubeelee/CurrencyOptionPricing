#ifndef BT_H
#define BT_H

#include <vector>

using namespace std;

class BT{
  public:
         BT();
         BT(double nsgm, double nr,double nrf, double nK, int nM, double nS0,double nT,char ntype);
         void setM(int &nM);
         double Value();
         void setTREE();
         double MValue(int &nM);
         vector< vector<double> > getTREE();


  private:
          double T;
          double S0;
          double sgm;
          double r;
          double rf;
          int M;
          std::vector< vector<double> > tree;   
          char type;
          double K;
          double u;
          double d;
          void setU();
          void setD();
          double p;
          void setP();   
          
};

#endif

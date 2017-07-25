#define E 2.7182818284

#include<math.h>
#include<iostream>
#include<vector>
#include "BT.h"

using namespace std;



BT::BT(){
    sgm=S0=T=0.0;
    M=0;
}
BT::BT(double nsgm, double nr,double nrf,double nK, int nM, double nS0,double nT,char ntype){
            if(ntype=='P'||ntype=='C')
            type = ntype;
            else{
                 type = 'C';
                 cout<<"The type should be 'P' or 'C'!"<<endl;
                 }
            if(nS0>=0){
            S0 = nS0;
            }
            else{
            S0 = 0;
            cout<<"S0 should be larger than 0!"<<endl;
            }
            if(nT>=0){
            T = nT;
            }
            else{
      
            cout<<"T should be larger than 0!"<<endl;
            }
            if(nK >=0){
            K = nK;
            }
            else{
            K = 0;
            cout<<"k should be larger than 0!"<<endl;
            }
            if(nsgm>=0){
            sgm = nsgm;            
            }
            else{
        
            cout<<"sgm should be larger than 0!"<<endl;
            }
            if(nr>=0){
            r = nr;          
            }
            else{
            r = 0;
            cout<<"rf should be larger than 0!"<<endl;
            }
            if(nrf>=0){
            rf = nrf;          
            }
            else{
            rf = 0;
            cout<<"rf should be larger than 0!"<<endl;
            }
            
            if(nM>=0){
            M = nM;          
            }
            else{
            M = 0;
            cout<<"M should be larger than 0!"<<endl;     
            }
            setU();
            setD();
            setP();
            setTREE();
}
  //   ~BT();
void BT::setM(int &nM){
     if(nM>0)
     M = nM;
     else{
     M = 0;
     cout<<"M should be larger than 0!"<<endl;
     }
     setU();
     setD();
     setP();
     setTREE();
}
double BT::Value(){
       return tree[0][0];
}
void BT::setTREE(){
   for (int i=0;i<=M;i++){
     vector<double> h(i+1);

     tree.push_back(h);         
   }
   for(int j=0; j<=M;j++){
   tree[M][j]=S0*pow(u,j)*pow(d,(M-j));

   if(type=='P'){
   if((K-tree[M][j])<0){
   tree[M][j]=0;
   }
   else{
   tree[M][j]=1.0;
   }
   }
   
   if(type=='C'){
   if((K-tree[M][j])>0)
   tree[M][j]=0;
   
   else{
   tree[M][j]=1.0;
   }
   }   
  
   }
   for(int k=M-1; k>=0; k--){
   for(int l=0;l<=k;l++){
   tree[k][l]=(1.0/pow(E,(r*(T/M))))*(p*tree[k+1][l+1]+(1-p)*tree[k+1][l]);
   
   }
       
   }

}

void BT::setU(){
     u=pow(E,(sgm*sqrt(T/M)));   
  
}
void BT::setD(){
          d=1/u;
}

void BT::setP(){
          p=(pow(E,(r-rf)*T/M) - d)/(u-d);   
       
}   
vector< vector<double> > BT::getTREE(){
                         return tree;        
}



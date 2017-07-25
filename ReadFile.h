#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

double GetVol(const string &filename){
       ifstream fin;
       
       int days = 0; 
       fin.open(filename.c_str());
       if(fin.fail()){
                   cout<<"Couldn't open input file "<<endl;
                   cout<<"Please make sure the input file:"<< filename <<endl;
                   cout<<"is in the same directory."<<endl;
                   
                   fin.close();
                   fin.clear();
                   
                   days = 0;
                   return 0.0;  
       }
       
        
       string line;
       fin >> line ;
       
       vector<double> FXrate_return;
       stringstream ss;
       string date;
       string data;
       double previous_data;
       double current_data;
       fin >> line; 
       days++;
       ss << string(line);
       getline(ss, date ,',');
       getline(ss, data, ',');
                 
       previous_data = log(atof(data.c_str())*100.0);
                 
       ss.clear();
       ss.str("");
       
       while(fin >> line){
                 days++;
                 ss << string(line);
                 getline(ss, date ,',');
                 getline(ss, data, ',');
                 
                 current_data = log(atof(data.c_str())*100.0);
                 FXrate_return.push_back(current_data - previous_data);
                 previous_data = current_data;
                 ss.clear();
                 ss.str("");
       };
       double miu;
       
       for(int i=0; i<days-1; i++){
       miu += FXrate_return[i];        
       }
       miu = miu/(days-1);
       
       double vol;
       for(int j=0; j< days-1; j++){
           vol += pow((FXrate_return[j]-miu), 2.0);    
       }
       vol = sqrt((252.0/(days-2))*vol);

       fin.close();
       fin.clear();
       return vol;     
}
double AverageInterest(multimap<string, double> &InterestRate,const string &maturity){

typedef multimap<string, double>::size_type sz_type;

multimap<string, double>::iterator iter=InterestRate.find(maturity);
sz_type entries=InterestRate.count(maturity);

double sum=0.0;
for(sz_type cnt=0; cnt < entries; ++cnt, ++iter)
sum += iter->second;


return sum/double(entries);
       
}
void GetInterestRate(const string &filename, double &r, double &rf){
     
     ifstream fin;
       
     fin.open(filename.c_str());
     string t = "2m"; 
     if(fin.fail()){
            cout<<"Couldn't open input file "<<endl;
            cout<<"Please make sure the input file:"<< filename <<endl;
            cout<<"is in the same directory."<<endl;
                   
            fin.close();
            fin.clear();
                   
            r = 0.0;
            rf = 0.0;  
       }
     map<string, int> Date;
     multimap<string, double> InterestRate;
     
     string date_cell;
     string line;
     fin >> line ;
     int index=0;
     stringstream ss;
     ss << string(line);
     
     while(getline(ss, date_cell, ',')){
     Date[date_cell] = index;
     index++;
     };
     ss.clear();
     ss.str("");
     string interest;     
     
     string maturity;
     string country;
     while(fin >> line){
     ss << string(line);
     getline(ss, maturity, ',');
     if(maturity==""||maturity=="USD"||maturity=="EUR"){
     if(maturity!="")
     country = maturity+"_";
     
     ss.clear();
     ss.str("");
     continue;
     }
     maturity = country + maturity;
     
     while(getline(ss, interest, ',')){      
          InterestRate.insert(make_pair(maturity,atof(interest.c_str())));
     }
     ss.clear();
     ss.str(""); 
     
     };
     
     string USDt = "USD_"+t;
     string EURt = "EUR_"+t;
     r = AverageInterest(InterestRate, USDt)/100;
     rf = AverageInterest(InterestRate, EURt)/100;
     

     fin.close();
     fin.clear();
}


#endif



#ifndef KROMOZOM_HPP 
#define KROMOZOM_HPP
#include "Gen.hpp"
using namespace std;
#include <string>

class Kromozom {
    int genSayisi;      
    Gen* ilkGen;        
    Gen* sonGen;      
    Kromozom* sonraki; 

public:
    Kromozom();
    friend class Dna;
    void genEkle(char deger);
    void genleriTerstenYaz() const;
    Gen*ortaGen();
    string genleriAl() const;
    ~Kromozom();
};

#endif 

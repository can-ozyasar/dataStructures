

#ifndef GEN_HPP 
#define GEN_HPP

class Gen {
private:
    char deger;      
    Gen* sonraki;    
    Gen* onceki;     

public:
    Gen(char deger);

    friend class Kromozom; 
    friend class Dna;
};

#endif 

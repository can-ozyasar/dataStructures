



#ifndef DNA_HPP
#define DNA_HPP
#include "Kromozom.hpp"
#include <string>

class Dna {
private:
    Kromozom* ilkKromozom;   
    Kromozom* sonKromozom;   
    int kromozomSayisi;      

public:
    Dna();
    friend class Kromozom; 
    void dosyadan_Oku(const std::string& dosyaAdi);
    void oto_Islemler(const std::string& dosyaAdi);
    void kromozom_Ekle(Kromozom* yeniKromozom);
    void caprazlama(int indeks1, int indeks2);
    void mutasyon(int kromozomIndeks, int genIndeks);
    void ekrana_Yaz() const;
    void dna_Tersten_Yaz() const;
    Kromozom* kromozom_Getir(int indeks) const;
    ~Dna();
};

#endif 


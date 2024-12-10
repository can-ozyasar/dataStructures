

#include "Kromozom.hpp"
#include <iostream>
#include "Gen.hpp"
using namespace std;

// Kromozom sınıfı (Gen bağlı listesi ortanca yapım)
//kromozom için kurucu fonksiyonum
Kromozom::Kromozom() : ilkGen(nullptr), sonraki(nullptr),sonGen(nullptr) ,genSayisi(0){}

//gen ekleme işlemini yapan fonksiyonum: songen değerini tutuyorum  ve güncelliyorum ki en sona eklemek daha hızlı olsun 
void Kromozom::genEkle(char deger) {

    Gen* yeniGen = new Gen(deger);
    if (!ilkGen) {
        ilkGen = yeniGen; 
    } 


    else {
        sonGen->sonraki = yeniGen;
        yeniGen->onceki = sonGen;
    }
    sonGen=yeniGen;
    genSayisi++;
}

// raporda istenilen ekrana yaz fonksiyonu: karşılaştırmalar sonucu bulunan geni ekrana yazıyor 
//A  özel durumu için performans katacak if koşulu direkt fonksiyonu bitiriyor işlemleri oldukça kısaltıyor
void Kromozom::genleriTerstenYaz() const {

    if (!ilkGen){
            cout << "Liste bos. İslem gerceklestirilemiyor.\n";
    return; // Liste boşsa işlem dursun 

    } 
    
    Gen* temp = ilkGen;
    char baslangic = temp->deger;
    temp=sonGen;
    
    //eğer en baştaki A ise direkt onu yazssın mantık olarak
    if(temp->deger=='A'){
        cout<<temp->deger<<" - ";
        return;
    } 
    else{

        while (temp != nullptr) {

        // sondan başa doğru ilerleyerek küçüğü arıyoruz
            if (baslangic > temp->deger ) {
                cout << temp->deger<<" - ";
                return;
            } 
        temp = temp->onceki;
        }
        cout << baslangic<<" - ";
    }

}

//orta geni bulmak için mantıklı bir algoritma sonucu orta geni kullanmak için döndürüyor
Gen *Kromozom::ortaGen()
{
    Gen* yavas = ilkGen;
    Gen* hizli = ilkGen;
    
    while (hizli != nullptr && hizli->sonraki != nullptr) {
        yavas = yavas->sonraki;          // Yavaş ilerleyen bir adım ilerler
        hizli = hizli->sonraki->sonraki; // Hızlı ilerleyen iki adım ilerler
        //sonuçta ortayı bulur
    }
    
    return yavas;
}


   //ekstra eklediğim  fonksiyon :tüm kromozomları ekrana yazan fonksiyon için genleri getiriyor
string Kromozom::genleriAl() const {
    Gen* temp = ilkGen;
    string genler ="";
    while (temp) {
        genler+=temp->deger;
        temp = temp->sonraki;
    }
    return genler;
}

// yıkıcı fonksiyon hafıza gediğini önlüyor
Kromozom::~Kromozom() {
    Gen* temp;
    while (ilkGen) {
        temp = ilkGen;
        ilkGen = ilkGen->sonraki;
        delete temp; 
    }
}
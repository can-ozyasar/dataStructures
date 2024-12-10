


#include "DNA.hpp"
#include "Kromozom.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// DNA sınıfı (Kromozom bağlı listesi)

// dna kurucu fonksiyonum ilk çalışır nesne oluşturulduğunda
Dna::Dna() : ilkKromozom(nullptr), sonKromozom(nullptr) ,kromozomSayisi(0){}

// otomatik işlemleri gerçekleştitren fonksiyonum okunan işlemlere göre uygun fonksiyonları çağırıyor (çaprazlama mutasyon)
void Dna::oto_Islemler(const string& dosyaAdi){

 ifstream islemDosyasi(dosyaAdi);
    if (!islemDosyasi.is_open()) {
        cout << "HATA!! Dosya acilamadi. " <<dosyaAdi<< endl;
        return;
    }

    string satir;
    while (getline(islemDosyasi, satir)) {
        if (satir.empty()) continue;

        // İşlem türünü almak için ilk karakteri alıyoruz
        char islem = satir[0];
        stringstream ss(satir.substr(2));  

        int indeks1, indeks2;

        // Boşlukla ayrılmış indeksleri almak için << operatörü kullandım
        ss >> indeks1 >> indeks2;

        if (islem == 'c' || islem == 'C') {
            caprazlama(indeks1, indeks2);  // Caprazlama işlemi yaptırıyor
        } else if (islem == 'm' || islem == 'M') {
            mutasyon(indeks1, indeks2);  // Mutasyon işlemi yaptırıyor
        } else {
            cout << "Gecersiz islem turu: " << islem << endl;
        }
    }

    cout << "Otomatik islemler tamamlandi.\n";
    islemDosyasi.close();


}

//dosyadan genleri okuyor ve aracı kullanmadan direkt listeye ekliyor char char olarak tek tek okuyor
void Dna::dosyadan_Oku(const string& dosyaAdi) {
    
    
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()){cout<<"HATA!! Dosya acilamadi" ;return;} 

    Kromozom* yeniKromozom = new Kromozom();
    char gen;

    while (dosya >> noskipws >> gen) { 
        if (gen == '\n') { 
            if (yeniKromozom->genSayisi>0) {
                kromozom_Ekle(yeniKromozom);
                yeniKromozom = new Kromozom(); 
            }
        } else if (gen != ' ') { 
            yeniKromozom->genEkle(gen); 
        }
    }

    if (yeniKromozom->genSayisi>0) {
        kromozom_Ekle(yeniKromozom);
    }

    dosya.close();
    
}

// kromozom ekleyen fonksiyon en sona eklemek için enson kromozomu tutuyorum bu sayede daha performasnlı olacak
void Dna::kromozom_Ekle(Kromozom* yeniKromozom) {
    if (!ilkKromozom) {
        ilkKromozom = sonKromozom = yeniKromozom;
    }
     else {
        sonKromozom->sonraki = yeniKromozom;
        sonKromozom = yeniKromozom;
    }
    kromozomSayisi++;
    
}

// çaprazlama işlemlerini gerçekleştiriyor arada bir yapı string vs. kullanmadan direkt listeden alıp çaprazlıyor
void Dna::caprazlama(int index1, int index2) {


    if (index1 < 0 || index2 < 0) {
        cout << "Hata: Negatif indeksler giremezsiniz.\n";
        return;
    }

    Kromozom* k1 = kromozom_Getir(index1);
    Kromozom* k2 = kromozom_Getir(index2);

    if (!k1 || !k2) {
        cout << "Hata: Gecersiz Kromozom indeks.\n";
        return;
    }

    int yarisi1 = k1->genSayisi / 2; 
    int yarisi2 = k2->genSayisi / 2;

    Kromozom* yeniKromozom1 = new Kromozom();
    Kromozom* yeniKromozom2 = new Kromozom();

    // Birinci kromozomun ilk yarısını yeniKromozom1'e 
    Gen* gecici = k1->ilkGen;
    for (int i = 0; i < yarisi1; ++i, gecici = gecici->sonraki) {
        yeniKromozom1->genEkle(gecici->deger);
    }

    if (k1->genSayisi % 2 != 0) { 
        gecici = gecici->sonraki;
    }

    // İkinci kromozomun ikinci yarısını yeniKromozom1'e 
    Gen* gecici2 = k2->ortaGen(); 
    
     if (k2->genSayisi % 2 != 0) { 
        gecici2 = gecici2->sonraki;
    }
    while (gecici2 != nullptr) {  
        yeniKromozom1->genEkle(gecici2->deger);
        gecici2 = gecici2->sonraki;
    }


    // Birinci kromozomun ikinci yarısını yeniKromozom2'e 
    while (gecici != nullptr) {  
        yeniKromozom2->genEkle(gecici->deger);
        gecici = gecici->sonraki;
    }

    // ikinci kromozomun birinci yarısını yeniKromozom2'e 
    gecici2=k2->ilkGen; 
    for (int i = 0; i < yarisi2; ++i, gecici2 = gecici2->sonraki) {
        yeniKromozom2->genEkle(gecici2->deger);
    } 
 
    kromozom_Ekle(yeniKromozom1);
    kromozom_Ekle(yeniKromozom2);
    

    cout << "Caprazlama islemi tamamlandi.\n";
    

}

// mutason işlemi yapıyor istenen kromozomdaki istenen geni X olarak güncelliyor, direkt liste üzerinde işlem yapıyorum
void Dna::mutasyon(int kromozomIndeks, int genIndeks) {

    Kromozom* kromozom = kromozom_Getir(kromozomIndeks);

    if (!kromozom) {
        cout << "Hata: Gecersiz kromozom indeksi.\n";
        return;
    }

    if (genIndeks < 0 || genIndeks >= kromozom->genSayisi) {
        cout << "Hata: Gecersiz gen indeksi.\n";
        return;
    }

    Gen* temp = kromozom->ilkGen; // indexteki gene gidiyor
    for (int i = 0; i < genIndeks && temp; ++i) {
        temp = temp->sonraki;
    }

    if (temp) temp->deger = 'X'; // Mutasyon için 'X' 
    cout << "Mutasyon islemi tamamlandi.\n";

}

// ekstra eklediğim bir fonksiyon tüm genleri görmek için kullanılabilir 
//işlemlerin sonuçlarını daha somut görmek için kullanılabiliriz
void Dna::ekrana_Yaz() const {
    if (!ilkKromozom) {
        cout << "Liste bos, herhangi bir kromozom bulunmuyor.\n";
        return;
    }

    Kromozom* temp = ilkKromozom;
    int indeks = 0;
    
    cout << "\n Mevcut Kromozomlar:\n";
    while (temp) {
        cout << "Kromozom " << indeks << ":  "<<temp->genleriAl() << endl;
        temp = temp->sonraki;
        ++indeks;
    }
    cout << endl;
}

// indexteki kromozomu döndürüyor getiriyor
Kromozom* Dna::kromozom_Getir(int indeks) const {
    if (indeks < 0) return nullptr;
    Kromozom* temp = ilkKromozom;
    for (int i = 0; i < indeks && temp; ++i) {
        temp = temp->sonraki;
    }
    return temp;
}

 //raporda yazılan ekrana yaz fonksiyonu özel bir işlem ile en küçük ilk geni buluyor ve yazıyor  aralarına "-" koyuyor
void Dna::dna_Tersten_Yaz() const {
    if (!ilkKromozom) {
        cout << "Liste bos, herhangi bir DNA veya kromozom bulunmuyor.\n";
        return;
    }
    Kromozom* temp =ilkKromozom;
    cout << "\n ILK GENDEN SONRAKI EN KUCUK GENLER \n";
    while (temp) {
        temp->genleriTerstenYaz();
        temp = temp->sonraki;
        
    }
    cout << endl;
}

//hafıza gediği oluşmaması için yıkıcı fonksiyon en son çalışır ve tüm listeydeki düğümleri siler
Dna::~Dna() {
    Kromozom* temp;
    while (ilkKromozom) {
        temp = ilkKromozom;
        ilkKromozom = ilkKromozom->sonraki;
        delete temp;
    }
}

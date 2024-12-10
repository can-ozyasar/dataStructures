

#include <iostream>
#include <fstream>
#include "DNA.hpp"
#include <sstream>


using namespace std;


int main() {
    int secim;
    Dna dna;
    // ilk başta dosyadaki tüm genleri okuyor ve eş zamanlı olarka kromozomlara ekliyor
    dna.dosyadan_Oku("Dna.txt");

    
    do {
        
        system("cls");
        // seçimler menüsü
        cout << "\n=== DNA Islemleri ===\n";
        cout << "1. Caprazlama\n";
        cout << "2. Mutasyon\n";
        cout << "3. Ekrana yaz (Kromozomlarin ilk En kucuk Genlerini Ekrana Yaz)\n";
        cout << "4. Otomatik islemler\n";
        cout << "5. Guncel Kromozomlari Yaz(Tum Kromozomlar)\n";
        cout << "6. Cikis\n";
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
        case 1: { //çaprazlama işlemi için case1
            
            int indeks1, indeks2;
            cout << "Caprazlama yapilacak iki kromozomun satir numarasini girin: "<<endl;
            cout<<"#k1 : ";
            cin >> indeks1;
            cout<<"#k2 : ";
            cin>> indeks2;
            dna.caprazlama(indeks1, indeks2);
            system("pause");
            break;
        }
        case 2: {//mutasyon işlemi için case2

            system("cls");
            int kromozomIndeks, genIndeks;
            cout << "Mutasyona ugratilacak kromozomun satir ve genin index numarasini girin: ";
            cout<<"#Satir : ";
            cin >> kromozomIndeks;
            cout<<"#Index : ";
            cin>> genIndeks;
            
            dna.mutasyon(kromozomIndeks, genIndeks);
            system("pause");
            break;
         
        }
        case 3:// raporda  istenilen ekrana yaz işlemi için case3
            system("cls");
            dna.dna_Tersten_Yaz();
            system("pause");
            break;
        case 4: {//otomatik işlemler işlemi için case4
            system("cls");
            dna.oto_Islemler("oto_islemler.txt");
            system("pause");
            break;
        }
        case 5:{//ekstra eklediğim tüm kromozomları ekrana yazan fonksiyon için case5

            system("cls");
            dna.ekrana_Yaz();
            system("pause");
            break; 
        }
        
        case 6:{//çıkış işlemi için case6

            system("cls");
            cout << "Programdan cikiliyor...\n";
            break;
        }
        default://başka bir değer girilirse  hata mesajı veriyor
            cout << "Hatali secim! Lutfen tekrar deneyin.\n";
            break;
        }
    } while (secim != 6); // seçim devam etme koşulu

    return 0;
}

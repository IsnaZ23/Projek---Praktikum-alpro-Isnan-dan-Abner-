#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct item{
    string nama;
    int jumlah;
    int durability;
};

struct player{
    char username[30];
    item backpack[36];
    
};

player userAktif;
int main() {
    int pilih;
    string namaplayer;
    FILE *pf;

    cout<<"===== MINECRAFT INVENTORY SYSTEM===== \n"
        <<"1. Bikin Akun baru (buat tas baru) \n"
        <<"2. Login Akun Lama (Isi inventory lama ) \n"
        <<"Pilih (NO 1-2) : ";
    cin>>pilih;
    cin.ignore();
    
    cout<<"Masukkan Nama Player: ";
    getline(cin, namaplayer);
    string namaFile = namaplayer + ".dat";

    switch (pilih){
    case 1:
        
    break;
    
    default:
        break;
    }

    return 0;
}
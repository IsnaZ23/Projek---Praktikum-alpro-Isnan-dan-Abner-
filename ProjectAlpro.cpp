#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct item{
    char nama[50];
    int jumlah;
    int durability;
};

struct player{
    char username[30];
    item backpack[36];
    
};

void aturAkun(){

} 
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
        pf = fopen(namaFile.c_str(), "wb");
        if (pf != NULL){
            strcpy(userAktif.username, namaplayer.c_str());
            for (int i = 0; i < 36; i++){
                strcpy(userAktif.backpack[i].nama, "-");
                userAktif.backpack[i].jumlah = 0;
                userAktif.backpack[i].durability;
            }

            fwrite(&userAktif, sizeof(userAktif), 1, pf);
            fclose(pf);
            cout<<"Akun berhasil dibuat dengan nama file "<<namaFile<<endl;
            
        }
    break;
    
    case 2 :

    break;
    default:
        break;
    }

    return 0;
}
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
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
//===================
player userAktif;  //|
//===================
string namaFile;  //|
string namaplayer;//|
FILE *pf;         //|
//===================

void lihatInventory() {
    bool isinya = false;

    cout <<"Isi Tas "<<userAktif.username<<" : \n";
    cout << "---------------------------------------------------------------" << endl;
    cout << " No | "<< left << setw(18)<<"Nama Item "<<"| Jumlah | Durabilty  " << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 36; i++){
        if (strcmp(userAktif.backpack[i].nama, "-") != 0){
            cout << " " <<left << setw(2)<<i<<" | "
                <<left<< setw(18) <<userAktif.backpack[i].nama<<" | "
                <<left<< setw(3)  <<userAktif.backpack[i].jumlah<<" | "
                <<userAktif.backpack[i].durability<<endl;
            isinya = true;
        }
    }

    if (!isinya){
        cout<<" Tas anda masih kosong ! "<<endl;
    }
    cout << "\n---------------------------------------------------------------" << endl;
};

void tambahItem() {
    int slot;
    cout << "\n=== TAMBAH ITEM KE 36 slot INVENTORY === " << endl;
    cout << "pilih nomor slot ke berapa :  ";
    cin >> slot;

    if (slot < 1 || slot > 36){
        cout<<"jumlah slot Tidak valid (jumlah maksimal 36 slot) ! \n";
    }else{
        cout << "Mengisi Slot Nomor " << slot << endl;
        int i = slot - 1;

        cout << "Masukkan Nama Item ('_' sebagai spasi) : ";
        cin >> userAktif.backpack[i].nama;
        cout << "Masukkan jumlah : ";
        cin >> userAktif.backpack[i].jumlah;
        cout << "Masukkan berapa jumlah durability : ";
        cin >> userAktif.backpack[i].durability;
        }
        cout<<"\n Berhasil mengisi slot nomor "<<slot<<endl;
};

void cariItem() {
    string namaItem;    
    cout << "\n=== CARI ITEM DI INVENTORY === " << endl;
    cout << "Masukkan nama item yang ingin dicari : ";
    cin >> namaItem;

    // simpan item terakhir yang di cari
    item tempTerakhir = userAktif.backpack[35];
    
    // Sentinel search
    strcpy(userAktif.backpack[35].nama, "\0"); // Set sentinel
    int i = 0;
    while (strcmp(userAktif.backpack[i].nama, namaItem.c_str()) != 0){
        i++;
    }

    userAktif.backpack[35] = tempTerakhir; // Kembalikan item terakhir ke slot 36

    if (i < 35){
        cout << "Item '" << namaItem << "' ditemukan di slot nomor " << i + 1 << endl;
        cout << "Jumlah: " << userAktif.backpack[i].jumlah << ", Durability: " << userAktif.backpack[i].durability << endl;
    } else {
        cout << "Item '" << namaItem << "' tidak ditemukan!" << endl;
    }

}

//  Sorting 
void bubbleSort() {
    cout << "\n=== MERAPIKAN INVENTORY DENGAN BUBBLE SORT === " << endl;
    for (int i = 0; i < 35; i++){
        for (int j = 0; j < 35 - i - 1; j++){
            if (strcmp(userAktif.backpack[j].nama, userAktif.backpack[j + 1].nama) > 0){
                item temp = userAktif.backpack[j];
                userAktif.backpack[j] = userAktif.backpack[j + 1];
                userAktif.backpack[j + 1] = temp;
            }
        }
    }
    cout << "Inventory berhasil dirapikan dengan Bubble Sort!" << endl;
}

void shellSort() {
    cout << "\n=== MERAPIKAN INVENTORY DENGAN SHELL SORT === " << endl;
    int n = 36;
    for (int gap = n / 2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i++){
            item temp = userAktif.backpack[i];
            int j;
            for (j = i; j >= gap && strcmp(userAktif.backpack[j - gap].nama, temp.nama) > 0; j -= gap){
                userAktif.backpack[j] = userAktif.backpack[j - gap];
            }
            userAktif.backpack[j] = temp;
        }
    }
    cout << "Inventory berhasil dirapikan dengan Shell Sort!" << endl;
}

void save(){
    cout<<"Terimakasih! \n";
    pf = fopen(namaFile.c_str(),"wb");
    if (pf != NULL){
        fwrite(&userAktif, sizeof(userAktif), 1, pf);
        fclose(pf);
        cout<<"data berhasil di simpan ke file! "<<endl;
    }
}

int main() {
    bool login = false;
    int pilih;

    cout<<"===== MINECRAFT INVENTORY SYSTEM===== \n"
        <<"1. Bikin Akun baru (buat tas baru) \n"
        <<"2. Login Akun Lama (Isi inventory lama ) \n"
        <<"Pilih (NO 1-2) : ";
    cin>>pilih;
    cin.ignore();
    
    cout<<"Masukkan Nama Player: ";
    getline(cin, namaplayer);
    namaFile = namaplayer + ".dat";


    switch (pilih){
    case 1:
        pf = fopen(namaFile.c_str(), "wb");
        if (pf != NULL){
            strcpy(userAktif.username, namaplayer.c_str());
            for (int i = 0; i < 36; i++){
                strcpy(userAktif.backpack[i].nama, "-");
                userAktif.backpack[i].jumlah = 0;
                userAktif.backpack[i].durability = 0;
            }

            fwrite(&userAktif, sizeof(userAktif), 1, pf);
            fclose(pf);
            cout<<"Akun berhasil dibuat dengan nama "<<namaFile<<endl;
            login = true;
        }
    break;
    
    case 2 :
        pf = fopen(namaFile.c_str(), "rb");
        if(pf != NULL){
            fread(&userAktif, sizeof(userAktif), 1, pf);
            fclose(pf);
            cout<<"Berhasil login selamat datang "<<userAktif.username<<" !"<<endl;
            login = true;
        }else{
            cout<<"Akun tidak ditemukan ! silahkan bikin akun terlebih dahulu. "<<endl;
            login = false;
        }
    break;

    default:
    cout << "Pilihan tidak valid!" << endl;
    break;
    }

    if (login){
        int menu;
        do{
            cout<<"\n=== Menu Inventory "<<userAktif.username<<" ! === \n"
                <<"1. Lihat Inventory \n"
                <<"2. Tambah Item \n"
                <<"3. Cari item (Searching) \n"
                <<"4. Merapikan Tas (Sorting) \n"
                <<"5. Keluar dan simpan akun \n"
                <<"Pilih 1-5 :";
            cin >>menu;
        
            switch (menu){

            case 1: 
                lihatInventory();
            break;
            case 2: 
                tambahItem();
                save();
            break;

            case 3: 
                cariItem();
            break;

            case 4:
                int sortChoice;
                cout << "\n Pilih metode sorting: \n1. Bubble Sort\n2. Shell Sort\nPilih (1-2): ";
                cin >> sortChoice;

                if (sortChoice == 1){
                    bubbleSort();
                } else if (sortChoice == 2){
                    shellSort();
                } else {
                    cout << "Pilihan tidak ada!" << endl;
                    break;
                }
            save();
            lihatInventory();
            break;

            case 5:
                save();
            break;
        
            default:
        
            break;
            }
        } while (menu != 5);
        
    }
    

    return 0;
}
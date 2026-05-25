#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <windows.h>
using namespace std;
//=========================|
struct item{
    char nama[50];
    int jumlah;
    int durability;
};

struct player{
    char username[30];
    item backpack[36];
    
};
//=========================|

void loading(){
    cout<<"Loading ";
    for (int i = 0; i < 6; i++){
        cout<<". "<<flush;
        Sleep(500);
    }
    cout<<endl;
}

void buatAkunBaru(player *plr, bool *status, string nf, string np){
    int i;
    ofstream fileTulis(nf, ios::out | ios::binary);
    if (fileTulis.is_open()){
        strncpy(plr->username,np.c_str(), 29);
        plr->username[29] = '\0';

        for (i = 0; i < 36; i++){
            strcpy(plr->backpack[i].nama,"-");
            plr->backpack[i].jumlah = 0;
            plr->backpack[i].durability = 0;
        }
        
        fileTulis.write((char*)plr, sizeof(player));
        fileTulis.close();
    cout<<"Akun berhasil dibuat ! \n";
    *status = true;
    }
    else{
        cout<<"Akun gagal dibuat !";
    *status = false;
    }
}

void loginAkun(player *plr, bool *status, string nf){
    ifstream fileBaca(nf, ios::in | ios::binary);
    if (fileBaca.is_open()){
        fileBaca.read((char*)plr, sizeof(player));
        fileBaca.close();
        cout << "Berhasil login! \n"
             << "Selamat datang kembali, "<<plr->username<<" !\n";
        *status = true;
    }
    else{
    cout << "Akun tidak ditemukan! Silahkan bikin akun terlebih dahulu." << endl;
        *status = false;
    }
    
}

void lihatInventory(player *plr){
    bool isiTas = false;
    cout<<"Isi tas : "<<plr->username<<" : \n";
    cout << "---------------------------------------------------------------" << endl;
    cout << " No | " << left << setw(18) << "Nama Item " << "| Jumlah | Durabilty  " << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 36; i++){
        if (strcmp(plr->backpack[i].nama, "-") !=0){
            cout<<" "<<left<<setw(2)<<i+1<<" | "
                <<left<<setw(18)<<plr->backpack[i].nama<<" | "
                <<left<<setw(3)<<plr->backpack[i].jumlah<<" | "
                <<left<<plr->backpack[i].durability<<endl;
                isiTas = true;
        }
        
    }
    if (!isiTas){
        cout<<"Tas anda belum ada isinya ! \n";
    }
    
    cout << "---------------------------------------------------------------" << endl;
}

void tambahInventory(player *plr){
    int slot;
    cout<<"\n===Tambah Item Di 36 Slot Inventory===\n"
        <<"Pilih nomor slot di backpack ke berapa : ";
    cin>>slot;
    if (slot < 1 || slot > 36){
        cout<<"jumlah slot tidak ada (1-36) \n";
    }else{
        int i = slot - 1;
        if (strcmp(plr->backpack[i].nama, "-")!=0){
            cout<<"Slot ini sudah terisi oleh "<<plr->backpack[i].nama<<"."<<endl;
            return;
        }
        
        cout<<"Mengisi slot pada nomor "<<slot<<endl;
        cout<<"Masukkan nama item ('_' -> spasi) : ";
        cin>>plr->backpack[i].nama;
        cout<<"Masukkan jumlah item : ";
        cin>>plr->backpack[i].jumlah;
        cout<<"Masukkan berapa jumlah durabilty item : ";
        cin>>plr->backpack[i].durability;
        loading();
        cout<<"\nBerhasil Menambah item di slot-"<<slot<<endl;
    }
    
}

void hapusItem(player *plr){
    int slot;
    cout<<"\n=== Buang Item Di INVENTORY ===\n";
    cout<<"Pilih No Slot (1-36) : ";
    cin>>slot;

    if (slot < 1 || slot > 36){
        cout<<"Nomor Slot tidak ada ! \n";
    }else{
        int i = slot - 1;

        if (strcmp(plr->backpack[i].nama, "-") == 0){
            cout<<"Slot Ini Memang kosong ! \n";
        }else{
            cout<<"Membuang item "<<plr->backpack[i].nama<<" di slot ke-"<<slot<<endl;

            strcpy(plr->backpack[i].nama, "-");
            plr->backpack[i].jumlah = 0;
            plr->backpack[i].durability = 0;
            loading();
            cout<<"Item berhasil dibuang !\n";
        }
        
    }
    
}

void cariItem(player *plr){
    string namaCari;
    cout<<"\n=== Cari Item Di inventory === \n"
        <<"Masukkan nama item yang ingin dicari : ";
        cin>>namaCari;

        item temp = plr->backpack[35];
        strcpy(plr->backpack[35].nama, namaCari.c_str());

        int i = 0;
        while (strcmp(plr->backpack[i].nama, namaCari.c_str()) != 0){
            i++;
        }
        plr->backpack[35] = temp;

        if (i<35 || strcmp(temp.nama, namaCari.c_str()) != 0){
            cout<<"Item "<<namaCari<<" ditemukan pada slot ke-"<<i+1<<endl;
            cout<<"Jumlah : "<<plr->backpack[i].jumlah<<"\n"
                <<"Durability : "<<plr->backpack[i].durability<<"\n";
        }else{
            cout<<"Item "<<namaCari<<" Tidak ditemukan didalam inventory !\n";
        }
}

bool tukarDulu(item itemA,item itemB){
    if (strcmp(itemA.nama, "-") == 0){ return true; }
    if (strcmp(itemB.nama, "-") == 0){ return false; }

    return itemA.jumlah < itemB.jumlah;
}

void BubbleSort(player *plr){
    loading();
    for (int i = 0; i < 35; i++){
        for (int j = 0; j < 35-i ; j++){
            if (tukarDulu(plr->backpack[j], plr->backpack[j+1]))
            {
                item temp = plr->backpack[j];
                plr->backpack[j] = plr->backpack[j + 1];
                plr->backpack[j + 1] = temp;
            }
        }
    }
    cout<<"Tas Berhasil dirapikan berdasarkan jumlah item !";
    
}

void ShellSort(player *plr){
    loading();
    int n = 36;
    for (int gap = n/2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i++){
            item temp = plr->backpack[i];
            int j;
            for ( j = i; j >= gap && tukarDulu(plr->backpack[j - gap],temp); j -= gap){
               plr->backpack[j] = plr->backpack[j - gap];
            }
            plr->backpack[j] = temp;
        }
    }
    cout<<"Tas Berhasil dirapikan berdasarkan jumlah item !";
}

void save(player *plr, string nf){
    ofstream fileDitulis(nf, ios::out | ios::binary);
    if (fileDitulis.is_open()){
        fileDitulis.write((char*)plr, sizeof(player));
        fileDitulis.close();
    }
}
//======================================================================|
int main() {
    player userAktif;
    bool login = false;
    int pilih;
    string namaPlayer, namaFile;
    cout << "===== MINECRAFT INVENTORY SYSTEM ===== \n"
         << "1. Bikin Akun baru \n"
         << "2. Login Akun Lama \n"
         << "Pilih (1-2) : ";
    cin>>pilih; cin.ignore();

    cout<<"Masukkan Nama Player: ";
    getline(cin, namaPlayer);
    namaFile = namaPlayer + ".dat";

    switch (pilih){
        case 1:
        buatAkunBaru(&userAktif,&login,namaFile,namaPlayer);
        break;

        case 2:
        loginAkun(&userAktif,&login,namaFile);
        break;
        
        default:
        cout << "Pilihan tidak valid!" << endl;
        return 0;
        break;
    }

    if (login){
        int menu;
        char mau;
do{
        cout << "\n=== Menu Inventory " << userAktif.username << " === \n"
             << "1. Lihat Inventory \n"
             << "2. Tambah Item \n"
             << "3. Cari item \n"
             << "4. Merapikan Tas \n"
             << "5. Buang item \n"
             << "Pilih: ";
            cin >> menu;
        switch (menu){
            case 1:
                lihatInventory(&userAktif);
            break;
            
            case 2:
                tambahInventory(&userAktif);
                save(&userAktif, namaFile);
            break;

            case 3:
                cariItem(&userAktif);
            break;

            case 4:{
            int pilihSort;
                cout<<"Urutkan item berdasarkan jumlah : \n"
                    <<"1. Bubble sort \n"
                    <<"2. Shell sort \n";
                cout<<"pilih No 1-2 : ";
                cin>>pilihSort;
                cin.ignore();

                if (pilihSort == 1){
                    BubbleSort(&userAktif);
                }else if(pilihSort == 2){
                    ShellSort(&userAktif);
                }else{
                    cout<<"Maaf tidak ada pilihan selain 1 dan 2 ! \n"; 
                }
                save(&userAktif, namaFile);
                cout<<"\nSetelah item diurutkan : \n";
                lihatInventory(&userAktif);
            }
            break;

            case 5:
                hapusItem(&userAktif);
                save(&userAktif, namaFile);
            break;

            default:
            cout << "Pilihan menu salah, tidak ada dilist menu !\n";
            break;
        }
        cout<<"Mau ulang ke menu utama ? (y/n) : ";
        cin>>mau;
        loading();
        if (mau == 'n' || mau == 'N'){
            save(&userAktif, namaFile);
            cout<<"Akun disimpan , Terimakasih "<<userAktif.username<<" !\n";
        }
        
} while (mau == 'y' || mau == 'Y');
}
    

}
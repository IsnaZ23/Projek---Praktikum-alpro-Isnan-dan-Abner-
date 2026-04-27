#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;
//=================================================
void loading() {
    cout << "Masuk ke akun ";
    for (int i = 0; i < 10; i++) {
        cout << ". " << flush;
        usleep(500000);
    }
    cout << "\n";
}
//=================================================
// Untuk Playernya
int jumlahLog = 0;
bool login = false;

    typedef struct {
        string nama; //
        string nim; // komponen akun
        string pw; //
        float uang = 50000;
        int lapar = 0;
    }player;

    player database[10];

//=================================================
string nimR, pwR;
int kesempatan ;
//=================================================

int main() {
int pilih;
while (!login){
        cout<<"===== RPG Mahasigmas ===== \n";
    cout<<"1. Registrasi\n"
        <<"2. Login\n";
    cout<<"Pilih Nomor (1- 2) : ";
    cin >> pilih;
switch (pilih){
//()()()()()
case 1:{
if (jumlahLog < 10){
    cout<<"==== Registrasi Menu ==== \n";
    cout<<"Masukkan Nama akun UPN : ";
    cin.ignore();
    getline(cin, database[jumlahLog].nama);
    cout<<"Masukkan NIM UPN : ";
    getline(cin, database[jumlahLog].nim);
do{
    cout<<"Masukkan PW (Minimal 6 huruf) : ";
    cin>>database[jumlahLog].pw;

    if (database[jumlahLog].pw.length() <= 5){
        cout<<"pasword Terlalu Pendek minimal 6 huruf dan angka  ! \n";
    }
    
} while (database[jumlahLog].pw.length() <= 5);

    cout<<" Berhasil Registrasi  ! \n";
    jumlahLog ++;
}else{
    cout<<"Maaf jumlah player sudah penuh ! \n";
    break;
}

break;
}
//()()()()()()
case 2 :{
kesempatan = 0;
do{
    cout << "===== Login Menu ===== \n";
    cout << "Masukkan NIM : ";
    cin  >> nimR;
    cout << "Masukkan PW : ";
    cin  >> pwR;
for(int i = 0; i < jumlahLog ;i++){
    if (nimR == database[i].nim && pwR == database[i].pw){
            login = true;
            break;
    }
}
    if (login){
        break;
    }else{
        kesempatan++;
        cout<<"Kesempatan tinggal "<< 3 - kesempatan<<endl;
    }

} while (kesempatan < 3);

if (login){
    loading();
    cout<<"Berhasil Login ! \n";
    
}else{
    cout<<"Login Gagal terimakasih !";
    return 0;
}
break;
}
//()()()()()()

    default:

    break;

}
}


}
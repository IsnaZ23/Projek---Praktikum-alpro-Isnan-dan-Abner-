#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <windows.h>
using namespace std;

//=========================|
struct item
{
    char nama[50];
    int jumlah;
    int durability;
};

struct player
{
    char username[30];
    item backpack[36];
};
//=========================|

void loading()
{
    cout << "Loading ";
    for (int i = 0; i < 6; i++)
    {
        cout << ". " << flush;
        Sleep(50);
    }
    cout << endl;
}

// Memeriksa apakah file pernah dibuat atau tidak
bool cekFileAda(string nf)
{
    ifstream fileCek(nf, ios::binary);
    return fileCek.is_open();
}

// Buat akun baru (File Baru)
void buatAkunBaru(player *plr, bool *status, string nf, string np)
{
   
    if (cekFileAda(nf))
    {
        cout << "[PERINGATAN] Player dengan nama \"" << np << "\" sudah terdaftar!\n";
        cout << "Silahkan gunakan menu login atau buat nama player lain.\n";
        *status = false;
        return;
    }
    
    ofstream fileTulis(nf, ios::out | ios::binary | ios::trunc);
    if (fileTulis.is_open())
    {
        strcpy(plr->username, np.c_str());
        for (int i = 0; i < 36; i++)
        {
            strcpy(plr->backpack[i].nama, "-");
            plr->backpack[i].jumlah = 0;
            plr->backpack[i].durability = 0;
        }
        fileTulis.write((char *)plr, sizeof(player));
        fileTulis.close();
        cout << "Akun berhasil dibuat ! \n";
        *status = true;
    }
    else
    {
        cout << "Akun gagal dibuat !\n";
        *status = false;
    }
}

// Login berdasarkan nama akun
void loginAkun(player *plr, bool *status, string nf)
{
    ifstream fileBaca(nf, ios::in | ios::binary);
    if (fileBaca.is_open())
    {
        fileBaca.read((char *)plr, sizeof(player));
        fileBaca.close();
        cout << "Berhasil login! \n";
        cout << "Selamat datang kembali, " << plr->username << " !\n";
        *status = true;
    }
    else
    {
        cout << "Akun tidak ditemukan! Silahkan bikin akun terlebih dahulu." << endl;
        *status = false;
    }
}

// Membuka Inventory 
void lihatInventory(player *plr)
{
    bool isiTas = false;
    cout << "\nIsi tas : " << plr->username << " : \n";
    cout << "---------------------------------------------------------------" << endl;
    cout << " No | " << left << setw(18) << "Nama Item " << "| Jumlah | Durability  " << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < 36; i++)
    {
        if (strcmp(plr->backpack[i].nama, "-") != 0)
        {
            cout << " " << left << setw(2) << i + 1 << " | "
                 << left << setw(18) << plr->backpack[i].nama << " | "
                 << left << setw(3) << plr->backpack[i].jumlah << " | "
                 << left << plr->backpack[i].durability << endl;
            isiTas = true;
        }
    }
    if (!isiTas)
    {
        cout << "Tas anda belum ada isinya ! \n";
    }
    cout << "---------------------------------------------------------------" << endl;
}

// Menambah item ke dalam inventory
void tambahInventory(player *plr)
{
    int slot;
    cout << "\n===Tambah Item Di 36 Slot Inventory===\n"
         << "Pilih nomor slot di backpack ke berapa (1-36) : ";
    cin >> slot;
    if (slot < 1 || slot > 36)
    {
        cout << "jumlah slot tidak ada (1-36) \n";
    }
    else
    {
        int i = slot - 1;
        if (strcmp(plr->backpack[i].nama, "-") != 0)
        {
            cout << "Slot ini sudah terisi oleh " << plr->backpack[i].nama << "." << endl;
            return;
        }

        cout << "Mengisi slot pada nomor " << slot << endl;
        cout << "Masukkan nama item : ";
        cin.ignore();
        cin.getline(plr->backpack[i].nama, 50); 
        cout << "Masukkan jumlah item : ";
        cin >> plr->backpack[i].jumlah;
        cout << "Masukkan berapa jumlah durability item : ";
        cin >> plr->backpack[i].durability;
        loading();
        cout << "\nBerhasil Menambah item di slot-" << slot << endl;
    }
}

// Menghapus item dari inventory
void hapusItem(player *plr)
{
    int slot;
    cout << "\n=== Buang Item Di INVENTORY ===\n";
    cout << "Pilih No Slot (1-36) : ";
    cin >> slot;

    if (slot < 1 || slot > 36)
    {
        cout << "Nomor Slot tidak ada ! \n";
    }
    else
    {
        int i = slot - 1;

        if (strcmp(plr->backpack[i].nama, "-") == 0)
        {
            cout << "Slot Ini Memang kosong ! \n";
        }
        else
        {
            cout << "Membuang item " << plr->backpack[i].nama << " di slot ke-" << slot << endl;

            strcpy(plr->backpack[i].nama, "-");
            plr->backpack[i].jumlah = 0;
            plr->backpack[i].durability = 0;
            loading();
            cout << "Item berhasil dibuang !\n";
        }
    }
}

// Mencari item menggunakan Sequential Search
void cariItem(player *plr)
{
    string namaCari;
    cout << "\n=== Cari Item Di inventory === \n"
         << "Masukkan nama item yang ingin dicari : ";
    cin.ignore();
    getline(cin, namaCari);

    item temp = plr->backpack[35];
    // Sentinel
    strcpy(plr->backpack[35].nama, namaCari.c_str());
    int i = 0;
    while (strcmp(plr->backpack[i].nama, namaCari.c_str()) != 0)
    {
        i++;
    }
    

    plr->backpack[35] = temp;

    if (i < 35 || strcmp(temp.nama, namaCari.c_str()) == 0)
    {
        cout << "Item " << namaCari << " ditemukan pada slot ke-" << i + 1 << endl;
        cout << "Jumlah     : " << plr->backpack[i].jumlah << "\n"
             << "Durability : " << plr->backpack[i].durability << "\n";
    }
    else
    {
        cout << "Item " << namaCari << " Tidak ditemukan didalam inventory !\n";
    }
}

// 
bool tukarDulu(item itemA, item itemB, int berdasarkan)
{
    if (strcmp(itemA.nama, "-") == 0) return true;
    if (strcmp(itemB.nama, "-") == 0) return false;

    if (berdasarkan == 1)
    {
        return itemA.jumlah < itemB.jumlah; 
    }
    else
    {
        return strcmp(itemA.nama, itemB.nama) < 0;
    }
}

// Sorting menggunakan Bubble Sort
void BubbleSort(player *plr, int berdasarkan)
{
    loading();
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 35 - i; j++)
        {
            if (tukarDulu(plr->backpack[j], plr->backpack[j + 1], berdasarkan))
            {
                item temp = plr->backpack[j];
                plr->backpack[j] = plr->backpack[j + 1]; 
                plr->backpack[j + 1] = temp;
            }
        }
    }
    if (berdasarkan == 1)
        cout << "Tas Berhasil dirapikan berdasarkan JUMLAH item (Bubble Sort)!\n";
    else
        cout << "Tas Berhasil dirapikan berdasarkan ABJAD NAMA item (Bubble Sort)!\n";
}

// Sorting menggunakan Shell Sort
void ShellSort(player *plr, int berdasarkan)
{
    loading();
    int n = 36;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            item temp = plr->backpack[i];
            int j;
            for (j = i; j >= gap && tukarDulu(plr->backpack[j - gap], temp, berdasarkan); j -= gap)
            {
                plr->backpack[j] = plr->backpack[j - gap];
            }
            plr->backpack[j] = temp;
        }
    }
    if (berdasarkan == 1)
        cout << "Tas Berhasil dirapikan berdasarkan JUMLAH item (Shell Sort)!\n";
    else
        cout << "Tas Berhasil dirapikan berdasarkan ABJAD NAMA item (Shell Sort)!\n";
}

// Save data ke akun 
void save(player *plr, string nf)
{
    ofstream fileDitulis(nf, ios::out | ios::binary | ios::trunc);
    if (fileDitulis.is_open())
    {
        fileDitulis.write((char *)plr, sizeof(player));
        fileDitulis.close();
    }
}

//======================================================================|
int main()
{
    player userAktif;
    bool login = false;
    int pilih;
    string namaPlayer, namaFile;

    do
    {
        cout << "\n===== MINECRAFT INVENTORY SYSTEM ===== \n"
             << "1. Bikin Akun baru \n"
             << "2. Login Akun Lama \n"
             << "3. Keluar Program \n"
             << "Pilih (1-3) : ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 3)
        {
            cout << "Keluar dari program. Sampai jumpa!\n";
            return 0;
        }

        if (pilih != 1 && pilih != 2)
        {
            cout << "Pilihan tidak valid! Silakan coba lagi.\n";
            continue;
        }

        cout << "Masukkan Nama Player: ";
        getline(cin, namaPlayer);
        namaFile = namaPlayer + ".dat";

        switch (pilih)
        {
        case 1:
            buatAkunBaru(&userAktif, &login, namaFile, namaPlayer);
            break;
        case 2:
            loginAkun(&userAktif, &login, namaFile);
            break;
        }
        cout << endl;
    } while (!login);

    if (login)
    {
        int menu;
        char mau;
        do
        {
            cout << "\n=== Menu Inventory " << userAktif.username << " === \n"
                 << "1. Lihat Inventory \n"
                 << "2. Tambah Item \n"
                 << "3. Cari item \n"
                 << "4. Merapikan Tas \n"
                 << "5. Buang item \n"
                 << "Pilih: ";
            cin >> menu;
            switch (menu)
            {
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

            case 4:
                int pilihKategori, pilihMetode;

                cout << "\n=== MERAPIKAN TAS (SORTING) ===\n"
                     << "Ingin merapikan berdasarkan apa?\n"
                     << "1. Jumlah Item (Terbanyak -> Tersedikit)\n"
                     << "2. Abjad Nama Item (A -> Z)\n"
                     << "Pilih Kategori (1-2) : ";
                cin >> pilihKategori;

                if (pilihKategori != 1 && pilihKategori != 2)
                {
                    cout << "Pilihan kategori tidak valid! Sorting dibatalkan.\n";
                    break;
                }

                cout << "\nPilih metode algoritma sorting:\n"
                     << "1. Bubble Sort\n"
                     << "2. Shell Sort\n"
                     << "Pilih Metode (1-2) : ";
                cin >> pilihMetode;

                if (pilihMetode == 1)
                {
                    BubbleSort(&userAktif, pilihKategori);
                }
                else if (pilihMetode == 2)
                {
                    ShellSort(&userAktif, pilihKategori);
                }
                else
                {
                    cout << "Pilihan metode tidak valid! Sorting dibatalkan.\n";
                    break;
                }

                save(&userAktif, namaFile);
                cout << "\nSetelah item diurutkan : \n";
                lihatInventory(&userAktif);
                break;

            case 5:
                hapusItem(&userAktif);
                save(&userAktif, namaFile);
                break;

            default:
                cout << "Pilihan menu salah, tidak ada dilist menu !\n";
                break;
            }
            cout << "\nMau ulang ke menu utama ? (y/n) : ";
            cin >> mau;
            loading();
            if (mau == 'n' || mau == 'N')
            {
                save(&userAktif, namaFile);
                cout << "Akun disimpan, Terimakasih " << userAktif.username << " !\n";
            }

        } while (mau == 'y' || mau == 'Y');
    }
    return 0;
}
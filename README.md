# Minecraft Inventory System

## Deskripsi
Minecraft Inventory System adalah aplikasi berbasis C++ yang mensimulasikan sistem inventory dari game Minecraft. Aplikasi ini memungkinkan pengguna untuk membuat akun, mengelola inventory dengan 36 slot, menambah item, menghapus item, mencari item, dan merapikan inventory menggunakan algoritma sorting.

## Fitur Utama
- **Pembuatan Akun Baru** - Membuat akun pemain baru dengan nama unik
- **Login Akun** - Login ke akun yang sudah ada (data disimpan dalam file binary)
- **Lihat Inventory** - Menampilkan isi inventory dalam format tabel dengan kolom Nama Item, Jumlah, dan Durability
- **Tambah Item** - Menambahkan item baru ke dalam slot inventory (36 slot tersedia)
- **Cari Item** - Mencari item dalam inventory berdasarkan nama
- **Hapus Item** - Menghapus item dari slot tertentu
- **Merapikan Tas** - Mengurutkan item berdasarkan jumlah menggunakan dua algoritma:
  - **Bubble Sort** - Algoritma sorting klasik dengan kompleksitas O(n²)
  - **Shell Sort** - Algoritma sorting yang lebih efisien dengan gap sequence

## Teknologi yang Digunakan
- **Bahasa Pemrograman** - C++
- **Library** - iostream, fstream, string, iomanip, windows.h
- **Penyimpanan Data** - Binary File (.dat)
- **Platform** - Windows (menggunakan Windows.h untuk fungsi Sleep)

## Struktur Data
```cpp
struct item {
    char nama[50];      // Nama item
    int jumlah;         // Jumlah item
    int durability;     // Durabilitas item
};

struct player {
    char username[30];  // Nama pemain
    item backpack[36];  // Array inventory dengan 36 slot
};
```

## Cara Menggunakan

### 1. Memulai Aplikasi
```
Jalankan program dan pilih opsi:
1. Bikin Akun baru
2. Login Akun Lama
```

### 2. Menu Utama
Setelah login, Anda akan masuk ke menu inventory dengan pilihan:
1. Lihat Inventory - Menampilkan semua item yang tersimpan
2. Tambah Item - Menambah item ke slot tertentu
3. Cari Item - Mencari item berdasarkan nama
4. Merapikan Tas - Mengurutkan item dengan Bubble Sort atau Shell Sort
5. Buang Item - Menghapus item dari slot tertentu

### 3. Contoh Penggunaan
- Nama item menggunakan '_' untuk spasi (contoh: Iron_Sword)
- Slot inventory bernomor 1-36
- Durability dan jumlah harus berupa angka

## File yang Dihasilkan
- `namaPlayer.dat` - File binary yang menyimpan data inventory pemain
  - Contoh: jika nama player "Isnan", maka akan membuat file "Isnan.dat"

## Algoritma Sorting

### Bubble Sort
- **Kompleksitas Waktu** - O(n²)
- **Metode** - Membandingkan elemen yang berdekatan dan menukar jika diperlukan
- **Cocok untuk** - Data kecil dan pembelajaran algoritma dasar

### Shell Sort
- **Kompleksitas Waktu** - O(n log n) hingga O(n²)
- **Metode** - Menggunakan gap sequence untuk membagi elemen menjadi sub-list
- **Cocok untuk** - Data yang lebih besar dibanding Bubble Sort

## Penulis
- **Isnan**
- **Abner**

## Catatan
- Program ini menggunakan `strcpy` yang bersifat unsafe. Untuk pengembangan lebih lanjut, disarankan menggunakan `strcpy_s` atau fungsi string yang lebih aman
- File data disimpan dalam format binary untuk efisiensi penyimpanan
- Program hanya kompatibel dengan Windows karena penggunaan `windows.h`

## Persyaratan Sistem
- Compiler C++ (g++, Visual Studio, MinGW, dll)
- Windows OS
- Terminal atau Command Prompt

## Cara Kompilasi
```bash
g++ -o ProjectAlpro "ProjectAlpro(Pakai Fstream).cpp"
```

## Cara Menjalankan
```bash
./ProjectAlpro.exe
```

---

*Last Updated: 2026*

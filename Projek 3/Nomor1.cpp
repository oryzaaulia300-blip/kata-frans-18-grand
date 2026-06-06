#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

struct Mobil {
    string platMobil;
    string merkMobil;
    string warnaMobil;
    time_t waktuMasuk;
};

struct Petugas {
    string nama;
    string id;
};

const int MAX_MOBIL = 20;
vector<Mobil*> daftarMobil; // Menggunakan pointer
Petugas petugas;

void cetakGaris() {
    cout << "========================================================================" << endl;
}

void cetakGarisTengah() {
    cout << "------------------------------------------------------------------------" << endl;
}

void tampilAwal() {
    cetakGaris();
    cout << "------------------------  S E L A M A T   D A T A N G  ----------------" << endl;
    cout << "                      DI PORTAL PARKIR KHUSUS MOBIL" << endl;
    cout << "                              MALL PRIENAL" << endl;
    cetakGaris();
    cout << endl;
    cout << "Kami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini." << endl;
    cout << endl;
    cout << "Masukkan nama  : ";
    getline(cin, petugas.nama);
    cout << "Masukkan ID    : ";
    getline(cin, petugas.id);
}

void tampilAwalan() {
    cetakGaris();
    cout << "Nama Petugas : " << petugas.nama << endl;
    cout << "ID Petugas   : " << petugas.id << endl;
    cout << endl;
    cout << "                    TERIMA KASIH ATAS KERJASAMANYA !" << endl;
    cout << "-------------- S E L A M A T   B E R T U G A S ---------------" << endl;
    cetakGaris();
}

void hitungDurasi(time_t waktuMasuk, int &jam, int &menit, int &detik) {
    time_t sekarang = time(0);
    double selisih = difftime(sekarang, waktuMasuk);
    jam   = (int)selisih / 3600;
    menit = ((int)selisih % 3600) / 60;
    detik = (int)selisih % 60;
}

void tambahKendaraan() {
    int jumlah;

    cout << "Masukan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlah;
    cin.ignore();

    if ((int)daftarMobil.size() + jumlah > MAX_MOBIL) {
        if ((int)daftarMobil.size() >= MAX_MOBIL) {
            cout << "Maaf, parkiran hanya dapat memuat " << MAX_MOBIL << " mobil !" << endl;
            return;
        } else {
            cout << "Maaf, parkiran hanya dapat memuat " << MAX_MOBIL << " mobil." << endl;
            jumlah = MAX_MOBIL - (int)daftarMobil.size();
        }
    }

    for (int i = 0; i < jumlah; i++) {
        Mobil* mobil = new Mobil();

        int nomorUrut = (int)daftarMobil.size() + 1;
        cout << endl;
        cout << "Mobil ke " << nomorUrut << endl;
        cout << "Masukkan plat mobil  : ";
        getline(cin, mobil->platMobil);
        cout << "Masukkan merk mobil  : ";
        getline(cin, mobil->merkMobil);
        cout << "Masukkan warna mobil : ";
        getline(cin, mobil->warnaMobil);

        mobil->waktuMasuk = time(0);

        daftarMobil.push_back(mobil);
    }
}

void tampilDaftarKendaraan() {
    cout << endl;
    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :" << endl;
    cetakGaris();

    if (daftarMobil.empty()) {
        cout << "Belum ada mobil yang terparkir." << endl;
        cetakGaris();
        return;
    }

    for (int i = 0; i < (int)daftarMobil.size(); i++) {
        Mobil* m = daftarMobil[i];
        int jam, menit, detik;
        hitungDurasi(m->waktuMasuk, jam, menit, detik);

        cout << "Mobil ke-" << (i + 1) << endl;
        cout << "Plat mobil   : " << m->platMobil << endl;
        cout << "Merk mobil   : " << m->merkMobil << endl;
        cout << "Warna mobil  : " << m->warnaMobil << endl;
        cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik" << endl;
        cetakGarisTengah();
    }

    cetakGaris();
}

void pembayaran() {
    string plat;
    cout << endl;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, plat);

    int index = -1;
    for (int i = 0; i < (int)daftarMobil.size(); i++) {
        if (daftarMobil[i]->platMobil == plat) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "PLAT TIDAK DITEMUKAN !" << endl;
        cout << endl;

        cout << "Masukkan plat mobil yang ingin dibayar : ";
        getline(cin, plat);

        for (int i = 0; i < (int)daftarMobil.size(); i++) {
            if (daftarMobil[i]->platMobil == plat) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "PLAT TIDAK DITEMUKAN !" << endl;
            cetakGaris();
            return;
        }
    }

    Mobil* m = daftarMobil[index];
    int jam, menit, detik;
    hitungDurasi(m->waktuMasuk, jam, menit, detik);

    int totalMenit = jam * 60 + menit + (detik > 0 ? 1 : 0);
    if (totalMenit < 1) totalMenit = 1;
    int biaya = totalMenit * 2000;

    cout << "B I A Y A   P A R K I R : Rp" << biaya << endl;
    cetakGaris();

    delete daftarMobil[index];
    daftarMobil.erase(daftarMobil.begin() + index);
}

void tampilMenu() {
    cout << endl;
    cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
    cout << "1. Tambahkan Daftar Kendaraan" << endl;
    cout << "2. Tampilkan Daftar Kendaraan" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "Masukkan opsi : ";
}

int main() {
    tampilAwal();
    tampilAwalan();

    int opsi;
    do {
        tampilMenu();
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                tambahKendaraan();
                break;
            case 2:
                tampilDaftarKendaraan();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                cout << endl;
                cetakGaris();
                cout << "Terima kasih, " << petugas.nama << ". Sampai jumpa!" << endl;
                cetakGaris();
                break;
            default:
                cout << "Opsi tidak valid! Silahkan coba lagi." << endl;
                break;
        }

    } while (opsi != 4);

    for (int i = 0; i < (int)daftarMobil.size(); i++) {
        delete daftarMobil[i];
    }
    daftarMobil.clear();

    return 0;
}
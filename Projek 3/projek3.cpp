#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

// Struct Barang
struct Barang
{
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

// Prototype Function
void tambahBarang(vector<Barang> &inventaris);
void tampilkanSemua(const vector<Barang> &inventaris);
void cariBarangTermahal(const vector<Barang> &inventaris);
void hitungTotalNilai(const vector<Barang> &inventaris);
void cekRestock(const vector<Barang> &inventaris);
void updateStok(vector<Barang> &inventaris);

int main()
{
    vector<Barang> inventaris;
    int pilihan;

    do
    {
        cout << "\n===================================" << endl;
        cout << "   MENU MANAJEMEN INVENTARIS TOKO" << endl;
        cout << "===================================" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang Termahal" << endl;
        cout << "4. Hitung Total Nilai Inventaris" << endl;
        cout << "5. Cek Restock (Stok < 5)" << endl;
        cout << "6. Update Stok (Pointer)" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahBarang(inventaris);
            break;

        case 2:
            tampilkanSemua(inventaris);
            break;

        case 3:
            cariBarangTermahal(inventaris);
            break;

        case 4:
            hitungTotalNilai(inventaris);
            break;

        case 5:
            cekRestock(inventaris);
            break;

        case 6:
            updateStok(inventaris);
            break;

        case 7:
            cout << "Program berakhir." << endl;
            break;

        default:
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 7);

    return 0;
}

// Fungsi Tambah Barang
void tambahBarang(vector<Barang> &inventaris)
{
    Barang b;

    cout << "\nKode Barang : ";
    cin >> b.kodeBarang;

    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, b.namaBarang);

    // Validasi Harga
    do
    {
        cout << "Harga : ";
        cin >> b.harga;

        if (b.harga < 0)
        {
            cout << "Error! Harga tidak boleh negatif.\n";
        }

    } while (b.harga < 0);

    // Validasi Stok
    do
    {
        cout << "Stok : ";
        cin >> b.stok;

        if (b.stok < 0)
        {
            cout << "Error! Stok tidak boleh negatif.\n";
        }

    } while (b.stok < 0);

    inventaris.push_back(b);

    cout << "Barang berhasil ditambahkan!" << endl;
}

// Fungsi Tampilkan Semua Barang
void tampilkanSemua(const vector<Barang> &inventaris)
{
    if (inventaris.empty())
    {
        cout << "\nData barang kosong!" << endl;
        return;
    }

    cout << "\n========== DAFTAR BARANG ==========" << endl;

    for (const auto &b : inventaris)
    {
        cout << "Kode Barang : " << b.kodeBarang << endl;
        cout << "Nama Barang : " << b.namaBarang << endl;
        cout << "Harga       : Rp." << b.harga << endl;
        cout << "Stok        : " << b.stok << endl;
        cout << "-----------------------------------" << endl;
    }
}

// Fungsi Cari Barang Termahal
void cariBarangTermahal(const vector<Barang> &inventaris)
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong!" << endl;
        return;
    }

    auto termahal = max_element(
        inventaris.begin(),
        inventaris.end(),
        [](const Barang &a, const Barang &b)
        {
            return a.harga < b.harga;
        });

    cout << "\n===== BARANG TERMAHAL =====" << endl;
    cout << "Kode Barang : " << termahal->kodeBarang << endl;
    cout << "Nama Barang : " << termahal->namaBarang << endl;
    cout << "Harga       : Rp." << termahal->harga << endl;
    cout << "Stok        : " << termahal->stok << endl;
}

// Fungsi Hitung Total Nilai Inventaris
void hitungTotalNilai(const vector<Barang> &inventaris)
{
    double total = 0;

    for (const auto &b : inventaris)
    {
        total += b.harga * b.stok;
    }

    cout << "\nTotal Nilai Inventaris = Rp."
         << total << endl;
}

// Fungsi Cek Restock
void cekRestock(const vector<Barang> &inventaris)
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong!" << endl;
        return;
    }

    bool ditemukan = false;

    cout << "\n===== BARANG YANG HARUS RESTOCK =====" << endl;

    for (const auto &b : inventaris)
    {
        if (b.stok < 5)
        {
            cout << "- " << b.namaBarang
                 << " (Stok: " << b.stok << ")" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
    {
        cout << "Tidak ada barang yang perlu restock." << endl;
    }
}

// Fungsi Update Stok Menggunakan Pointer
void updateStok(vector<Barang> &inventaris)
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong!" << endl;
        return;
    }

    string kode;
    cout << "\nMasukkan kode barang: ";
    cin >> kode;

    for (auto &b : inventaris)
    {

        Barang *ptr = &b; // Pointer ke barang

        if (ptr->kodeBarang == kode)
        {

            int perubahan;

            cout << "Stok sekarang: "
                 << ptr->stok << endl;

            cout << "Masukkan perubahan stok (+/-): ";
            cin >> perubahan;

            ptr->stok += perubahan;

            // Validasi stok tidak negatif
            if (ptr->stok < 0)
            {
                ptr->stok = 0;
            }

            cout << "Stok berhasil diperbarui!" << endl;
            return;
        }
    }

    cout << "Kode barang tidak ditemukan!" << endl;
}
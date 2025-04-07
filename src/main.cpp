#include <iostream>
#include "mll.h"

using namespace std;

int main() {
    int pilihan;
    string idNasabah;
    string namaTeller;
    ListTeller LT;
    ListNasabah LN;

    createListTeller(LT);
    createListNasabah(LN);
    teller dataTeller;
    nasabah dataNasabah;
    pilihan = menuUtama();
    while (pilihan != 0) {
        switch (pilihan) {
            // 1. input data Teller
            case 1: {
                cout << "---------------------" << endl;
                cout << "  Input Data Teller  " << endl;
                cout << "---------------------" << endl;
                cout << "ID Teller: "; cin >> dataTeller.idTeller;
                cout << "Nama Teller: "; cin >> dataTeller.namaTeller;
                adr_teller namaTeller = searchTeller(LT, dataTeller.namaTeller);
                if (namaTeller == NULL) {
                    adr_teller P = createElementTeller(dataTeller);
                    insertFirstTeller(LT, P);
                    cout << "Data tersimpan" << endl;
                } else {
                    cout << "Nama Teller bank sudah ada" << endl;
                }

                break;
            }
            // 2. Tampilkan data Teller Bank
            case 2: {
                cout << "---------------------" << endl;
                cout << "     Data Teller     " << endl;
                cout << "---------------------" << endl;
                showTeller(LT);
                break;
            }
            // 3.Hapus Data Teller Bank dan Nasabah
            case 3: {
                string namaTeller;
                cout << "Masukkan nama Teller Bank yang akan di hapus: ";
                cin >> namaTeller; cout << endl;
                deleteTellerAndNasabah(LT, namaTeller);
                break;
            }
            // 4. Cari Data Teller Bank
            case 4: {
                string namaTeller;
                cout << "Masukkan nama Teller Bank yang ingin dicari: ";
                cin >> namaTeller;
                adr_teller tellerFound = searchTeller(LT, namaTeller);
                if (tellerFound != NULL) {
                    cout << "Teller Bank ditemukan: " << endl;
                    cout << "ID Teller Bank: " << info(tellerFound).idTeller << endl;
                    cout << "Nama Teller Bank: " << info(tellerFound).namaTeller << endl;
                } else {
                    cout << "Teller Bank tidak ditemukan." << endl;
                }
                break;

            }
            // 5. Input Data Nasabah
            case 5: {
                char choice = 'y';

                do {
                cout << "--------------------" << endl;
                cout << " Input data Nasabah " << endl;
                cout << "--------------------" << endl;
                cout << "ID Nasabah: "; cin >> dataNasabah.idNasabah;
                cout << "Nama Nasabah: "; cin >> dataNasabah.namaNasabah;
                cout << "Jenis Transaksi: "; cin >> dataNasabah.jenisTransaksi;
                cout << "Nominal Transaksi: "; cin >> dataNasabah.nominalTransaksi;
                adr_teller T = first(LT);
                adr_nasabah idNbh;
                while (T != NULL) {
                    idNbh = searchNasabah(child(T), dataNasabah.idNasabah);
                    if (T != NULL) {
                        break;
                    }
                    T = next(T);
                }
                if (idNbh == NULL){
                    connect(LT, dataNasabah);
                } else {
                    cout << "ID Nasabah sudah ada." << endl;
                }

                cout << "Apakah Anda ingin menambahkan Nasabah lagi? (y/n): ";
                cin >> choice;

                } while (choice == 'y' || choice == 'Y');

                break;
            }
            // 6. Update Data Nasabah
            case 6: {
                string idNasabah;
                cout << "Masukkan ID Nasabah yang ingin diupdate: ";
                cin >> idNasabah;
                adr_teller P = first(LT);
                adr_nasabah NasabahUpdate = NULL;
                while (P != NULL) {
                    NasabahUpdate = searchNasabah(child(P), idNasabah);
                    if (NasabahUpdate != NULL) {
                        break;
                    }
                    P = next(P);
                }
                if (NasabahUpdate != NULL) {
                    cout << "Masukkan Nama Nasabah Baru: ";
                    cin >> info(NasabahUpdate).namaNasabah;
                    cout << "Masukkan Jenis Transaksi Baru: ";
                    cin >> info(NasabahUpdate).jenisTransaksi;
                    cout << "Masukkan Nominal Transaksi Baru: ";
                    cin >> info(NasabahUpdate).nominalTransaksi;
                    cout << "Data Nasabah berhasil diupdate." << endl;
                } else {
                    cout << "Nasabah tidak ditemukan." << endl;
                }
                break;
            }
            // 7. Tampilkan Semua Data Teller Bank dan Nasabah
            case 7: {
                cout << "--------------------------------------" << endl;
                cout << " Data seluruh Teller Bank dan Nasabah " << endl;
                cout << "--------------------------------------" << endl;
                showAll(LT,LN);
                break;
            }
            // 8. Cari Data Nasabah pada Teller Bank tertentu
            case 8: {

                    findNasabahTeller(LT,idNasabah,namaTeller);
                break;

            }
            // 9. Menghapus data Nasabah pada Teller Bank tertentu
            case 9: {
                deleteNasabahFromParent(LT);
                break;
            }
            // 10. Hitung total Transaksi pada Teller Bank tertentu
            case 10: {
                string namaTeller;
                cout << "Masukkan nama Teller untuk menghitung total transaksi: ";
                cin >> namaTeller;
                totalTransaksi(LT, namaTeller);
                break;
            }

            default: {
                cout << "Pilihan tidak valid!" << endl;
                break;
            }

        }
        pilihan = menuUtama();
    }

    return 0;
}



#include <iostream>
#include "mll.h"


void createListTeller(ListTeller &LT) {
  first(LT) = NULL;
  last(LT) = NULL;
}
void createListNasabah(ListNasabah &LN) {
  first(LN) = NULL;
}
adr_teller createElementTeller(teller x) {
    adr_teller T = new elm_teller;
    info(T).idTeller = x.idTeller;
    info(T).namaTeller = x.namaTeller;
    next(T) = NULL;
    prev(T) = NULL;
    //child(T) = new ListNasabah
    createListNasabah(child(T));
    return T;
}
adr_nasabah createElementNasabah(nasabah x) {
    adr_nasabah p = new elm_nasabah;
    info(p).idNasabah = x.idNasabah;
    info(p).namaNasabah = x.namaNasabah;
    info(p).jenisTransaksi = x.jenisTransaksi;
    info(p).nominalTransaksi = 0;
    next(p) = NULL;
    return p;
}


void deleteFirstTeller(ListTeller &LT, adr_teller P) {
    P = first(LT);
    if (first(LT) != last(LT)) {
        first(LT) = next(P);
        next(P) = NULL;
        prev(first(LT)) = NULL;
    } else {
        first(LT) = NULL;
        last(LT) = NULL;
    }
}

void deleteAfterTeller(adr_teller prec, adr_teller P) {
    P = next(prec);
    next(prec) = next(P);
    prev(next(P)) = prec;
    prev(P) = NULL;
    next(P) = NULL;
}

void deleteLastTeller(ListTeller &LT, adr_teller P) {
    P = last(LT);
    if (first(LT) != last(LT)) {
        last(LT) = prev(P);
        next(prev(P)) = NULL;
        prev(P) = NULL;
    } else {
        first(LT) = NULL;
        last(LT) = NULL;
    }
}
void deleteTellerAndNasabah(ListTeller &LT, string namaTeller) {
    adr_teller Q = searchTeller(LT, namaTeller);
    if (Q == NULL) {
        cout << "Teller tidak ditemukan" << endl;
    } else {
        if (Q == first(LT)) {
            deleteFirstTeller(LT, Q);
        } else if (Q == last(LT)) {
            deleteLastTeller(LT, Q);
        } else {
            adr_teller prec = first(LT);
                while (next(prec) != Q) {
                    prec = next(prec);
                }
            deleteAfterTeller(prec, Q);
        }
        cout << "Teller " << namaTeller <<" dan seluruh nasabahnya telah dihapus." << endl;
    }

}

adr_teller searchTeller(ListTeller LT, string nama) {
    adr_teller T = first(LT);
    while (T != NULL) {
        if(info(T).namaTeller == nama) {
            return T;
        }
        T = next(T);
    }
    return NULL;
}

adr_nasabah searchNasabah(ListNasabah LN, string NasabahID) {
    adr_nasabah P = first(LN);
    while (P != NULL) {
        if (info(P).idNasabah == NasabahID) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

// Mengubah data parent / data child
void updateTellerData(adr_teller &P, teller newData) {
    if (P != NULL) {
        info(P).idTeller = newData.idTeller;
        info(P).namaTeller = newData.namaTeller;
    } else {
        cout << "Teller tidak ditemukan!" << endl;
    }
}

// Mengubah data child (nasabah) pada teller tertentu
void updateNasabahData(adr_nasabah &P, nasabah newData) {
    if (P != NULL) {  // Memastikan bahwa pointer P tidak kosong
        // Memperbarui semua data dalam nasabah dengan data baru menggunakan makro info(P)
        info(P).idNasabah = newData.idNasabah;
        info(P).namaNasabah = newData.namaNasabah;
        info(P).jenisTransaksi = newData.jenisTransaksi;
        info(P).nominalTransaksi = newData.nominalTransaksi;

        cout << "Data Nasabah telah berhasil diperbarui." << endl;
    } else {
        cout << "Nasabah tidak ditemukan!" << endl;
    }
}

void deleteNasabahFromParent(ListTeller &LT) {
    string namaTeller, idNasabah;
    cout << "Masukkan Nama Teller Bank: ";
    cin >> namaTeller;

    adr_teller Par = searchTeller(LT, namaTeller);
    if (Par != NULL) {
        // tampilkan data Nasabah pada Teller yang dicari
        ListNasabah &LN = child(Par);
        cout << "Daftar nasabah teller " << namaTeller << ":" << endl;
        adr_nasabah temp = first(LN);
        while (temp != NULL) {
            cout << "- ID: " << info(temp).idNasabah
                 << ", Nama: " << info(temp).namaNasabah << endl;
            temp = next(temp);
        }

        cout << "Masukkan ID Nasabah yang akan dihapus: ";
        cin >> idNasabah;

        adr_nasabah Ch = searchNasabah(LN, idNasabah);
        if (Ch != NULL) {
            adr_nasabah prec = NULL;
            if (Ch == first(LN)) {
                deleteFirstNasabah(LN, Ch);
            } else {
                prec = first(LN);
                while (next(prec) != Ch) {
                    prec = next(prec);
                }
                deleteAfterNasabah(LN, prec, Ch);
            }
            cout << "Nasabah dengan ID " << idNasabah << " berhasil dihapus." << endl;
        } else {
            cout << "Nasabah dengan ID " << idNasabah << " tidak ditemukan." << endl;
        }
    } else {
        cout << "Teller dengan nama " << namaTeller << " tidak ditemukan!" << endl;
    }
}

void deleteFirstNasabah(ListNasabah &LN, adr_nasabah P){
    if (first(LN) != NULL) {
        P = first(LN);
        first(LN) = next(P);
        next(P) = NULL;
    } else {
        first(LN) = NULL;
    }
}
void deleteLastNasabah(ListNasabah &LN, adr_nasabah P){
    adr_nasabah Q = first(LN);
    while (next(next(Q)) != NULL) {
        Q = next(Q);
    }
    P = next(Q);
    next(Q) = NULL;
}
void deleteAfterNasabah(ListNasabah &LN, adr_nasabah prec, adr_nasabah P){
    P = next(prec);
    next(prec) = next(P);
    next(P) = NULL;
}

void totalTransaksi(ListTeller LT, string namaTeller) {
    adr_teller T = searchTeller(LT, namaTeller);
    if (T != NULL) {
        int totalTransaksi = 0;
        adr_nasabah N = first(child(T));
        while (N != NULL) {
            totalTransaksi++;
            N = next(N);
        }
        cout << "Total transaksi untuk Teller " << namaTeller << " adalah: " << totalTransaksi << endl;
    }else {
        cout << "Teller dengan nama " << namaTeller << " tidak ditemukan." << endl;
    }
}

void insertFirstTeller(ListTeller &LT, adr_teller P){
     if((first(LT) == NULL) && (last(LT) == NULL)){
        first(LT) = P;
        last(LT) = P;
    }else{
        next(P) = first(LT);
        prev(first(LT)) = P;
        first(LT) = P;
    }
}
void insertLastNasabah(ListNasabah &LN, adr_nasabah P){
    if (first(LN) == NULL) {
        first(LN) = P;
    } else {
        adr_nasabah Q;
        Q = first(LN);
        while (next(Q)!=NULL){
            Q=next(Q);
        }
        next(Q)=P;
  }

}

int menuUtama() {
    cout << "------------------------------------------" << endl;
    cout << "                MENU UTAMA                " << endl;
    cout << "------------------------------------------" << endl;
    cout << "1. Input Data Teller Bank";
    cout << "\n2. Tampilkan Data Teller Bank";
    cout << "\n3. Hapus Data Teller Bank dan Nasabah";
    cout << "\n4. Cari Data Teller Bank";
    cout << "\n5. Input Data Nasabah";
    cout << "\n6. Update Data Nasabah";
    cout << "\n7. Tampilkan Semua Data Teller Bank dan Nasabah";
    cout << "\n8. Cari Data Nasabah pada Teller Bank tertentu";
    cout << "\n9. Menghapus data Nasabah pada Teller Bank tertentu ";
    cout << "\n10. Hitung total Transaksi pada Teller Bank tertentu";
    cout << "\n0. Exit\n";
    cout << "Pilih Menu: ";
    int input = 0;
    cin >> input;
    return input;
}

void showTeller(ListTeller LT){
    adr_teller B = first(LT);
    int i = 1;
    cout << "Daftar Teller: " << endl;
    if (B != NULL) {
        while (B != NULL) {
            cout << i << ". idTeller : " << info(B).idTeller << endl;
            cout << "   Nama Teller : " << info(B).namaTeller << endl;
            i++;
            B = next(B);
        }
    } else {
        cout << "Data Teller kosong" << endl;
    }

}

void showAll(ListTeller &LT , ListNasabah &LN){
    adr_teller P = first(LT);
    if(P == NULL){
        cout << "Tidak Ada Data Teller" << endl;
    } else{
        cout << "Data Teller : " << endl;
        cout << "---------------------" << endl;
        while(P != NULL){
            cout << "Nama : " << info(P).namaTeller << endl;
            cout << "ID : " << info(P).idTeller << endl;
            cout << endl;
            cout << "Data Nasabah: " << endl;
            adr_nasabah M  = first(LN);
            if(M == NULL){
                cout << "--------------------------" << endl;
                cout << "Tidak Ada Data Nasabah" << endl;
                cout << "--------------------------" << endl;
            }else{
                while(M != NULL){
                    cout << "Nama : " << info(M).namaNasabah << endl;
                    cout << "ID : " << info(M).idNasabah << endl;
                    cout << "Jenis transaksi : " << info(M).jenisTransaksi << endl;
                    cout << "Jumlah Transaksi : " << info(M).nominalTransaksi << endl;
                    if(next(M) != NULL){
                        cout << endl;
                    }
                    M = next(M);
                }
            }
            cout << "---------------------" << endl;
            P = next(P);
        }
    }

}

void connect(ListTeller LT, nasabah dataNasabah) {
    string namaTeller;
    cout << "Nama Teller: "; cin >> namaTeller;
    adr_teller Q = searchTeller(LT, namaTeller);
    if (Q != NULL) {
        adr_nasabah P = createElementNasabah(dataNasabah);
        insertLastNasabah(child(Q),P);
        cout << "Data Tersimpan." << endl;
    } else {
        cout << "nama Teller tidak ditemukan." << endl;
    }
}

void findNasabahTeller(ListTeller &LT, string idNasabah , string namaTeller) {
    adr_teller P = first(LT);
    if(P == NULL){
        cout << "Belum ada data nasabah!" << endl;
        cout << endl;
    }else{
        cout << "Cari id Nasabah: ";
        cin >> idNasabah;
        cout << "Cari di teller mana?: ";
        cin >> namaTeller;
        bool ketemu = false;

        while (P != NULL) {
            adr_nasabah T = first(child(P));
            while (T != NULL) {
                if (info(T).idNasabah == idNasabah && info(P).namaTeller == namaTeller) {
                    cout << "\nNama nasabah di Teller: " << info(P).namaTeller << endl;
                    cout << " - Nama Nasabah : " << info(T).namaNasabah << endl;
                    cout << "   id Nasabah   : " << info(T).idNasabah << endl;
                    cout << "   Jenis Transaksi    : " << info(T).jenisTransaksi << endl;
                     cout << "   Total Transaksi    : " << info(T).nominalTransaksi << endl;
                    ketemu = true;
                    break;
                }
                T = next(T);
            }
            if (ketemu) break;
            P = next(P);
        }

        if (!ketemu) {
            cout << "\n tidak ditemukan nama nasabah tersebut .\n" << endl;
        }
    }
}


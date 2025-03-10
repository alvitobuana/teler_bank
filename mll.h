#ifndef TELLER_H_INCLUDED
#define TELLER_H_INCLUDED
#include <iostream>
#define info(P) P->info
#define next(P) P->next
#define prev(P) P->prev
#define first(L) L.first
#define last(L) L.last
#define child(P) P->child
using namespace std;

// ADT Nasabah

struct nasabah {
    string idNasabah;
    string namaNasabah;
    string jenisTransaksi;
    int nominalTransaksi;
};

typedef struct elm_nasabah *adr_nasabah;

struct elm_nasabah {
    nasabah info;
    adr_nasabah next;

};

struct ListNasabah {
    adr_nasabah first;
};

// ADT Teller Bank

struct teller {
    string idTeller;
    string namaTeller;
};

typedef struct elm_teller *adr_teller;

struct elm_teller {
    teller info;
    adr_teller next;
    adr_teller prev;
    ListNasabah child;

};

struct ListTeller {
    adr_teller first;
    adr_teller last;
};



void createListTeller(ListTeller &LT);
void createListNasabah(ListNasabah &LN);
adr_teller createElementTeller(teller x);
adr_nasabah createElementNasabah(nasabah x);
//insert
void insertFirstTeller(ListTeller &LT, adr_teller P);
void insertLastNasabah(ListNasabah &LN, adr_nasabah P);
// FIND
adr_teller searchTeller(ListTeller LT, string namaTeller);
adr_nasabah searchNasabah(ListNasabah LN, string idNasabah);
void findNasabahTeller(ListTeller &LT, string idNasabah, string namaTeller);
// DELETE TELLER
void deleteFirstTeller(ListTeller &LT, adr_teller P);
void deleteAfterTeller(adr_teller prec, adr_teller P);
void deleteLastTeller(ListTeller &LT, adr_teller P);
void deleteTellerAndNasabah(ListTeller &LT, string namaTeller);
//DELETE NASABAH
void deleteFirstNasabah(ListNasabah &LN, adr_nasabah P);
void deleteLastNasabah(ListNasabah &LN, adr_nasabah P);
void deleteAfterNasabah(ListNasabah &LN, adr_nasabah prec, adr_nasabah P);
void deleteNasabahFromParent(ListTeller &LT);
//menhitung total transaksi
void totalTransaksi(ListTeller LT, string namaTeller);
//Tampilan
int menuUtama();
void showTeller(ListTeller LT);
void showAll(ListTeller &LT , ListNasabah &LN);
//Menunjuk ke Nasabah
void connect(ListTeller LT, nasabah dataNasabah);

#endif // TELLER_H_INCLUDED

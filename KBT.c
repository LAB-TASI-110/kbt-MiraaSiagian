#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk atoi

#define MAX_PENUMPANG 8

// Struktur data untuk Penumpang
struct Penumpang {
    char nama[50];
    int nomorKursi; // 1-8
    char rute[20];  // Balige-Medan atau Tarutung-Medan
    int totalBayar;
};

// Array untuk merepresentasikan 8 kursi armada L300
// 0 = kosong, 1 = terisi
int kursi[MAX_PENUMPANG];

// Array untuk menyimpan data penumpang
struct Penumpang manifest[MAX_PENUMPANG];
int jumlahPenumpang = 0; // Counter untuk penumpang yang terdaftar

int main() {
    int i;
    // Inisialisasi semua kursi kosong saat program dimulai
    for (i = 0; i < MAX_PENUMPANG; i++) {
        kursi[i] = 0;
    }

    int pilihan;
    do {
        printf("\n=====================================\n");
        printf(" SISTEM TICKETING KBT TAPANULI\n");
        printf("=====================================\n");
        printf("1. Lihat Ketersediaan Kursi\n");
        printf("2. Pesan Tiket\n");
        printf("3. Tampilkan Manifest Penumpang\n");
        printf("4. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        // Clear input buffer setelah scanf
        while (getchar() != '\n'); 

        switch (pilihan) {
            case 1: // Lihat Ketersediaan Kursi
                printf("\n--- Denah Kursi Armada L300 ---\n");
                for (i = 0; i < MAX_PENUMPANG; i++) {
                    printf("| Kursi %d: %s ", i + 1, (kursi[i] == 0) ? "KOSONG" : "TERISI");
                    if ((i + 1) % 2 == 0) { // Setiap 2 kursi, buat baris baru untuk visual
                        printf("|\n");
                    }
                }
                if (MAX_PENUMPANG % 2 != 0) { // Jika jumlah kursi ganjil
                    printf("|\n");
                }
                printf("-------------------------------\n");
                break;
            case 2: // Pesan Tiket
                if (jumlahPenumpang >= MAX_PENUMPANG) {
                    printf("Maaf, semua kursi sudah terisi.\n");
                } else {
                    struct Penumpang p;

                    printf("\n--- Pesan Tiket ---\n");
                    printf("Nama Penumpang: ");
                    scanf("%s", p.nama);

                    int pilihanRute;
                    printf("Pilih Rute:\n");
                    printf("1. Balige-Medan (Rp150.000)\n");
                    printf("2. Tarutung-Medan (Rp170.000)\n");
                    printf("Pilihan Anda: ");
                    scanf("%d", &pilihanRute);
                    // Clear input buffer
                    while (getchar() != '\n'); 

                    switch (pilihanRute) {
                        case 1:
                            strcpy(p.rute, "Balige-Medan");
                            p.totalBayar = 150000;
                            break;
                        case 2:
                            strcpy(p.rute, "Tarutung-Medan");
                            p.totalBayar = 170000;
                            break;
                        default:
                            printf("Pilihan rute tidak valid.\n");
                            continue; // Kembali ke menu utama jika rute tidak valid
                    }

                    int nomorKursiPesan;
                    printf("Pilih Nomor Kursi (1-%d): ", MAX_PENUMPANG);
                    scanf("%d", &nomorKursiPesan);
                    // Clear input buffer
                    while (getchar() != '\n'); 

                    if (nomorKursiPesan < 1 || nomorKursiPesan > MAX_PENUMPANG) {
                        printf("Nomor kursi tidak valid.\n");
                    } else if (kursi[nomorKursiPesan - 1] == 1) {
                        printf("Kursi %d sudah terisi. Silakan pilih kursi lain.\n", nomorKursiPesan);
                    } else {
                        p.nomorKursi = nomorKursiPesan;
                        kursi[nomorKursiPesan - 1] = 1; // Tandai kursi sebagai terisi
                        manifest[jumlahPenumpang] = p; // Tambahkan penumpang ke manifest
                        jumlahPenumpang++;

                        printf("Tiket berhasil dipesan untuk %s (Kursi %d, Rute %s, Total Bayar Rp%d).\n",
                               p.nama, p.nomorKursi, p.rute, p.totalBayar);
                    }
                }
                break;
            case 3: // Tampilkan Manifest Penumpang
                printf("\n--- Manifest Penumpang KBT ---\n");
                if (jumlahPenumpang == 0) {
                    printf("Tidak ada penumpang terdaftar saat ini.\n");
                } else {
                    printf("%-20s %-10s %-15s %-15s\n", "Nama", "Kursi", "Rute", "Total Bayar");
                    printf("-------------------------------------------------------------\n");
                    for (i = 0; i < jumlahPenumpang; i++) {
                        printf("%-20s %-10d %-15s %-15d\n",
                               manifest[i].nama,
                               manifest[i].nomorKursi,
                               manifest[i].rute,
                               manifest[i].totalBayar);
                    }
                    printf("-------------------------------------------------------------\n");
                }
                break;
            case 4: // Keluar
                printf("Terima kasih telah menggunakan SISTEM TICKETING KBT TAPANULI.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (pilihan != 4);

    return 0;
}

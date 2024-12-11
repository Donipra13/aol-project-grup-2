#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur menu
typedef struct {
    int id;         //ID menu
    char name[50];  //nama menu
    float price;    //harga menu
    int quantitySold; // Jumlah yang terjual
} MenuItem;

// Struktur member
typedef struct {
    char name[50];  //nama member
    int purchases; // Jumlah pembelian
    float totalSpent; // Total pengeluaran
} Member;

// Fungsi untuk menampilkan menu
void displayMenu(MenuItem menu[], int size) {
    printf("\n========== Menu Restoran ==========\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - Rp%.2f\n",
               menu[i].id, menu[i].name, menu[i].price);
    }
    printf("===================================\n");
}

// Fungsi untuk membaca data member dari file
int loadMembers(Member members[], int maxSize) {
    FILE *file = fopen("members.txt", "r");
    if (!file) {
        return 0;
    }
    char buffer[50];
    fgets(buffer,50,file);
    int count = 0;
    while (fscanf(file, "%49[^,],%d,%f\n",
                  members[count].name,
                  &members[count].purchases,
                  &members[count].totalSpent) != EOF && count < maxSize) {
        count++;
    }

    fclose(file);
    return count;
}

// Fungsi untuk menyimpan data member ke file
void saveMembers(Member members[], int count) {
    FILE *file = fopen("members.txt", "w");
    if (!file) {
        printf("Gagal menyimpan data member!\n");
        return;
    }
    fprintf(file,"Nama,Frekuensi Pembelian,Total Spent\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%.2f\n",
                members[i].name,
                members[i].purchases,
                members[i].totalSpent);
    }

    fclose(file);
}

void loadMenuStatistics(MenuItem menu[], int size) {
    FILE *file = fopen("menu_statistics.txt", "r");
    if (!file) {
        printf("File statistik menu tidak ditemukan. Menggunakan data default.\n");
        return;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), file); // Lewati header (ID,Name,QuantitySold)

    int id, quantitySold;
    while (fscanf(file, "%d,%*[^,],%d\n", &id, &quantitySold) != EOF) {
        if (id >= 1 && id <= size) {
            menu[id - 1].quantitySold = quantitySold;
        }
    }

    fclose(file);
}
// Fungsi untuk menyortir menu berdasarkan jumlah terjual
void sortMenuByQuantitySold(MenuItem menu[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (menu[j].quantitySold < menu[j + 1].quantitySold) {
                // Tukar elemen jika menu[j] lebih kecil dari menu[j+1]
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk menyimpan statistik penjualan menu ke file
void saveMenuStatistics(MenuItem menu[], int size) {
    sortMenuByQuantitySold(menu, size); // Sortir menu berdasarkan jumlah terjual

    FILE *file = fopen("menu_statistics.txt", "w");
    if (!file) {
        printf("Gagal menyimpan statistik menu!\n");
        return;
    }

    fprintf(file, "ID,Name,QuantitySold\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%s,%d\n",
                menu[i].id,
                menu[i].name,
                menu[i].quantitySold);
    }

    fclose(file);
}

int main() {
    // Daftar menu
    MenuItem menu[] = {
        {1, "Nasi Goreng", 25000.0, 0},
        {2, "Mie Goreng", 20000.0, 0},
        {3, "Ayam Bakar", 30000.0, 0},
        {4, "Bebek Goreng", 25000.0, 0},
        {5, "Pecel Lele", 18000.0, 0},
        {6, "Nasi Bakar", 18000.0, 0},
        {7, "Teh Hangat", 8000.0, 0},
        {8, "Es Teh", 8000.0, 0},
        {9, "Jus Jeruk", 12000.0, 0},
        {10, "Matcha", 12000.0, 0},
        {11, "Kopi Panas", 10000.0, 0},
        {12, "Es Kopi", 11000.0, 0}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    loadMenuStatistics(menu, menuSize);
    // Daftar member
    Member members[100];
    int memberCount = loadMembers(members, 100);
    printf("=============================================\n");
    printf("            Rumah Makan Sederhana            \n");
    printf("=============================================\n");
    // Variabel untuk sistem
    char name[50], table[10];
    int choice, qty, memberIndex = -1;
    float total = 0;

    printf("Selamat datang di Rumah Makan Sederhana\n");

    // Masukkan data member
    printf("Masukkan nama Anda: ");
    scanf(" %[^\n]", name);

    // Cek apakah member sudah ada
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            memberIndex = i;
            break;
        }
    }

    // Jika member baru, tambahkan ke daftar
    if (memberIndex == -1) {
        strcpy(members[memberCount].name, name);
        members[memberCount].purchases = 0;
        members[memberCount].totalSpent = 0;
        memberIndex = memberCount;
        memberCount++;
    }

    while (1) {
        // Tampilkan menu utama
        printf("\nPilihan:\n");
        printf("1. Lihat Menu\n");
        printf("2. Pesan Makanan\n");
        printf("3. Lihat Total Tagihan\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);
        int jumlah;
        switch (choice) {
            case 1: // Lihat Menu
                displayMenu(menu, menuSize);
                break;
            case 2: // Pesan Makanan

                printf("Masukkan jumlah menu: ");
                scanf("%d",&jumlah);

                for(int p=0; p<jumlah; p++){
                    printf("Masukkan nomor menu %d yang ingin dipesan: ", p+1);

                    scanf("%d", &choice);

                    if (choice >= 1 && choice <= menuSize) {
                        printf("Masukkan jumlah: ");
                        scanf("%d", &qty);

                        float price = menu[choice - 1].price * qty;
                        total += price;
                        members[memberIndex].totalSpent += price;
                        menu[choice - 1].quantitySold += qty; // Tambahkan jumlah terjual
                        printf("----------------------------------------------------------------\n");
                        printf("Pesanan %s sebanyak %d berhasil ditambahkan.\n", menu[choice - 1].name, qty);
                        printf("----------------------------------------------------------------\n");
                        members[memberIndex].purchases += qty;
                    } else {
                        printf("----------------------------------------------------------------\n");
                        printf("Pilihan menu tidak valid!\n");
                        printf("----------------------------------------------------------------\n");
                        p--;
                    }
                }
                break;
            case 3: // Lihat Total Tagihan
                printf("--------------------------------------\n");
                printf("Total tagihan Anda: Rp%.2f\n", total);
                 printf("--------------------------------------\n");
                break;
            case 4: // Keluar
                printf("Terima kasih telah berkunjung. Sampai jumpa!\n");
                saveMembers(members, memberCount); //simpan data member
                saveMenuStatistics(menu, menuSize); // Simpan statistik menu
                exit(0);
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    }

    return 0;
}

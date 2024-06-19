#include <iostream>
#include <string>
#define MAX 5  // Ukuran maksimal antrian

using namespace std;

struct Patient {
    int id;
    string name;
};

struct Queue {
    int front, rear;
    Patient queue[MAX];
};

void initializeQueue(Queue &q) {
    q.front = -1;
    q.rear = -1;
}

// Fungsi untuk menambahkan pasien ke dalam antrian
void Enqueue(Queue &q, int id, string name) {
    if (q.rear == MAX - 1) {
        cout << "Antrian penuh. Tidak bisa menambahkan pasien.\n";
    } else {
        if (q.front == -1)
            q.front = 0;
        q.queue[++q.rear].id = id;
        q.queue[q.rear].name = name;
        cout << "Pasien dengan ID " << id << " dan Nama " << name << " telah ditambahkan ke antrian.\n";
    }
}

// Fungsi untuk mengeluarkan pasien dari antrian
void Dequeue(Queue &q) {
    if (q.front == -1 || q.front > q.rear) {
        cout << "Antrian kosong. Tidak ada pasien untuk dikeluarkan.\n";
    } else {
        cout << "Pasien dengan ID " << q.queue[q.front].id << " dan Nama " << q.queue[q.front].name << " telah dipanggil.\n";
        q.front++;
        if (q.front > q.rear) {
            q.front = q.rear = -1; // Reset antrian jika kosong
        }
    }
}

// Fungsi untuk menampilkan antrian
void Display(Queue &q) {
    if (q.front == -1) {
        cout << "Antrian kosong.\n";
    } else {
        cout << "====================================\n";
        cout << "|         ANTRIAN SAAT INI         |\n";
        cout << "====================================\n";
        for (int i = q.front; i <= q.rear; i++) {
            cout << "ID: " << q.queue[i].id << endl;
            cout << "Nama: " << q.queue[i].name << endl;
            cout << "====================================" << endl;
        }
    }
}

int main() {
    Queue q;
    initializeQueue(q);
    int choice, id;
    string name;

    do {
        cout << "====================================\n";
        cout << "|    Sistem Antrian Rumah Sakit    |\n";
        cout << "====================================\n";
        cout << "| 1. Tambahkan Pasien (Enqueue)    |\n";
        cout << "| 2. Pemanggilan Pasien (Dequeue)  |\n";
        cout << "| 3. Tampilkan Antrian (Display)   |\n";
        cout << "| 4. Keluar                        |\n";
        cout << "====================================\n";
        cout << "Masukkan Pilihan: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Masukkan ID Pasien: ";
            cin >> id;
            cin.ignore();  // Membersihkan buffer input
            cout << "Masukkan Nama Pasien: ";
            getline(cin, name);
            Enqueue(q, id, name);
            break;
        case 2:
            Dequeue(q);
            break;
        case 3:
            Display(q);
            break;
        case 4:
            cout << "Keluar dari sistem.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 4);

    return 0;
}
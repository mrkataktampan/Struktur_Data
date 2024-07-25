#include <iostream>
using namespace std;

// Struktur node untuk binary tree
struct Node {
    int data;
    Node* kiri;
    Node* kanan;
    
    Node(int nilai) : data(nilai), kiri(NULL), kanan(NULL) {}
};

// Fungsi untuk menambah node baru ke dalam binary tree
Node* tambahNode(Node* akar, int nilai) {
    if (akar == NULL) {
        return new Node(nilai);
    }
    if (nilai < akar->data) {
        akar->kiri = tambahNode(akar->kiri, nilai);
    } else {
        akar->kanan = tambahNode(akar->kanan, nilai);
    }
    return akar;
}

// Pre-order traversal
void preOrder(Node* akar) {
    if (akar == NULL) {
        return;
    }
    cout << akar->data << " ";
    preOrder(akar->kiri);
    preOrder(akar->kanan);
}

// In-order traversal
void inOrder(Node* akar) {
    if (akar == NULL) {
        return;
    }
    inOrder(akar->kiri);
    cout << akar->data << " ";
    inOrder(akar->kanan);
}

// Post-order traversal
void postOrder(Node* akar) {
    if (akar == NULL) {
        return;
    }
    postOrder(akar->kiri);
    postOrder(akar->kanan);
    cout << akar->data << " ";
}

// Fungsi untuk mencari elemen dalam binary tree
bool cari(Node* akar, int kunci) {
    if (akar == NULL) {
        return false;
    }
    if (akar->data == kunci) {
        return true;
    } else if (kunci < akar->data) {
        return cari(akar->kiri, kunci);
    } else {
        return cari(akar->kanan, kunci);
    }
}

// Fungsi untuk menghitung tinggi binary tree
int tinggi(Node* akar) {
    if (akar == NULL) {
        return 0;
    }
    int tinggiKiri = tinggi(akar->kiri);
    int tinggiKanan = tinggi(akar->kanan);
    return max(tinggiKiri, tinggiKanan) + 1;
}

int main() {
    Node* akar = NULL;
    int pilihan, nilai;
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah elemen ke dalam tree\n";
        cout << "2. Tampilkan pre-order traversal\n";
        cout << "3. Tampilkan in-order traversal\n";
        cout << "4. Tampilkan post-order traversal\n";
        cout << "5. Cari elemen dalam tree\n";
        cout << "6. Hitung tinggi tree\n";
        cout << "7. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                cout << "Masukkan nilai: ";
                cin >> nilai;
                akar = tambahNode(akar, nilai);
                break;
            case 2:
                cout << "Pre-order traversal: ";
                preOrder(akar);
                cout << endl;
                break;
            case 3:
                cout << "In-order traversal: ";
                inOrder(akar);
                cout << endl;
                break;
            case 4:
                cout << "Post-order traversal: ";
                postOrder(akar);
                cout << endl;
                break;
            case 5:
                cout << "Masukkan nilai yang ingin dicari: ";
                cin >> nilai;
                if (cari(akar, nilai)) {
                    cout << "Nilai ditemukan dalam tree.\n";
                } else {
                    cout << "Nilai tidak ditemukan dalam tree.\n";
                }
                break;
            case 6:
                cout << "Tinggi tree: " << tinggi(akar) << endl;
                break;
            case 7:
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
    
    return 0;
}
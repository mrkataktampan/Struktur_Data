#include <iostream>  // Menggunakan input-output standar C++
#include <stack>     // Menggunakan struktur data stack
#include <string>    // Menggunakan tipe data string

using namespace std;  // Menggunakan namespace std untuk mempermudah penggunaan objek dan fungsi dari std

// Fungsi untuk membersihkan layar konsol
void clearScreen() {
    cout << "\033[2J\033[1;1H";  // ANSI escape sequence untuk membersihkan layar dan menggeser kursor ke (1,1)
}

// Fungsi untuk menambahkan teks baru
void typeText(string& currentText, stack<string>& undoStack, stack<string>& redoStack) {
    cout << "Masukkan teks yang ingin ditambahkan: ";  // Menampilkan pesan untuk meminta input teks
    string newText;  // Mendeklarasikan variabel untuk menyimpan teks baru
    getline(cin, newText);  // Mengambil input teks dari pengguna
    
    // Menyimpan teks saat ini dalam undoStack untuk digunakan pada operasi undo
    undoStack.push(currentText);
    
    // Jika currentText tidak kosong, tambahkan koma dan spasi sebelum menambahkan newText
    if (!currentText.empty()) {
        currentText += ", ";
    }
    currentText += newText;  // Menambahkan newText ke currentText
    
    redoStack = stack<string>();  // Mengosongkan redoStack karena operasi baru telah dilakukan
}

// Fungsi untuk melakukan operasi undo
void performUndo(string& currentText, stack<string>& undoStack, stack<string>& redoStack) {
    if (!undoStack.empty()) {  // Memeriksa apakah undoStack tidak kosong
        redoStack.push(currentText);  // Menyimpan teks saat ini dalam redoStack untuk operasi redo
        currentText = undoStack.top();  // Mengembalikan teks sebelumnya dari undoStack
        undoStack.pop();  // Menghapus teks sebelumnya dari undoStack
        cout << "Undo berhasil dilakukan." << endl;  // Menampilkan pesan keberhasilan operasi undo
    } else {
        cout << "Tidak ada operasi undo yang dapat dilakukan." << endl;  // Menampilkan pesan ketika undoStack kosong
    }
}

// Fungsi untuk melakukan operasi redo
void performRedo(string& currentText, stack<string>& undoStack, stack<string>& redoStack) {
    if (!redoStack.empty()) {  // Memeriksa apakah redoStack tidak kosong
        undoStack.push(currentText);  // Menyimpan teks saat ini dalam undoStack untuk operasi undo
        currentText = redoStack.top();  // Mengembalikan teks yang dibatalkan dari redoStack
        redoStack.pop();  // Menghapus teks yang dibatalkan dari redoStack
        cout << "Redo berhasil dilakukan." << endl;  // Menampilkan pesan keberhasilan operasi redo
    } else {
        cout << "Tidak ada operasi redo yang dapat dilakukan." << endl;  // Menampilkan pesan ketika redoStack kosong
    }
}

// Fungsi untuk menampilkan status kosongnya undoStack
void checkEmptyUndo(stack<string>& undoStack) {
    cout << "IsEmptyUndo: " << (undoStack.empty() ? "true" : "false") << endl;  // Menampilkan status kosongnya undoStack
}

// Fungsi untuk menampilkan status kosongnya redoStack
void checkEmptyRedo(stack<string>& redoStack) {
    cout << "IsEmptyRedo: " << (redoStack.empty() ? "true" : "false") << endl;  // Menampilkan status kosongnya redoStack
}

// Fungsi utama (main) dari program
int main() {
    stack<string> undoStack;  // Mendeklarasikan stack untuk operasi undo
    stack<string> redoStack;  // Mendeklarasikan stack untuk operasi redo
    string currentText;  // Mendeklarasikan variabel untuk menyimpan teks saat ini yang dikelola

    // Loop utama untuk menampilkan menu dan memproses input pengguna
    while (true) {
        clearScreen();  // Memanggil fungsi untuk membersihkan layar konsol
        cout << "Teks saat ini: " << currentText << endl;  // Menampilkan teks saat ini yang sedang dikelola
        cout << "1. Ketik teks" << endl;  // Menampilkan opsi untuk menambahkan teks baru
        cout << "2. Undo" << endl;  // Menampilkan opsi untuk melakukan undo
        cout << "3. Redo" << endl;  // Menampilkan opsi untuk melakukan redo
        cout << "4. IsEmptyUndo" << endl;  // Menampilkan opsi untuk memeriksa apakah undoStack kosong
        cout << "5. IsEmptyRedo" << endl;  // Menampilkan opsi untuk memeriksa apakah redoStack kosong
        cout << "6. Keluar" << endl;  // Menampilkan opsi untuk keluar dari program
        cout << "Masukkan pilihan anda: ";  // Menampilkan pesan untuk meminta input pilihan

        int choice;  // Mendeklarasikan variabel untuk menyimpan pilihan pengguna
        cin >> choice;  // Mengambil input pilihan pengguna
        cin.ignore();  // Mengabaikan newline character dari buffer input

        // Menggunakan switch-case untuk memproses pilihan pengguna
        switch (choice) {
            case 1:
                typeText(currentText, undoStack, redoStack);  // Memanggil fungsi untuk menambahkan teks baru
                break;
            case 2:
                performUndo(currentText, undoStack, redoStack);  // Memanggil fungsi untuk melakukan operasi undo
                break;
            case 3:
                performRedo(currentText, undoStack, redoStack);  // Memanggil fungsi untuk melakukan operasi redo
                break;
            case 4:
                checkEmptyUndo(undoStack);  // Memanggil fungsi untuk memeriksa status kosongnya undoStack
                break;
            case 5:
                checkEmptyRedo(redoStack);  // Memanggil fungsi untuk memeriksa status kosongnya redoStack
                break;
            case 6:
                cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                return 0;  // Keluar dari program dengan nilai 0 yang menunjukkan kelancaran program
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;  // Menampilkan pesan kesalahan untuk pilihan tidak valid
                break;
        }

        cout << "\nTekan Enter untuk melanjutkan...";  // Menampilkan pesan untuk melanjutkan setelah setiap operasi
        cin.get();  // Menunggu pengguna menekan Enter sebelum melanjutkan ke iterasi berikutnya dalam loop
    }

    return 0;  // Mengakhiri program dengan nilai 0 yang menunjukkan kelancaran program
}
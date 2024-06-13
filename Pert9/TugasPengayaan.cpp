#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<string> tumpukanUndo;
stack<string> tumpukanRedo;
string teksSaatIni;

void tambahkanTeks(const string &teks) {
    tumpukanUndo.push(teksSaatIni);
    teksSaatIni += teks;
    while (!tumpukanRedo.empty()) {
        tumpukanRedo.pop();
    }
}

void undo() {
    if (!tumpukanUndo.empty()) {
        tumpukanRedo.push(teksSaatIni);
        teksSaatIni = tumpukanUndo.top();
        tumpukanUndo.pop();
    } else {
        cout << "Tumpukan undo kosong.\n";
    }
}

void redo() {
    if (!tumpukanRedo.empty()) {
        tumpukanUndo.push(teksSaatIni);
        teksSaatIni = tumpukanRedo.top();
        tumpukanRedo.pop();
    } else {
        cout << "Tumpukan redo kosong.\n";
    }
}

bool tumpukanUndoKosong() {
    return tumpukanUndo.empty();
}

bool tumpukanRedoKosong() {
    return tumpukanRedo.empty();
}

void cetakTeksSaatIni() {
    cout << "\nTeks saat ini: " << teksSaatIni << endl;
}

void cetakMenu() {
    cout << "==================================\n";
    cout << "|              Menu              |\n";
    cout << "==================================\n";
    cout << "| 1. Ketik teks                  |\n";
    cout << "| 2. Undo                        |\n";
    cout << "| 3. Redo                        |\n";
    cout << "| 4. IsEmptyUndo                 |\n";
    cout << "| 5. IsEmptyRedo                 |\n";
    cout << "| 6. Keluar                      |\n";
    cout << "==================================\n";
    cout << " Masukkan pilihan Anda: ";
}

void cetakTumpukanUndo() {
    if (tumpukanUndoKosong()) {
        cout << "Tumpukan undo kosong.\n";
    } else {
        cout << "Isi tumpukan undo:\n";
        stack<string> temp = tumpukanUndo;
        while (!temp.empty()) {
            cout << "\"" << temp.top() << "\"\n";
            temp.pop();
        }
    }
}

void cetakTumpukanRedo() {
    if (tumpukanRedoKosong()) {
        cout << "Tumpukan redo kosong.\n";
    } else {
        cout << "Isi tumpukan redo:\n";
        stack<string> temp = tumpukanRedo;
        while (!temp.empty()) {
            cout << "\"" << temp.top() << "\"\n";
            temp.pop();
        }
    }
}

int main() {
    int pilihan;
    string teks;

    do {
        cetakTeksSaatIni();
        cetakMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan teks yang ingin ditambahkan: ";
                getline(cin, teks);
                tambahkanTeks(teks);
                cout << "\nTeks Berhasil Ditambahkan!! " << endl;
                cout << "Tekan Enter untuk melanjutkan..."; 
                cin.get();
                break;
            case 2:
                undo();
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            case 3:
                redo();
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            case 4:
                cetakTumpukanUndo();
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            case 5:
                cetakTumpukanRedo();
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            case 6:
                cout << "==============================================\n";
                cout << "| Terima Kasih Telah Menggunakan Program Ini |\n";
                cout << "==============================================\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 6);

    return 0;
}
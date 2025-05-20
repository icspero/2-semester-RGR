#define WIN32_LEAN_AND_MEAN
#include "CodeWord.h"
#include "MagicSquare.h"
#include "Hughes.h"
#include <cstdlib>
#include <windows.h>
#include <locale.h>

unsigned int simpleHash(const string& str) {
    unsigned int hash = 0;
    for (char c : str) {
        hash += static_cast<unsigned char>(c);
    }
    return hash;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    int hash = 996;
    string password;
    cout << "Введите пароль: ";
    cin >> password;

    while (true) {
        if (simpleHash(password) == hash) {
            cout << "URAAA" << endl;
            break;
        } else {
			cout << "Неверный пароль, попробуйте снова: ";
			cin >> password;
		}
    }

    system("cls");

    while (true) {
        int p;
        cout << "HAHAH: ";
        cin >> p;
        system("cls");
    }
}
#define WIN32_LEAN_AND_MEAN
#include "CodeWord.h"
#include "MagicSquare.h"
#include "Hughes.h"
#include "startMenu.h"
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
	setlocale(LC_ALL, "ru");
	// дл€ работы с русским €зыком в консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    int hash = 996;
    string password;
    cout << "¬ведите пароль: ";
    cin >> password;

    while (true) {
        if (simpleHash(password) == hash) {
            break;
        } else {
			cout << "Ќеверный пароль, попробуйте снова: ";
			cin >> password;
		}
    }

    system("cls");

	bool isTrue = 1;
	while (isTrue) {
		char method = mainMenu(); // получение команды пользовател€
		system("cls");

		if (method == '4') {
			isTrue = 0; 
			break; 
		}

		char action = encryptOrDecrypt();
		system("cls");

		string message = getMessage(action);
		system("cls");

		if (method == '1') {
			hughes(action, message);
		}
		else if (method == '2') {
			codeWord(action, message);
		}
        else if (method == '3') {
			magicSquare(action, message);
		}
	}
}
#include "startMenu.h"

char mainMenu() {
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
	cout << "Выберите действие:" << endl;
	cout << "1. Использовать метод шифрования 'Хьюза'" << endl;
	cout << "2. Использовать метод шифрования 'Кодовое слово'" << endl;
	cout << "3. Использовать метод шифрования 'Магический квадрат'" << endl;
	cout << "4. Выход из программы" << endl;
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

	int command;
	while (true) {
		command = _getch();
		if (command >= 49 && command <= 52) { // в случае получения команды заканчиваем работу
			break;
		}
	}

	char res = static_cast<char>(command);

	return res;
}

char encryptOrDecrypt (){
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
	cout << "Выберите действие:" << endl;
	cout << "1. Зашифровать" << endl;
	cout << "2. Расшифровать" << endl;
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

	int command;
	while (true) {
		command = _getch();
		if (command >= 49 && command <= 50) {
			break;
		}
	}

	return static_cast<char>(command);
}

string getMessage(char action) {
    string message;
    int command;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "Выберите способ ввода сообщения:" << endl;
    cout << "1. Ввести сообщение с клавиатуры" << endl;
    cout << "2. Взять сообщение из файла" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    while (true) {
        command = _getch();
        if (command == 49) {
            system("cls");

            cout << "Введите ваше сообщение: ";
            if (char(cin.peek()) == '\n') { //очищение буфера в вынужденных мерах
                cin.ignore();
            }
            
            while (true) {
                getline(cin, message);
                if (message.size() == 0) {
                    cout << "Сообщение не должно быть пустым. Попробуйте снова: ";
                }else {
                    return message;
                }
            }
        } else if (command == 50) {
            system("cls");

            string filename = (action == '1') ? "decryptMessage.txt" : "encryptMessage.txt";
            ifstream file(filename);

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    message += line;
                }
                file.close();

                if (message.empty()) {
                    cout << "Файл пуст, попробуйте снова" << endl;

                    system("pause");
                    system("cls");

                    return getMessage(action);
                }
                
                return message;
            }else {
                cout << "У вас нет файла с записанными значениями, попробуйте снова" << endl;

                system("pause");
                system("cls");

                return getMessage(action);
            }
        }
    }
}
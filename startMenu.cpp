#include "startMenu.h"

char mainMenu() {
	system("cls");
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

char encryptOrDecrypt () {
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
            if (char(cin.peek()) == '\n') { // очищение буфера в вынужденных мерах
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
            } else {
                cout << "У вас нет файла с записанными значениями, попробуйте снова" << endl;

                system("pause");
                system("cls");

                return getMessage(action);
            }
        }
    }
}

void recToFile(const string& message, char action) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "Хотите записать результат в файл?" << endl;
    cout << "1. Да, записать" << endl;
    cout << "2. Продолжить без записи" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    int command;
    while (true) {
        command = _getch();
        if (command == '1') { // клавиша '1'
            string filename = (action == '1') ? "encryptMessage.txt" : "decryptMessage.txt";

            ofstream file(filename, ios::trunc); // перезаписываем файл
            if (!file.is_open()) {
                cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
                return;
            }

            file << message;  // без лишнего пробела или \n
            file.close();
            cout << "Результат успешно записан в файл: " << filename << endl;
            break;
        }
        else if (command == '2') { // клавиша '2'
            break;
        }
    }
}

void recCodeWordToFile(const string& codeWord) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "Хотите сохранить кодовое слово в файл?" << endl;
    cout << "1. Да, сохранить" << endl;
    cout << "2. Продолжить без записи" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    char res;
    while (true) {
        int command = _getch();
        if (command == '1' || command == '2') {
            res = static_cast<char>(command);
            break;
        }
    }

    if (res == '1') {
        string filename = "codeWord.txt";
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
            return;
        }
        file << codeWord;
        file.close();
        cout << "Результат успешно записан в файл: " << filename << endl;
    }
}

void getCodeWord(char& method, string& codeWord) {
    int command;

    while (true) {
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
        cout << "Выберите способ ввода кодового слова:" << endl;
        cout << "1. Ввести кодовое слово с клавиатуры" << endl;
        cout << "2. Взять кодовое слово из файла" << endl;
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
        command = _getch();
        if (command == '1') {
            method = '1';
            system("cls");
            cout << "Введите кодовое слово: ";

            if (cin.peek() == '\n') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                getline(cin, codeWord);
                if (codeWord.empty()) {
                    cout << "Кодовое слово не должно быть пустым. Попробуйте снова: ";
                } else {
                    return;
                }
            }
        }
        else if (command == '2') {
            method = '2';
            system("cls");

            string filename = "codeWord.txt"; // файл с кодовым словом
            ifstream file(filename);
            if (file.is_open()) {
                getline(file, codeWord);
                file.close();

                if (codeWord.empty()) {
                    cout << "Файл пуст, попробуйте снова" << endl;
                    system("pause");
                    system("cls");
                    continue; // повторим выбор
                }
                return;
            } else {
                cout << "Файл с кодовым словом не найден, попробуйте снова" << endl;
                system("pause");
                system("cls");
                continue; // повторим выбор
            }
        }
    }
}

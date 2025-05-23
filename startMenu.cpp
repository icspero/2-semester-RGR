#include "startMenu.h"

char mainMenu() {
	system("cls");
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
	cout << "�������� ��������:" << endl;
	cout << "1. ������������ ����� ���������� '�����'" << endl;
	cout << "2. ������������ ����� ���������� '������� �����'" << endl;
	cout << "3. ������������ ����� ���������� '���������� �������'" << endl;
	cout << "4. ����� �� ���������" << endl;
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

	int command;
	while (true) {
		command = _getch();
		if (command >= 49 && command <= 52) { // � ������ ��������� ������� ����������� ������
			break;
		}
	}

	char res = static_cast<char>(command);

	return res;
}

char encryptOrDecrypt () {
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
	cout << "�������� ��������:" << endl;
	cout << "1. �����������" << endl;
	cout << "2. ������������" << endl;
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
    cout << "�������� ������ ����� ���������:" << endl;
    cout << "1. ������ ��������� � ����������" << endl;
    cout << "2. ����� ��������� �� �����" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    while (true) {
        command = _getch();
        if (command == 49) {
            system("cls");

            cout << "������� ���� ���������: ";
            if (char(cin.peek()) == '\n') { // �������� ������ � ����������� �����
                cin.ignore();
            }
            
            while (true) {
                getline(cin, message);
                if (message.size() == 0) {
                    cout << "��������� �� ������ ���� ������. ���������� �����: ";
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
                    cout << "���� ����, ���������� �����" << endl;

                    system("pause");
                    system("cls");

                    return getMessage(action);
                }
                
                return message;
            } else {
                cout << "� ��� ��� ����� � ����������� ����������, ���������� �����" << endl;

                system("pause");
                system("cls");

                return getMessage(action);
            }
        }
    }
}

void recToFile(const string& message, char action) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "������ �������� ��������� � ����?" << endl;
    cout << "1. ��, ��������" << endl;
    cout << "2. ���������� ��� ������" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

    int command;
    while (true) {
        command = _getch();
        if (command == '1') { // ������� '1'
            string filename = (action == '1') ? "encryptMessage.txt" : "decryptMessage.txt";

            ofstream file(filename, ios::trunc); // �������������� ����
            if (!file.is_open()) {
                cerr << "������: �� ������� ������� ���� ��� ������!" << endl;
                return;
            }

            file << message;  // ��� ������� ������� ��� \n
            file.close();
            cout << "��������� ������� ������� � ����: " << filename << endl;
            break;
        }
        else if (command == '2') { // ������� '2'
            break;
        }
    }
}

void recCodeWordToFile(const string& codeWord) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "������ ��������� ������� ����� � ����?" << endl;
    cout << "1. ��, ���������" << endl;
    cout << "2. ���������� ��� ������" << endl;
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
            cerr << "������: �� ������� ������� ���� ��� ������!" << endl;
            return;
        }
        file << codeWord;
        file.close();
        cout << "��������� ������� ������� � ����: " << filename << endl;
    }
}

void getCodeWord(char& method, string& codeWord) {
    int command;

    while (true) {
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
        cout << "�������� ������ ����� �������� �����:" << endl;
        cout << "1. ������ ������� ����� � ����������" << endl;
        cout << "2. ����� ������� ����� �� �����" << endl;
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
        command = _getch();
        if (command == '1') {
            method = '1';
            system("cls");
            cout << "������� ������� �����: ";

            if (cin.peek() == '\n') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                getline(cin, codeWord);
                if (codeWord.empty()) {
                    cout << "������� ����� �� ������ ���� ������. ���������� �����: ";
                } else {
                    return;
                }
            }
        }
        else if (command == '2') {
            method = '2';
            system("cls");

            string filename = "codeWord.txt"; // ���� � ������� ������
            ifstream file(filename);
            if (file.is_open()) {
                getline(file, codeWord);
                file.close();

                if (codeWord.empty()) {
                    cout << "���� ����, ���������� �����" << endl;
                    system("pause");
                    system("cls");
                    continue; // �������� �����
                }
                return;
            } else {
                cout << "���� � ������� ������ �� ������, ���������� �����" << endl;
                system("pause");
                system("cls");
                continue; // �������� �����
            }
        }
    }
}

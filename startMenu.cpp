#include "startMenu.h"

char mainMenu() {
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

char encryptOrDecrypt (){
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
            if (char(cin.peek()) == '\n') { //�������� ������ � ����������� �����
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
            }else {
                cout << "� ��� ��� ����� � ����������� ����������, ���������� �����" << endl;

                system("pause");
                system("cls");

                return getMessage(action);
            }
        }
    }
}
#include "Hughes.h"
#include "startMenu.h"

int64_t inputValue(int64_t option) {
    string userInput;
    while (true) {
        getline(cin, userInput);

        if (userInput.size() == 0) {
            cout << "������������ ����, ���������� �����: ";
            continue;
        }

        bool isTrue = true;
        for (char symbol : userInput) {
            if (!isdigit(symbol)) {
                isTrue = false;
                break;
            }
        }

        if (isTrue) {
            int64_t value = stoi(userInput);
            if (option == 0) { // ��� �������
                if (value != 0) {
                    return value;
                }
                else {
                    cout << "������������ ����, ���������� �����: ";
                    continue;
                }
            }
            
            if (primeNum(value) == false) { // ��� �������� ��������� ������� � ������
                cout << "������������ ���� - ����� ������ ���� �������, ���������� �����: ";
                continue;
            }

            if (option == 1) {
                return value;
            }

            if (value == option) {
                cout << "������ �� ������ ���� ����� ��������� ������� (����� �� �������: " << option << "). ���������� �����: ";
                continue;
            } else {
                return value;
            }
        } else {
            cout << "������������ ����, ���������� �����: ";
        }
    }
}

int64_t NOD(int64_t a, int64_t p) {
    while (p != 0) {
        int64_t r = a % p;
        a = p;
        p = r;
    }

    return a;
}

int64_t algoEuclid(int64_t a, int64_t m) {
    int64_t x1 = 1, x2 = 0;

    while (m != 0) {
        int64_t q = a / m;
        int64_t r = a % m;

        int64_t tempx = x1;
        x1 = x2;
        x2 = tempx - q * x2;

        a = m;
        m = r;
    }

    return x1;
}

int64_t powmod(int64_t a, int64_t x, int64_t p) {
    int64_t res = 1;
    a = a % p;

    while (x > 0) {
        if (x % 2 == 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x = x / 2;
    }

    return res;
}

bool primeNum(int64_t modal) {
    if (modal <= 1) return false; // ������������� �����, 0 � 1 � �� �������

    if (modal <= 3) return true; // 2 � 3 � ������� �����

    if (modal % 2 == 0 || modal % 3 == 0) return false; // �������� �� ��������� �� 2 � 3
        
    for (int64_t i = 5; i * i <= modal; i += 6) {
        if (modal % i == 0 || modal % (i + 2) == 0) return false;
    }
    return true;
}

string encrypt(int64_t aliceKey, string message) {
    vector<int64_t> result;
    for (size_t i = 0; i < message.size(); i++) {
        unsigned char simbol = message[i];
        result.push_back(static_cast<int64_t>(simbol) * aliceKey);
    }

    ostringstream oss;
    for (const auto& num : result) {
        oss << num << " ";
    }

    return oss.str();
}

string decrypt(int64_t bobeKey, vector<int64_t> mesToDecrypt) {
    string result;
    for (size_t i = 0; i < mesToDecrypt.size(); i++) {
        int64_t simbol = mesToDecrypt[i];
        unsigned char decrSim = (simbol / bobeKey);
        result += decrSim;
    }
    return result;
}

void recToFile(const string& message, char action) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "������ �������� ��������� � ����?" << endl;
    cout << "1. ��, �������� ��������� � ����" << endl;
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

void hughes(char action, const string& message) {
    random_device rd;
    mt19937 gen(rd());
	
    if (action == '1') {
        cout << "������� ������� ����� - ��������� ������� (��������� ���): ";
        int64_t num = inputValue(1); // �������� �������� ���������� ��� ���� �������� (��� ��� ��������� �������)
        system("cls");

        cout << "������� ������� ����� - ������, �� ������ ��������� ������� (��������� ���): ";
        int64_t modal = inputValue(num); // �������� ������
        system("cls");

        cout << "������� ����������� ����� - ������� (��������� ���): ";
        int64_t degreeAlice = inputValue(0);

        int64_t aliceKey = powmod(num, degreeAlice, modal);

        system("cls");

        string result = encrypt(aliceKey, message);
        cout << "���� ������������� ���������: " << result << endl;

        recToFile(result, action);

        system("cls");
    } 
    else {
        cout << "������� ������� ����� - ��������� �������: ";
        int64_t num = inputValue(1); //�������� �������� ���������� ��� ���� �������� (��� ��� ��������� �������)
        system("cls");

        cout << "������� ������� ����� - ������ (�� ������ ��������� �������): ";
        int64_t modal = inputValue(num); //�������� ������
        system("cls");

        cout << "������� ����������� �����-�������: ";
        int64_t degreeAlice = inputValue(0);

        uniform_int_distribution<int64_t> dist(2, 999);
        int64_t degBob = dist(gen);

        int64_t bobNumfirst = powmod(num, degBob, modal); // ���������� �������������� ����� ����
        int64_t aliceNum = powmod(bobNumfirst, degreeAlice, modal); // ���������� �������������� ����� �����
        int64_t bobNumsecond = algoEuclid(degBob, modal - 1); // ���������� ������� �������������� ����� ���� �� ��������� �������
        int64_t bobeKey = powmod(aliceNum, bobNumsecond, modal); // ��������� ��������� ����� ����

        system("cls");

        vector<int64_t> mesToDecrypt;
        istringstream iss(message); // ��������� ������ � ������ 
        int64_t messegeElem;
        while (iss >> messegeElem) {
            mesToDecrypt.push_back(messegeElem);
        }

        string result = decrypt(bobeKey, mesToDecrypt);
        cout << "���� �������������� ���������: " << result << endl;

        recToFile(result, action);

        system("cls");
    }
}
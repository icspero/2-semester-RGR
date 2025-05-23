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
    if (NOD(a, m) != 1) {
        return 0;
    }
    
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

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
    } 
    else {
        cout << "������� ������� ����� - ��������� �������: ";
        int64_t num = inputValue(1); //�������� �������� ���������� ��� ���� �������� (��� ��� ��������� �������)
        system("cls");

        cout << "������� ������� ����� - ������, �� ������ ��������� �������: ";
        int64_t modal = inputValue(num); //�������� ������
        system("cls");

        cout << "������� ����������� �����-�������: ";
        int64_t degreeAlice = inputValue(0);

        uniform_int_distribution<int64_t> dist(2, modal - 2);
        
        int64_t degBob = dist(gen);
        while (NOD(degBob, modal - 1) != 1) {
            degBob = dist(gen);
        }

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
    }
}
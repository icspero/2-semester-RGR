#include "Hughes.h"
#include "startMenu.h"

int64_t inputValue(int64_t option) {
    string userInput;
    while (true) {
        getline(cin, userInput);

        if (userInput.size() == 0) {
            cout << "Некорректный ввод, попробуйте снова: ";
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
            if (option == 0) { // для степени
                if (value != 0) {
                    return value;
                }
                else {
                    cout << "Некорректный ввод, попробуйте снова: ";
                    continue;
                }
            }
            
            if (primeNum(value) == false) { // для проверки основания степени и модуля
                cout << "Некорректный ввод - число должно быть простым, попробуйте снова: ";
                continue;
            }

            if (option == 1) {
                return value;
            }

            if (value == option) {
                cout << "Модуль не должен быть равен основанию степени (ранее вы вводили: " << option << "). Попробуйте снова: ";
                continue;
            } else {
                return value;
            }
        } else {
            cout << "Некорректный ввод, попробуйте снова: ";
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
    if (modal <= 1) return false; // Отрицательные числа, 0 и 1 — не простые

    if (modal <= 3) return true; // 2 и 3 — простые числа

    if (modal % 2 == 0 || modal % 3 == 0) return false; // Проверка на делимость на 2 и 3
        
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
    cout << "Хотите записать результат в файл?" << endl;
    cout << "1. Да, записать результат в файл" << endl;
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

void hughes(char action, const string& message) {
    random_device rd;
    mt19937 gen(rd());
	
    if (action == '1') {
        cout << "Введите простое число - основание степени (запомните его): ";
        int64_t num = inputValue(1); // вводимый параметр обозначает для чего проверка (тут для основания степени)
        system("cls");

        cout << "Введите простое число - модуль, не равный основанию степени (запомните его): ";
        int64_t modal = inputValue(num); // проверка модуля
        system("cls");

        cout << "Введите натуральное число - степень (запомните его): ";
        int64_t degreeAlice = inputValue(0);

        int64_t aliceKey = powmod(num, degreeAlice, modal);

        system("cls");

        string result = encrypt(aliceKey, message);
        cout << "Ваше зашифрованное сообщение: " << result << endl;

        recToFile(result, action);

        system("cls");
    } 
    else {
        cout << "Введите простое число - основание степени: ";
        int64_t num = inputValue(1); //вводимый параметр обозначает для чего проверка (тут для основания степени)
        system("cls");

        cout << "Введите простое число - модуль (не равный основанию степени): ";
        int64_t modal = inputValue(num); //проверка модуля
        system("cls");

        cout << "Введите натуральное число-степень: ";
        int64_t degreeAlice = inputValue(0);

        uniform_int_distribution<int64_t> dist(2, 999);
        int64_t degBob = dist(gen);

        int64_t bobNumfirst = powmod(num, degBob, modal); // вычисление промежуточного числа Боба
        int64_t aliceNum = powmod(bobNumfirst, degreeAlice, modal); // вычисление промежуточного числа Алисы
        int64_t bobNumsecond = algoEuclid(degBob, modal - 1); // вычисление второго промежуточного числа Боба по алгоритму Евклида
        int64_t bobeKey = powmod(aliceNum, bobNumsecond, modal); // вычиление закрытого ключа Боба

        system("cls");

        vector<int64_t> mesToDecrypt;
        istringstream iss(message); // переводим строку в вектор 
        int64_t messegeElem;
        while (iss >> messegeElem) {
            mesToDecrypt.push_back(messegeElem);
        }

        string result = decrypt(bobeKey, mesToDecrypt);
        cout << "Ваше расшифрованное сообщение: " << result << endl;

        recToFile(result, action);

        system("cls");
    }
}
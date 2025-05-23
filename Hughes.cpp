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
    if (modal <= 1) return false; // отрицательные числа, 0 и 1 — не простые

    if (modal <= 3) return true; // 2 и 3 — простые числа

    if (modal % 2 == 0 || modal % 3 == 0) return false; // проверка на делимость на 2 и 3
        
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
    } 
    else {
        cout << "Введите простое число - основание степени: ";
        int64_t num = inputValue(1); //вводимый параметр обозначает для чего проверка (тут для основания степени)
        system("cls");

        cout << "Введите простое число - модуль, не равный основанию степени: ";
        int64_t modal = inputValue(num); //проверка модуля
        system("cls");

        cout << "Введите натуральное число-степень: ";
        int64_t degreeAlice = inputValue(0);

        uniform_int_distribution<int64_t> dist(2, modal - 2);
        
        int64_t degBob = dist(gen);
        while (NOD(degBob, modal - 1) != 1) {
            degBob = dist(gen);
        }

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
    }
}
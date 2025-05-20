#include "Hughes.h"

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












/*
int main() {
    string message;
    while (true) {
        random_device rd;
        mt19937 gen(rd());
        
        int64_t g, m, x;
        cout << "Введите g, x, m: ";
        cin >> g >> m >> x;

        cout << "Выберите опцию:\n";
        cout << "1. Зашифровать сообщение.\n";
        cout << "2. Расшифровать сообщение.\n";
        cout << "Option: ";
        int op;
        cin >> op;

        if (op == 1) {
            int64_t aliceKey = powmod(g, x, m);

            cout << "Введите сообщение: ";
            cin >> message;
            message = encrypt(aliceKey, message);

            cout << "Ваше зашифрованное сообщение: " << message << endl; 
        }
        else {
            uniform_int_distribution<int64_t> dist(2, 999);
            int64_t degBob = dist(gen);

            while (NOD(degBob, m - 1) != 1) {
                degBob = dist(gen);
            }

            int64_t bobNumFirst = powmod(g, degBob, m);
            int64_t aliceNum = powmod(bobNumFirst, x, m);
            int64_t bobNumSecond = algoEuclid(degBob, m - 1);
            int64_t bobKey = powmod(aliceNum, bobNumSecond, m);

            vector<int64_t> mesToDecrypt;
            istringstream iss(message); // переводим строку в вектор 
            int64_t messegeElem;
            while (iss >> messegeElem) {
                mesToDecrypt.push_back(messegeElem);
            }

            string message = decrypt(bobKey, mesToDecrypt);
            cout << "Ваше расшифрованное сообщение: " << message << endl;
        }
    }
}

*/
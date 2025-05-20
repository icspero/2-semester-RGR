#include "MagicSquare.h"

// Функция для определения порядка квадрата
int defOfOrder(string& mes) { 
    int size_m = mes.size();
    double n = sqrt(size_m);
    int res = static_cast<int>(ceil(n));

    if (res % 2 == 0) { // делаем квадрат нечётным
        res += 1;
    }

    return res;
}

vector<vector<int>> createSquare(vector<vector<int>>& square, int& n) {
    for (int i = 0; i < n; i++) {
        vector<int> res;
        for (int j = 0; j < n; j++) {
            res.push_back(0);
        }
        square.push_back(res);
    }

    return square;
}

vector<vector<int>> filligTheSquare(vector<vector<int>>& square, int& n) {
    int i = 0, j = n / 2;

    for (int k = 1; k <= pow(n, 2); k++) {
        square[i][j] = k;
        int next_i = (i - 1 + n) % n;
        int next_j = (j + 1) % n;
        if (square[next_i][next_j] != 0) {
            i = (i + 1) % n;
        } else {
            i = next_i;
            j = next_j;
        }
    }

    return square;
}

void display(vector<vector<int>>& square) {
    for (auto i : square) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

string encryptMessage(const vector<vector<int>>& square, string& message, int n) {
    // Дополняем сообщение пробелами до длины n^2
    int blockSize = n * n;
    if ((int)message.length() < blockSize) {
        message.append(blockSize - message.length(), ' ');
    }

    // Создаем матрицу строк для зашифрованного сообщения
    vector<vector<string>> encVec(n, vector<string>(n, " "));

    // Заполняем encVec в соответствии с квадратом
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = square[i][j];  // позиция буквы в сообщении (от 1 до n^2)
            encVec[i][j] = string(1, message[pos - 1]);
        }
    }

    // Формируем итоговую строку из encVec
    string cipher = "";
    for (const auto& row : encVec) {
        for (const auto& ch : row) {
            cipher += ch;
        }
    }

    return cipher;
}

string decryptMessage(const vector<vector<int>>& square, string& cipher, int n) {
    vector<vector<char>> tempMatrix(n, vector<char>(n));
    int index = 0;

    // Заполняем матрицу шифротекста
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tempMatrix[i][j] = cipher[index++];
        }
    }

    // Восстанавливаем исходное сообщение по порядку из магического квадрата
    vector<char> message(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = square[i][j]; // позиция от 1 до n^2
            message[pos - 1] = tempMatrix[i][j];
        }
    }

    string result(message.begin(), message.end());

    // Находим "##" и обрезаем всё после него
    size_t endPos = result.find("##");
    if (endPos != string::npos) {
        result = result.substr(0, endPos);
    }

    return result;
}


/*
int main() {
    string cipher = "";
    string message = "Hello World!, Fuck you bitch, i am stuck, Your Mom is good girl?";
    message += "##";
    int n = defOfOrder(message);

    vector<vector<int>> sq;
    sq = createSquare(sq, n);
    sq = filligTheSquare(sq, n);
    cipher = encryptMessage(sq, message, n);
    
    cout << cipher << endl;

    string result = decryptMessage(sq, cipher, n);
    cout << result << endl;
}

*/
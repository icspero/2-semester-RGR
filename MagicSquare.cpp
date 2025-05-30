#include "MagicSquare.h"
#include "startMenu.h"

// Функция для определения порядка квадрата
int defOfOrder(string& mes) { 
    int size_m = mes.size();
    double n = sqrt(size_m);
    int res = static_cast<int>(ceil(n)); // ceil округляет до ближайшего целого

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

void printMatrix(const vector<vector<int>>& matrix) {
    // найти максимальную ширину элемента
    int maxWidth = 0;
    for (const auto& row : matrix) {
        for (int elem : row) {
            int len = to_string(elem).size();
            if (len > maxWidth) maxWidth = len;
        }
    }

    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << setw(maxWidth + 1) << elem; // +1 для пробела между колонками
        }
        cout << endl;
    }
}

string encryptMessage(const vector<vector<int>>& square, string& message, int n) {
    // дополняем сообщение пробелами до длины n^2
    int blockSize = n * n;
    if ((int)message.length() < blockSize) {
        message.append(blockSize - message.length(), ' ');
    }

    // создаем матрицу строк для зашифрованного сообщения
    vector<vector<string>> encVec(n, vector<string>(n, " "));

     // заполняем encVec в соответствии с квадратом
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = square[i][j];  // позиция буквы в сообщении (от 1 до n^2)
            encVec[i][j] = string(1, message[pos - 1]);
        }
    }

    // формируем итоговую строку из encVec
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

    // заполняем матрицу шифротекста
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tempMatrix[i][j] = cipher[index++];
        }
    }

    // восстанавливаем исходное сообщение по порядку из магического квадрата
    vector<char> message(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = square[i][j];
            message[pos - 1] = tempMatrix[i][j];
        }
    }

    string result(message.begin(), message.end());

    // находим "##" и обрезаем всё после него
    size_t endPos = result.find("##");
    if (endPos != string::npos) {
        result = result.substr(0, endPos);
    }

    return result;
}

void magicSquare(char action, string message) {
    if (action == '1') {
        string cipher = "";
        int n = defOfOrder(message);
        message += "##";
        
        vector<vector<int>> sq, fill;
        sq = createSquare(sq, n);
        fill = filligTheSquare(sq, n);
        cipher = encryptMessage(fill, message, n);
        cout << "Ваше зашифрованное сообщение: " << cipher << endl;
        cout << "Построенный магический квадрат:" << endl;
        printMatrix(sq);

        recToFile(cipher, action);
        system("cls");
    }
    else {
        int n = defOfOrder(message);
        vector<vector<int>> sq, fill;
        sq = createSquare(sq, n);
        fill = filligTheSquare(sq, n);
        string result = decryptMessage(fill, message, n); 
        cout << "Ваше расшифрованное сообщение: " << result << endl;

        recToFile(result, action);
        system("cls");
    }
}
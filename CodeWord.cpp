#include "CodeWord.h"
#include "startMenu.h"

bool isRus(char ch) {
    unsigned char uch = static_cast<unsigned char>(ch); // �������� � ���� unsigned char, ����� ��������� �������� � ����� �������
    // ��������� � - �: 0xC0 - 0xDF
    // �������� � - �: 0xE0 - 0xFF
    // �: 0xA8, �: 0xB8
    return (uch >= 0xC0 && uch <= 0xDF) || 
           (uch >= 0xE0 && uch <= 0xFF) || 
           uch == 0xA8 || uch == 0xB8;
}

// ��������� ������� ����� � �������
string addCodeWord(string codeWord, string alphabet) {
    string newWord = "";
    
    for (const char ch : codeWord) {
        newWord += ch;
    }
    for (const char ch : alphabet) {
        newWord += ch;
    }

    return newWord;
}

// ������� ��������� ��������
string remDup(string word) {
    string newWord = "";

    for (int i = 0; i < word.size(); i++) {
        if (newWord.find(word[i]) != string::npos) { // ���� ����� ��� ����, �� ����������
            continue;
        }
        if (!isalpha(word[i]) && !isRus(word[i])) { // ���� �� ����� � �� ������� �����, �� ����������
            continue;
        }
        newWord += word[i];
    }

    return newWord;
}

string encryptedMess(const string& mess, const string& alpha, const string& newAlpha) {
    string encMess = "";

    for (char ch : mess) {
        int i;
        if (!isalpha(ch) && !isRus(ch)) {
            encMess += ch;
            continue;
        }
        else {
            for (i = 0; i < alpha.size(); i++) {
                if (alpha[i] == ch) {
                    break;
                }
            }
            ch = newAlpha[i];
            encMess += ch;
        }
    }
    
    return encMess;
}

string decryptedMess(const string& encMess, const string& alpha, const string& newAlpha) {
    string decMess = "";

    for (char ch : encMess) {
        int i;
        if (!isalpha(ch) && !isRus(ch)) {
            decMess += ch;
            continue;
        }
        else {
            for (i = 0; i < newAlpha.size(); i++) {
                if (newAlpha[i] == ch) {
                    break;
                }
            }
            ch = alpha[i];
            decMess += ch;
        }
    }
    
    return decMess;
}

void codeWord(char action, const string& message) {
    string alphabet;
    for (char c = -64; c <= -59; ++c) alphabet += c; // ������� ���������: ���, �(0xC0 = -64) to �(0xC5 = -59)
    alphabet += char(-88); // � (0xA8 = -88)
    for (char c = -58; c <= -33; ++c) alphabet += c; // ������� ���������: Ɩ�
    for (char c = -32; c <= -27; ++c) alphabet += c; // ������� ��������: ���, �(0xE0 = -32) to �(0xE5 = -27)
    alphabet += char(-72); // � (0xB8 = -72)
    for (char c = -26; c <= -1; ++c) alphabet += c; // ������� ��������: ��
    for (char c = 'A'; c <= 'Z'; ++c) alphabet += c; // ���������� ���������
    for (char c = 'a'; c <= 'z'; ++c) alphabet += c; // ���������� ��������

    if (action == '1') {
        char method;
        string codeWord;
        getCodeWord(method, codeWord);

        system("cls"); 
        if (method == '1') {
            recCodeWordToFile(codeWord);
        }
        system("cls");

        codeWord = remDup(codeWord);
        string newAlphabet = addCodeWord(codeWord, alphabet);
        newAlphabet = remDup(newAlphabet);

        string encMess = encryptedMess(message, alphabet, newAlphabet);

        cout << "���� ������������� ���������: " << encMess << endl;

        recToFile(encMess, action);

        system("cls");
    } 
    else {
        char method;
        string codeWord;
        getCodeWord(method, codeWord);

        system("cls"); 
        if (method == '1') {
            recCodeWordToFile(codeWord);
        }
        system("cls");

        codeWord = remDup(codeWord);
        string newAlphabet = addCodeWord(codeWord, alphabet);
        newAlphabet = remDup(newAlphabet);

        string decMess = decryptedMess(message, alphabet, newAlphabet);

        cout << "���� �������������� ���������: " << decMess << endl;

        recToFile(decMess, action);

        system("cls");
    }
}
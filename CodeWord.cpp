#include "CodeWord.h"

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

string remDup(string word) {
    string newWord = "";

    for (int i = 0; i < word.size(); i++) {
        if (newWord.find(word[i]) != string::npos) {
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
        if (!isalpha(ch)) {
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
        if (!isalpha(ch)) {
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




































/*
int main() {
    string alphabet = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";

    string codeWord = "xWwVvoO";

    codeWord = remDup(codeWord);

    string newAlphabet = addCodeWord(codeWord, alphabet);

    newAlphabet = remDup(newAlphabet);

    string message = "Hello World!";

    cout << message << endl;

    string encMess = encryptedMess(message, alphabet, newAlphabet);
    cout << encMess << endl;

    string decMess = decryptedMess(encMess, alphabet, newAlphabet);
    cout << decMess << endl;
}
*/
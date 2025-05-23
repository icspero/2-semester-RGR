#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <locale>

using namespace std;

string addCodeWord(string codeWord, string alphabet);
string remDup(string word);
string encryptedMess(const string& mess, const string& alpha, const string& newAlpha);
string decryptedMess(const string& encMess, const string& alpha, const string& newAlpha);
void codeWord(char action, const string& message);
bool isRus(char ch);
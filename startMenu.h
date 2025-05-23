#pragma once

#include <iostream>
#include <cstdlib>
#define byte win_byte
#include <windows.h>
#undef byte
#include <locale.h>
#include <conio.h>
#include <fstream>
#include <string>
#ifdef max
#undef max
#endif
#include <limits>

using namespace std;

char mainMenu();
char encryptOrDecrypt();
string getMessage(char action);
void recToFile(const string& message, char action);
void recCodeWordToFile(const string& codeWord);
void getCodeWord(char& method, string& codeWord);
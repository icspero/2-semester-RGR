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

using namespace std;

char mainMenu();
char encryptOrDecrypt();
string getMessage(char action);
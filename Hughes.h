#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdint>
#include <random>
#include <string>
using namespace std;

int64_t NOD(int64_t a, int64_t p);
int64_t algoEuclid(int64_t a, int64_t m);
int64_t powmod(int64_t a, int64_t x, int64_t p);
string encrypt(int64_t aliceKey, string message);
string decrypt(int64_t bobeKey, vector<int64_t> mesToDecrypt);
int64_t inputValue(int64_t option);
bool primeNum(int64_t modal);
void recToFile(const string& message, char action);
void hughes(char action, const string& message);
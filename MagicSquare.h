#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>
#include <iomanip>

using namespace std;

int defOfOrder(string& mes);
vector<vector<int>> createSquare(vector<vector<int>>& square, int& n);
vector<vector<int>> filligTheSquare(vector<vector<int>>& square, int& n);
string encryptMessage(const vector<vector<int>>& square, string& message, int n);
string decryptMessage(const vector<vector<int>>& square, string& cipher, int n);
void magicSquare(char action, string message);
void printMatrix(const vector<vector<int>>& matrix);
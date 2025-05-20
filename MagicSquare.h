#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>

using namespace std;

int defOfOrder(string& mes);
vector<vector<int>> createSquare(vector<vector<int>>& square, int& n);
vector<vector<int>> filligTheSquare(vector<vector<int>>& square, int& n);
void display(vector<vector<int>>& square);
string encryptMessage(const vector<vector<int>>& square, string& message, int n);
string decryptMessage(const vector<vector<int>>& square, string& cipher, int n);
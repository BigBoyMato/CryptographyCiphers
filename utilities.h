#pragma once

#include <vector>
#include <string>

using namespace std;

const int ascii_size = 256;
const int alphabet_size = 26;
const char dummy_symbol = 'z';

int CalcDeterminant(vector<vector<int>> Matrix);
int getDeterminant(std::vector<std::vector<int>> vect);
int getIndex(vector<char> v, char C);
vector<vector<int>> inverseVec33(vector<vector<int>> J, int dim);
vector<vector<int>> getInverse(vector<vector<int>>& A);
vector<vector<int>> EnterMatrix();
vector<vector<int>> MultiplyMatrix(vector<vector<int>>& a, vector<vector<int>>& b);
vector<string> SplitIntoWords(const string& text);
vector<string> Input();
void PrintResult(vector<string> encrypted_words);

#pragma once
#include "utilities.h"

#include <vector>
#include <string>

using namespace std;

// ---------- ENCRYPTION ---------- //

vector<string> EncryptShiftCipher(vector<string> words_to_encrypt);
vector<string> EncryptAffineCipher(vector<string> words_to_encrypt);
vector<string> EncryptRecurrentAffineCipher(vector<string> words_to_encrypt);
vector<string> EncryptHillsCipher(vector<string> words_to_encrypt);
vector<string> EncryptRecurrentHillsCipher(vector<string> words_to_encrypt);

// ---------- DECRYPTION ---------- //

vector<string> DecryptShiftCipher(vector<string> words_to_decrypt);
vector<string> DecryptAffineCipher(vector<string> words_to_decrypt);
vector<string> DecryptRecurrentAffineCipher(vector<string> words_to_decrypt);
vector<string> DecryptHillsCipher(vector<string> words_to_decrypt);
vector<string> DecryptRecurrentHillsCipher(vector<string> words_to_decrypt);

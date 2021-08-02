#include "menu.h"

#include <iostream>

using namespace std;

// FULL ASCII 256 ciphers
void MenuFunc1(vector<string> text_to_use){
	bool run = true;
	while (run == true){
		cout << "Choose from: "s << endl;
		cout << "1. ENCRYPTION"s << endl;
		cout << "2. DECRYPTION"s << endl;
		cout << "3. QUIT"s << endl;
		cout << "*enter 1/2/3..."s << endl;
		int input_num_0;
		cin >> input_num_0;
		if (input_num_0 == 1){
			cout << "Choose an ENCRYPTION method: "s << endl;
			cout << "1. Substitution cipher ENCRYPTION"s << endl;
			cout << "2. Affine cipher ENCRYPTION"s << endl;
			cout << "3. Recurrent Affine cipher ENCRYPTION"s << endl;
			cout << "*enter 1/2/3..."s << endl;
			int input_num_1;
			cin >> input_num_1;
			if (input_num_1 == 1){
				auto result = EncryptShiftCipher(text_to_use);
				cout << "Substitution cipher ENCRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 2){
				auto result = EncryptAffineCipher(text_to_use);
				cout << "Affine cipher ENCRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 3){
				auto result = EncryptRecurrentAffineCipher(text_to_use);
				cout << "Recurrent Affine cipher ENCRYPTION results: "s;
				PrintResult(result);
			}
		}else if (input_num_0 == 2){
			cout << "Choose a DECRYPTION method: "s << endl;
			cout << "1. Substitution cipher DECRYPTION"s << endl;
			cout << "2. Affine cipher DECRYPTION"s << endl;
			cout << "3. Recurrent Affine cipher DECRYPTION"s << endl;
			cout << "*enter 1/2/3..."s << endl;
			int input_num_1;
			cin >> input_num_1;
			if (input_num_1 == 1){
				auto result = DecryptShiftCipher(text_to_use);
				cout << "Substitution cipher DECRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 2){
				auto result = DecryptAffineCipher(text_to_use);
				cout << "Affine cipher DECRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 3){
				auto result = DecryptRecurrentAffineCipher(text_to_use);
				cout << "Recurrent Affine cipher DECRYPTION results: "s;
				PrintResult(result);
			}
		}else if (input_num_0 == 3){
			run = false;
		}
	}
}

// ONLY ENG ALPHABET CIPHERS
void MenuFunc2(vector<string> text_to_use){
	bool run = true;
	while (run == true){
		cout << "Choose from: "s << endl;
		cout << "1. ENCRYPTION"s << endl;
		cout << "2. DECRYPTION"s << endl;
		cout << "3. QUIT"s << endl;
		cout << "*enter 1/2/3..."s << endl;
		int input_num_0;
		cin >> input_num_0;
		if (input_num_0 == 1){
			cout << "Choose an ENCRYPTION method: "s << endl;
			cout << "1. Hill's cipher ENCRYPTION"s << endl;
			cout << "2. Hill's reccurent cipher ENCRYPTION"s << endl;
			cout << "*enter 1/2..."s << endl;
			int input_num_1;
			cin >> input_num_1;
			if (input_num_1 == 1){
				auto result = EncryptHillsCipher(text_to_use);
				cout << " Hill's cipher ENCRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 2){
				auto result = EncryptRecurrentHillsCipher(text_to_use);
				cout << " Hill's reccurent cipher ENCRYPTION results: "s;
				PrintResult(result);
			}
		}else if (input_num_0 == 2){
			cout << "Choose a DECRYPTION method: "s << endl;
			cout << "1. Hill's cipher DECRYPTION"s << endl;
			cout << "2. Hill's reccurent cipher DECRYPTION"s << endl;
			cout << "*enter 1/2..."s << endl;
			int input_num_1;
			cin >> input_num_1;
			if (input_num_1 == 1){
				auto result = DecryptHillsCipher(text_to_use);
				cout << " Hill's cipher DECRYPTION results: "s;
				PrintResult(result);
			}else if(input_num_1 == 2){
				auto result = DecryptRecurrentHillsCipher(text_to_use);
				cout << " Hill's reccurent cipher DECRYPTION results: "s;
				PrintResult(result);
			}
		}else if (input_num_0 == 3){
			run = false;
		}
	}
}

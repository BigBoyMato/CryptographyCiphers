#include "ciphers.h"

#include <iostream>
#include <math.h>
#include <algorithm>

// ---------- ---------- ---------- //
// ---------- ENCRYPTION ---------- //
// ---------- ---------- ---------- //

vector<char> alphabet = {'a', 'b', 'c', 'd', 'e',
						'f', 'g', 'h', 'i', 'g',
						'k', 'l', 'm', 'n', 'o',
						'p', 'q', 'r', 's', 't',
						'u', 'v', 'w', 'x', 'y',
						'z'};

// ---------- SHIFT CIPHER ---------- //

vector<string> EncryptShiftCipher(vector<string> words_to_encrypt){
	vector<string> encrypted_words;
	int shift;

	cout << "Enter the the shift value to encrypt: ";
	cin >> shift;

	for (const auto word : words_to_encrypt){
		string encrypted_word;
		for (const auto c : word){
			int i_new_c = c + shift;

			encrypted_word += static_cast<char>(i_new_c);
		}
		encrypted_words.push_back(encrypted_word);
	}

	return encrypted_words;
}

// ---------- AFFINE CIPHER ---------- //

vector<string> EncryptAffineCipher(vector<string> words_to_encrypt){
	vector<string> encrypted_words;
	int a, b;

	cout << "Enter KEY=a to encrypt: "s;
	cin >> a;
	while (__gcd(a, ascii_size) != 1){
		cout << "'a' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a to encrypt: "s;
		cin >> a;
	}
	cout << "Enter KEY=b to encrypt: "s;
	cin >> b;

	for (const auto& word : words_to_encrypt){
		string encrypted_word;
		for (const auto& c : word){
			int i_new_c;

			i_new_c = (a*c + b) % ascii_size;

			encrypted_word += static_cast<uint8_t>(i_new_c);

		}
		encrypted_words.push_back(encrypted_word);
	}

	return encrypted_words;
}

// ---------- RECURRENT AFFINE CIPHER ---------- //

vector<string> EncryptRecurrentAffineCipher(vector<string> words_to_encrypt){
	vector<string> encrypted_words;
	int a1, b1, a2, b2;

	cout << "Enter KEY=(a1,b1) to encrypt: "s << endl;
	cout << "Enter KEY=a1: "s;
	cin >> a1;
	while (__gcd(a1, ascii_size) != 1){
		cout << "'a1' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a1: "s;
		cin >> a1;
	}
	cout << "Enter KEY=b1: "s;
	cin >> b1;

	cout << "Enter KEY=(a2,b2) to encrypt: "s << endl;
	cout << "Enter KEY=a2: "s;
	cin >> a2;
	while (__gcd(a2, ascii_size) != 1){
		cout << "'a2' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a2: "s;
		cin >> a2;
	}
	cout << "Enter KEY=b2: "s;
	cin >> b2;

	int counter = 1;
	int current_a, current_b, previous_a, previous_b;
	// could be done recursive
	for (const auto& word : words_to_encrypt){
		string encrypted_word;
		for (const auto& c : word){
			int i_new_c;
			if (counter == 1){
				int a_n = a1;
				int b_n = b1;
				current_a = a1;
				current_b = b1;
				i_new_c = (a_n*c + b_n) % ascii_size;
			}else if (counter == 2){
				int a_n = a2;
				int b_n = b2;
				current_a = a2;
				current_b = b2;
				previous_a = a1;
				previous_b = b1;
				i_new_c = (a_n*c + b_n) % ascii_size;
			}else if (counter >= 3){
				int a_n = previous_a*current_a;
				int b_n = previous_b + current_b;
				previous_a = current_a;
				previous_b = current_b;
				current_a = a_n;
				current_b = b_n;
				i_new_c = (a_n*c + b_n) % ascii_size;
			}

			encrypted_word += static_cast<uint8_t>(i_new_c);
			++counter;
		}
		encrypted_words.push_back(encrypted_word);
	}

	return encrypted_words;
}

// ---------- HILL'S CIPHER ---------- //

vector<string> EncryptHillsCipher(vector<string> words_to_encrypt){
	vector<string> encrypted_words;

	auto matrix_key = EnterMatrix();

	for (auto& word : words_to_encrypt){
		string encrypted_word;
		vector<vector<char>> word_by_n_gramms;

		while (word.size() % matrix_key.size() != 0){
			word += dummy_symbol;
		}

		int counter = 0;
		vector<char> n_gramm;
		for (auto c : word){
			n_gramm.push_back(c);
			++counter;
			if (counter == static_cast<int>(matrix_key.size())){
				word_by_n_gramms.push_back(n_gramm);
				n_gramm.clear();
				counter = 0;
			}
		}

		vector<vector<int>> word_by_n_gramms_int;
		for (auto& n_gramm : word_by_n_gramms){
			vector<int> n_gramm_int;
			for (auto& c : n_gramm){
				int c_number = getIndex(alphabet, c);
				n_gramm_int.push_back(c_number);
			}
			word_by_n_gramms_int.push_back(n_gramm_int);
		}

		vector<vector<int>> word_by_n_gramms_int_encrypted;
		for (auto& n_gramm_int : word_by_n_gramms_int){
			vector<vector<int>> matrix_dummy;
			for (auto& num : n_gramm_int){
				vector<int> row_dummy;
				row_dummy.push_back(num);
				matrix_dummy.push_back(row_dummy);
			}

			vector<vector<int>> matrix_to_encrypt = MultiplyMatrix(matrix_key, matrix_dummy);

			vector<int> matrix_encrypted;
			for (auto& row : matrix_to_encrypt){
				vector<int> row_encrypted;
				for(auto& num : row){
					int encrypted_num = num % alphabet_size;
					matrix_encrypted.push_back(encrypted_num);
				}
			}
			word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);

		}

		vector<vector<char>> word_by_n_gramms_encrypted;
		for(auto& n_gramm_int : word_by_n_gramms_int_encrypted){
			vector<char> encrypted_n_gramm;
			for (auto& encrypted_int_c : n_gramm_int){
				char encrypted_c = alphabet[encrypted_int_c];
				encrypted_n_gramm.push_back(encrypted_c);
			}
			word_by_n_gramms_encrypted.push_back(encrypted_n_gramm);
		}

		for(auto& encrypted_n_gramm : word_by_n_gramms_encrypted){
			for(auto& encrypted_c : encrypted_n_gramm){
				encrypted_word += encrypted_c;
			}
		}

		encrypted_words.push_back(encrypted_word);
	}

	return encrypted_words;
}

// ---------- RECURRENT HILL'S CIPHER ---------- //

vector<string> EncryptRecurrentHillsCipher(vector<string> words_to_encrypt){
	vector<string> encrypted_words;

	cout << "Enter Matrix 1 key:" << endl;
	auto matrix_key_1 = EnterMatrix();
	cout << "Matrix 2 should be the same size as Matrix 1" << endl;
	cout << "Enter Matrix 2 key: " << endl;
	auto matrix_key_2 = EnterMatrix();

	for (auto& word : words_to_encrypt){
		auto matrix_key_a = matrix_key_1;
		auto matrix_key_b = matrix_key_2;
		string encrypted_word;
		vector<vector<char>> word_by_n_gramms;

		while (word.size() % matrix_key_1.size() != 0){
			word += dummy_symbol;
		}

		int counter = 0;
		vector<char> n_gramm;
		for (auto c : word){
			n_gramm.push_back(c);
			++counter;
			if (counter == static_cast<int>(matrix_key_1.size())){
				word_by_n_gramms.push_back(n_gramm);
				n_gramm.clear();
				counter = 0;
			}
		}

		vector<vector<int>> word_by_n_gramms_int;
		for (auto& n_gramm : word_by_n_gramms){
			vector<int> n_gramm_int;
			for (auto& c : n_gramm){
				int c_number = getIndex(alphabet, c);
				n_gramm_int.push_back(c_number);
			}
			word_by_n_gramms_int.push_back(n_gramm_int);
		}

		// recursion
		int counter_m = 1;
		vector<vector<int>> word_by_n_gramms_int_encrypted;
		for (auto& n_gramm_int : word_by_n_gramms_int){
			vector<vector<int>> matrix_dummy;

			for (auto& num : n_gramm_int){
				vector<int> row_dummy;
				row_dummy.push_back(num);
				matrix_dummy.push_back(row_dummy);
			}

			vector<vector<int>> matrix_to_encrypt;
			if (counter_m == 1){
				auto matrix_to_encrypt = MultiplyMatrix(matrix_key_1, matrix_dummy);
				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;

			}else if (counter_m == 2){
				auto matrix_to_encrypt = MultiplyMatrix(matrix_key_2, matrix_dummy);
				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;

			}else{
				// recursion
				auto matrix_key_n = MultiplyMatrix(matrix_key_b, matrix_key_a);
				auto matrix_to_encrypt = MultiplyMatrix(matrix_key_n, matrix_dummy);

				matrix_key_b = matrix_key_n;
				matrix_key_a = matrix_key_b;

				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;
			}
		}

		vector<vector<char>> word_by_n_gramms_encrypted;
		for(auto& n_gramm_int : word_by_n_gramms_int_encrypted){
			vector<char> encrypted_n_gramm;
			for (auto& encrypted_int_c : n_gramm_int){
				char encrypted_c = alphabet[encrypted_int_c];
				encrypted_n_gramm.push_back(encrypted_c);
			}
			word_by_n_gramms_encrypted.push_back(encrypted_n_gramm);
		}

		for(auto& encrypted_n_gramm : word_by_n_gramms_encrypted){
			for(auto& encrypted_c : encrypted_n_gramm){
				encrypted_word += encrypted_c;
			}
		}

		encrypted_words.push_back(encrypted_word);
	}

	return encrypted_words;
}

// ---------- ---------- ---------- //
// ---------- DECRYPTION ---------- //
// ---------- ---------- ---------- //

// ---------- SHIFT CIPHER ---------- //

vector<string> DecryptShiftCipher(vector<string> words_to_decrypt){
	vector<string> decrypted_words;
	int shift;

	cout << "Enter the the shift value to decrypt: ";
	cin >> shift;

	for (const auto word : words_to_decrypt){
		string decrypted_word;
		for (const auto c : word){
			int i_new_c = c - shift;

			decrypted_word += static_cast<char>(i_new_c);
		}
		decrypted_words.push_back(decrypted_word);
	}

	return decrypted_words;
}

// ---------- AFFINE CIPHER ---------- //

vector<string> DecryptAffineCipher(vector<string> words_to_decrypt){
	vector<string> decrypted_words;
	int a, b;

	cout << "Enter KEY=a to decrypt: "s;
	cin >> a;
	while (__gcd(a, ascii_size) != 1){
		cout << "'a' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a to encrypt: "s;
		cin >> a;
	}
	cout << "Enter KEY=b to decrypt: "s;
	cin >> b;

	for (const auto& word : words_to_decrypt){
		string decrypted_word;
		for (const auto& c : word){
			int i_new_c;

			int a_ = 1;
			while (a*a_ % ascii_size != 1){
				++a_;
			}

			i_new_c = (a_*(c + ascii_size - b)) % ascii_size;

			decrypted_word += static_cast<uint8_t>(i_new_c);
		}
		decrypted_words.push_back(decrypted_word);
	}

	return decrypted_words;
}

// ---------- RECURRENT AFFINE CIPHER ---------- //

vector<string> DecryptRecurrentAffineCipher(vector<string> words_to_decrypt){
	vector<string> decrypted_words;
	int a1, b1, a2, b2;

	cout << "Enter KEY=(a1,b1) to decrypt: "s << endl;
	cout << "Enter KEY=a1: "s;
	cin >> a1;
	while (__gcd(a1, ascii_size) != 1){
		cout << "'a1' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a1: "s;
		cin >> a1;
	}
	cout << "Enter KEY=b1: "s;
	cin >> b1;

	cout << "Enter KEY=(a2,b2) to decrypt: "s << endl;
	cout << "Enter KEY=a2: "s;
	cin >> a2;
	while (__gcd(a2, ascii_size) != 1){
		cout << "'a2' key should be mutually simple with ascii size = 256"s << endl;
		cout << "Enter KEY=a2: "s;
		cin >> a2;
	}
	cout << "Enter KEY=b2: "s;
	cin >> b2;

	int counter = 1;
	int current_a, current_b, previous_a, previous_b;
	// could be done recursive
	for (const auto& word : words_to_decrypt){
		string decrypted_word;
		for (const auto& c : word){
			int i_new_c = c;
			if (counter == 1){
				int a_n = a1;
				int b_n = b1;
				int a_ = 1;
				current_a = a1;
				current_b = b1;
				while (a_n*a_ % ascii_size != 1){
					++a_;
				}
				i_new_c = (a_*(c + ascii_size - b_n)) % ascii_size;
			}else if (counter == 2){
				int a_n = a2;
				int b_n = b2;
				current_a = a2;
				current_b = b2;
				previous_a = a1;
				previous_b = b1;
				int a_ = 1;
				while (a_n*a_ % ascii_size != 1){
					++a_;
				}
				i_new_c = (a_*(c + ascii_size - b_n)) % ascii_size;
			}else if (counter >= 3){
				int a_n = previous_a*current_a;
				int b_n = previous_b + current_b;
				previous_a = current_a;
				previous_b = current_b;
				current_a = a_n;
				current_b = b_n;
				int a_ = 1;
				while (a_n*a_ % ascii_size != 1){
					++a_;
				}
				i_new_c = (a_*(c + ascii_size - b_n)) % ascii_size;
			}

			decrypted_word += static_cast<uint8_t>(i_new_c);
			++counter;
		}
		decrypted_words.push_back(decrypted_word);
	}

	return decrypted_words;
}

// ---------- HILL'S CIPHER ---------- //

vector<string> DecryptHillsCipher(vector<string> words_to_decrypt){
	vector<string> decrypted_words;

	auto matrix_key = EnterMatrix();
	vector<vector<int>> matrix_inverse_key = getInverse(matrix_key);

	for (auto& word : words_to_decrypt){
		string decrypted_word;
		vector<vector<char>> word_by_n_gramms;

		int counter = 0;
		vector<char> n_gramm;
		for (auto c : word){
			n_gramm.push_back(c);
			++counter;
			if (counter == static_cast<int>(matrix_key.size())){
				word_by_n_gramms.push_back(n_gramm);
				n_gramm.clear();
				counter = 0;
			}
		}

		vector<vector<int>> word_by_n_gramms_int;
		for (auto& n_gramm : word_by_n_gramms){
			vector<int> n_gramm_int;
			for (auto& c : n_gramm){
				int c_number = getIndex(alphabet, c);
				n_gramm_int.push_back(c_number);
			}
			word_by_n_gramms_int.push_back(n_gramm_int);
		}

		vector<vector<int>> word_by_n_gramms_int_encrypted;
		for (auto& n_gramm_int : word_by_n_gramms_int){
			vector<vector<int>> matrix_dummy;
			for (auto& num : n_gramm_int){
				vector<int> row_dummy;
				row_dummy.push_back(num);
				matrix_dummy.push_back(row_dummy);
			}

			vector<vector<int>> matrix_to_encrypt = MultiplyMatrix(matrix_inverse_key, matrix_dummy);

			vector<int> matrix_encrypted;
			for (auto& row : matrix_to_encrypt){
				vector<int> row_encrypted;
				for(auto& num : row){
					int encrypted_num = num % alphabet_size;
					if (encrypted_num < 0){
						encrypted_num += 26;
					}
					matrix_encrypted.push_back(encrypted_num);
				}
			}
			word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);

		}

		vector<vector<char>> word_by_n_gramms_encrypted;
		for(auto& n_gramm_int : word_by_n_gramms_int_encrypted){
			vector<char> encrypted_n_gramm;
			for (auto& encrypted_int_c : n_gramm_int){
				char encrypted_c = alphabet[encrypted_int_c];
				encrypted_n_gramm.push_back(encrypted_c);
			}
			word_by_n_gramms_encrypted.push_back(encrypted_n_gramm);
		}

		for(auto& encrypted_n_gramm : word_by_n_gramms_encrypted){
			for(auto& encrypted_c : encrypted_n_gramm){
				decrypted_word += encrypted_c;
			}
		}

		decrypted_words.push_back(decrypted_word);
	}

	return decrypted_words;
}

// ---------- RECURRENT HILL'S CIPHER ---------- //

vector<string> DecryptRecurrentHillsCipher(vector<string> words_to_decrypt){
	vector<string> decrypted_words;

	cout << "Enter Matrix 1 key:" << endl;
	auto matrix_key_1 = EnterMatrix();
	cout << "Matrix 2 should be the same size as Matrix 1" << endl;
	cout << "Enter Matrix 2 key:" << endl;
	auto matrix_key_2 = EnterMatrix();

	vector<vector<int>> matrix_inverse_key_1 = getInverse(matrix_key_1);
	vector<vector<int>> matrix_inverse_key_2 = getInverse(matrix_key_2);

	for (auto& word : words_to_decrypt){
		auto matrix_inverse_key_a = matrix_inverse_key_1;
		auto matrix_inverse_key_b = matrix_inverse_key_2;
		string decrypted_word;
		vector<vector<char>> word_by_n_gramms;

		int counter = 0;
		vector<char> n_gramm;
		for (auto c : word){
			n_gramm.push_back(c);
			++counter;
			if (counter == static_cast<int>(matrix_key_1.size())){
				word_by_n_gramms.push_back(n_gramm);
				n_gramm.clear();
				counter = 0;
			}
		}

		vector<vector<int>> word_by_n_gramms_int;
		for (auto& n_gramm : word_by_n_gramms){
			vector<int> n_gramm_int;
			for (auto& c : n_gramm){
				int c_number = getIndex(alphabet, c);
				n_gramm_int.push_back(c_number);
			}
			word_by_n_gramms_int.push_back(n_gramm_int);
		}

		//recursion
		int counter_m = 1;
		vector<vector<int>> word_by_n_gramms_int_encrypted;
		for (auto& n_gramm_int : word_by_n_gramms_int){
			vector<vector<int>> matrix_dummy;
			for (auto& num : n_gramm_int){
				vector<int> row_dummy;
				row_dummy.push_back(num);
				matrix_dummy.push_back(row_dummy);
			}

			vector<vector<int>> matrix_to_encrypt;
			if (counter_m == 1){
				matrix_to_encrypt = MultiplyMatrix(matrix_inverse_key_1, matrix_dummy);
				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						if (encrypted_num < 0){
							encrypted_num += 26;
						}
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;

			}else if (counter_m == 2){
				matrix_to_encrypt = MultiplyMatrix(matrix_inverse_key_2, matrix_dummy);
				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						if (encrypted_num < 0){
							encrypted_num += 26;
						}
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;

			}else{
				auto matrix_inverse_key_n = MultiplyMatrix(matrix_inverse_key_a, matrix_inverse_key_b);
				matrix_to_encrypt = MultiplyMatrix(matrix_inverse_key_n, matrix_dummy);

				matrix_inverse_key_a = matrix_inverse_key_n;
				matrix_inverse_key_b = matrix_inverse_key_a;

				vector<int> matrix_encrypted;
				for (auto& row : matrix_to_encrypt){
					vector<int> row_encrypted;
					for(auto& num : row){
						int encrypted_num = num % alphabet_size;
						if (encrypted_num < 0){
							encrypted_num += 26;
						}
						matrix_encrypted.push_back(encrypted_num);
					}
				}
				word_by_n_gramms_int_encrypted.push_back(matrix_encrypted);
				++counter_m;
			}
		}

		vector<vector<char>> word_by_n_gramms_encrypted;
		for(auto& n_gramm_int : word_by_n_gramms_int_encrypted){
			vector<char> encrypted_n_gramm;
			for (auto& encrypted_int_c : n_gramm_int){
				char encrypted_c = alphabet[encrypted_int_c];
				encrypted_n_gramm.push_back(encrypted_c);
			}
			word_by_n_gramms_encrypted.push_back(encrypted_n_gramm);
		}

		for(auto& encrypted_n_gramm : word_by_n_gramms_encrypted){
			for(auto& encrypted_c : encrypted_n_gramm){
				decrypted_word += encrypted_c;
			}
		}

		decrypted_words.push_back(decrypted_word);
	}

	return decrypted_words;
}

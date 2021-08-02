//============================================================================
// Name        : CryptographyCiphers.cpp
// Author      : Maxim Kholodilin
// Version     : v.0.2
// Copyright   : Maxim Kholodilin
// Description : Some of the cryptography ciphers
//============================================================================

#include "menu.h"

#include <iostream>

int main(){
	auto text_to_use = Input();

	std::cout << "Choose from: " << std::endl;
	std::cout << "1. FULL ASCII CIPHERS" << std::endl;
	std::cout << "2. ALPHABET CIPHERS" << std::endl;
	std::cout << "enter 1/2..." << std::endl;

	int num;
	std::cin >> num;

	if (num == 1){
		MenuFunc1(text_to_use);
	}else if (num == 2){
		MenuFunc2(text_to_use);
	}else{
		return 0;
	}

	return 0;
}

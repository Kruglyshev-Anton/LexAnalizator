#pragma once
#include<iostream>

using namespace std;
struct Token {
	char* lex;
	char* type;
	Token() {
		lex = nullptr;
		type = nullptr;

	}
	Token(char* lex, char* type) {
		this->lex = lex;
		this->type = type;
		
	}
	~Token() {
	/*	delete[] lex;
		delete[] type;*/
	}
	Token& setLex(const char* newLex) {
		delete[] lex;
		lex = new char[strlen(newLex) + 1];
		int i = 0;
		while (newLex[i] != '\0') {
			lex[i] = newLex[i];
			++i;
		}
		lex[i] = '\0';
		return *this;
	}

	Token& setType(const char* newType) {
		delete[] type;
		type = new char[strlen(newType) + 1];
		int i = 0;
		while (newType[i] != '\0') {
			type[i] = newType[i];
			++i;
		}
		type[i] = '\0';
		return *this;
	}

	Token& setToken(const char* newLex, const char* newType) {
		setLex(newLex);
		setType(newType);
		return *this;
	}

};
class HashTable
{
private:


	Token* tokens;



public:
	size_t hashFunc(const char* lex) {
		int num = 0;
		int ch = 0;
		while (lex[ch] != '\0') {
			num += 997 * lex[ch];
			num %= 1000003;
			++ch;
		}
		while (tokens[num % 1000003].lex != nullptr) {
			++num;
		}
		return num;
	}
	HashTable() {
		tokens = new Token[1000003];
	}
	void add(const char* lex, const char* type) {
		size_t ind = hashFunc(lex);
		tokens[ind].setToken(lex, type);
	}
	Token& operator[](int i) {
		return tokens[i];
	}


};


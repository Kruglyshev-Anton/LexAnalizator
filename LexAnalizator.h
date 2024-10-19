#pragma once
#include "HashTable.h"

#include "nfa.h"
#include <fstream>

class LexAnalizator
{
private:

	HashTable tokens;
	std::vector<char> alph = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', \
		'c', 'v', 'b', 'n', 'm', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ';', ':', ',', '+', '-', '(', ')',\
		'=', '>', '<', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',\
		'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
	std::vector<int> dopsos = { 9, 14, 17, 20, 27, 30, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 };
	std::vector<std::vector<std::vector<int>>> teta = std::vector<std::vector<std::vector<int>>>(50, std::vector<std::vector<int>>(72, std::vector<int>(1, -1)));
	dfa DFA;
	nfa NFA;

public:
	LexAnalizator() {
		tokens = HashTable();

		std::vector<int> sost;
		
		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 72; ++j) {
				if (i == 47) {
					if (j < 26 || j >= 43)sost = { 47 };
					else sost = { 49 };
					}
				else if (i == 0) {
					if (alph[j] == 'p')sost = { 1, 47 };
					else if (alph[j] == 'b')sost = { 10,47 };
					else if (alph[j] == 'e')sost = { 15,47 };
					else if (alph[j] == 'v')sost = { 18,47 };
					else if (alph[j] == 'i')sost = { 21,47 };
					else if (alph[j] == 'f')sost = { 28,47 };
					else if (alph[j] == 't')sost = { 31,47 };
					else if (alph[j] == 'd')sost = { 33,47 };
					else if (alph[j] == ';')sost = { 35 };
					else if (alph[j] == ':')sost = { 36 };
					else if (alph[j] == ',')sost = { 38 };
					else if (alph[j] == '+')sost = { 39 };
					else if (alph[j] == '-')sost = { 40 };
					else if (alph[j] == '(')sost = { 41 };
					else if (alph[j] == ')')sost = { 42 };
					else if (alph[j] == '=')sost = { 43 };
					else if (alph[j] == '<')sost = { 44 };
					else if (alph[j] == '>')sost = { 46 };
					else if (j < 26 || j >= 43)sost = { 47 };
					else if (alph[j] != '0')sost = { 48 };
					else sost = { 49 };
				}

				else if (i == 1) {
					if (alph[j] == 'r')sost = { 2 };
					else sost = { 49 };
				}
				else if (i == 2) {
					if (alph[j] == 'o')sost = { 3 };
					else sost = { 49 };
				}
				else if (i == 3) {
					if (alph[j] == 'c')sost = { 4 };
					else sost = { 49 };
				}
				else if (i == 4) {
					if (alph[j] == 'e')sost = { 5 };
					else sost = { 49 };
				}
				else if (i == 5) {
					if (alph[j] == 'd')sost = { 6 };
					else sost = { 49 };
				}
				else if (i == 6) {
					if (alph[j] == 'u')sost = { 7 };
					else sost = { 49 };
				}
				else if (i == 7) {
					if (alph[j] == 'r')sost = { 8 };
					else sost = { 49 };
				}
				else if (i == 8) {
					if (alph[j] == 'e')sost = { 9 };
					else sost = { 49 };
				}
				else if (i == 9) {
					sost = { 49 };
				}
				else if (i == 10) {
					if (alph[j] == 'e')sost = { 11 };
					else sost = { 49 };
				}
				else if (i == 11) {
					if (alph[j] == 'g')sost = { 12 };
					else sost = { 49 };
				}
				else if (i == 12) {
					if (alph[j] == 'i')sost = { 13 };
					else sost = { 49 };
				}
				else if (i == 13) {
					if (alph[j] == 'n')sost = { 14 };
					else sost = { 49 };
				}
				else if (i == 14) {
					sost = { 49 };
				}
				else if (i == 15) {
					if (alph[j] == 'n')sost = { 16 };
					else sost = { 49 };
				}
				else if (i == 16) {
					if (alph[j] == 'd')sost = { 17 };
					else sost = { 49 };
				}
				else if (i == 17) {
					sost = { 49 };
				}
				else if (i == 18) {
					if (alph[j] == 'a')sost = { 19 };
					else sost = { 49 };
				}
				else if (i == 19) {
					if (alph[j] == 'r')sost = { 20 };
					else sost = { 49 };
				}
				else if (i == 20) {
					sost = { 49 };
				}
				else if (i == 21) {
					if (alph[j] == 'n')sost = { 22 };
					else sost = { 49 };
				}
				else if (i == 22) {
					if (alph[j] == 't')sost = { 23 };
					else sost = { 49 };
				}
				else if (i == 23) {
					if (alph[j] == 'e')sost = { 24 };
					else sost = { 49 };
				}
				else if (i == 24) {
					if (alph[j] == 'g')sost = { 25 };
					else sost = { 49 };
				}
				else if (i == 25) {
					if (alph[j] == 'e')sost = { 26 };
					else sost = { 49 };
					}
				else if (i == 26) {
					if (alph[j] == 'r')sost = { 27 };
					else sost = { 49 };
					}
				else if (i == 27) {
					sost = { 49 };
					}
				else if (i == 28) {
					if (alph[j] == 'o')sost = { 29 };
					else sost = { 49 };
					}
				else if (i == 29) {
					if (alph[j] == 'r')sost = { 30 };
					else sost = { 49 };
					}
				else if (i == 30) {
					sost = { 49 };
					}
				else if (i == 31) {
					if (alph[j] == 'o')sost = { 32 };
					else sost = { 49 };
					}
				else if (i == 32) {
					sost = { 49 };
					}
				else if (i == 33) {
					if (alph[j] == 'o')sost = { 34 };
					else sost = { 49 };
					}
				else if (i == 34) {
					sost = { 49 };
					}
				else if (i == 35) {
					sost = { 49 };
					}
				else if (i == 36) {
					if (alph[j] == '=')sost = { 37 };
					else sost = { 49 };
					}
				else if (i == 37) {
					sost = { 49 };
				}
				else if (i == 38) {
					sost = { 49 };
				}
				else if (i == 39) {
					 sost = { 49 };
					}
				else if (i == 40) {
					 sost = { 49 };
				}
				else if (i == 41) {
					sost = { 49 };
				}
				else if (i == 42) {
					 sost = { 49 };
					}
				else if (i == 43) {
					sost = { 49 };
				}
				else if (i == 44) {
					if (alph[j] == '>')sost = { 45 };
					else sost = { 49 };
					}
				else if (i == 45) {
					sost = { 49 };
					}
				else if (i == 46) {
					 sost = { 49 };
					}
				


				else if (i == 48) {
					if (j >= 26 && j <=35)sost = { 48 };
					else sost = { 49 };
					}
				else if (i == 49) {
					sost = { -1 };
					}
				else sost = { -1 };

					teta[i][j] = sost;
			}
		}
		/*
		for (std::vector<std::vector<int>> i : teta) {
			for (std::vector<int> j : i) {
				for (int k : j) {
					cout << k << ',';
				}
				cout << ' ';
			}
			cout << endl;
		}
		*/
		NFA = nfa(50, alph, dopsos, teta);
		DFA = NFA.createDFA();
		DFA.minimize();
	}
	void Scan(std::string file) {
		ifstream fin;
		fin.open(file);
		std::string x;
		std::pair<bool, int> pa;
		int cs;
		while (fin >> x) {
			
			try {
				pa = DFA.isAccept(x);
			}
			catch (...) {

			}
			cs = pa.second;
			//cout << cs << ' ';
			//cout << x.c_str() << ' ' << tokens.hashFunc(x.c_str()) << std::endl;
			if (pa.first) {
				
				if (cs==50||cs==33||cs==44) {
					tokens.add(x.c_str(), "COMMAND");
				}
				else if (cs==37||cs==47) {
					
					tokens.add(x.c_str(), "TYPE");
				}
				else if (cs==36||cs==24||cs==27) {
					tokens.add(x.c_str(), "INSTRUCTION");
				}
				else if (cs==1||cs==9||cs==6||cs==2||cs==7||cs==4||cs==5||cs==3||cs==8) {
					tokens.add(x.c_str(), "ID_NAME");
				}
				else if (cs==10) {
					tokens.add(x.c_str(), "NUMBER");
				}
				else if (cs == 32 || cs == 15 || cs == 16 || cs == 21 || cs == 20 || cs == 12 || cs == 13 || cs == 17 || cs == 18||
					cs==19||cs==14) {
					tokens.add(x.c_str(), "OPERATOR");
				}

			}
		}
		fin.close();
	}
	void ScanWrite(std::string file) {
		ifstream fin;
		ofstream fout;
		fin.open(file);
		fout.open("output.txt");
		std::string x;
		std::pair<bool, int> pa;
		int cs;
		while (fin >> x) {
			
			//cout << DFA.isAccept(x).second;
			try {
				pa = DFA.isAccept(x);
			}
			catch (...) {}
			cs = pa.second;
			//cout << cs << ' ';
			//cout << x.c_str() << ' ' << tokens.hashFunc(x.c_str()) << std::endl;
			
			if (pa.first) {
				size_t ind = tokens.hashFunc(x.c_str());
				if (cs == 50 || cs == 33 || cs == 44) {
					tokens.add(x.c_str(), "COMMAND");
					fout << x << '|' << "COMMAND|" << ind << endl;

				}
				else if (cs == 37 || cs == 47) {
					tokens.add(x.c_str(), "TYPE");
					fout << x << '|' << "TYPE|" << ind << endl;
				}
				else if (cs == 36 || cs == 24 || cs == 27) {
					tokens.add(x.c_str(), "INSTRUCTION");
					fout << x << '|' << "INSTUCLION|" << ind << endl;
				}
				else if (cs == 1 || cs == 9 || cs == 6 || cs == 2 || cs == 7 || cs == 4 || cs == 5 || cs == 3 || cs == 8||cs==22) {
					tokens.add(x.c_str(), "ID_NAME");
					fout << x << '|' << "ID_NAME|" << ind << endl;
				}
				else if (cs == 10) {
					tokens.add(x.c_str(), "NUMBER");
					fout << x << '|' << "NUMBER|" << ind << endl;
				}
				else if (cs == 32 || cs == 15 || cs == 16 || cs == 21 || cs == 20 || cs == 12 || cs == 13 || cs == 17 || cs == 18 ||
					cs == 19 || cs == 14) {
					tokens.add(x.c_str(), "OPERATOR");
					fout << x << '|' << "OPERATOR|" << ind << endl;
				}

			}
			else {
				fout << x << " Bad lexem\n";
			}
		}
		fin.close();
	}
	void write() {
		ofstream fout;
		fout.open("output.txt");
		for (int i = 0; i < 1000003; ++i) {
			if (tokens[i].lex != nullptr) {
				cout << tokens[i].lex << std::endl;
				fout << tokens[i].lex << " | " << tokens[i].type << " | " << tokens.hashFunc(tokens[i].lex) << std::endl;
			}
		}

		fout.close();
	}
};


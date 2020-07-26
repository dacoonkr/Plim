#include "plim.h"
#include "concolor.h"
#include <conio.h>
#include <Windows.h>

string codes;

std::string ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); 
	}
	return str;
}

int main(int argc, char** argv) {
	if (argv[1] != nullptr) {
		if (strcmp(argv[1], "build") == 0) {
			fstream file(argv[2]);
			string buff;
			while (getline(file, buff)) {
				codes += (buff + ';');
			}
			compile_(codes, argv[3]);
		}
		else if (strcmp(argv[1], "run") == 0) {
			run_(argv[2]);
		}
		else {
			fstream file(argv[1]);
			string buff;
			while (getline(file, buff)) {
				codes += (buff + ';');
			}
			compile_and_run(codes);
		}
	}
	else {
		string tmps;
		switch (false) {
		case true:
			while (getline(cin, tmps)) {
				codes = tmps;
				if (tmps.length() > 0) if (tmps[tmps.length() - 1] != ';') {
					while (1) {
						string tmps;
						cout << "  > ", getline(cin, tmps);
						codes += ";";
						codes += tmps;
						if (tmps.length() > 0) { if (tmps[tmps.length() - 1] == ';') break; }
					}
				}
				if (codes != "") {
					compile_and_run(codes);
				}
			}
			break;
		case false:
			vector<Data> tokens;
			string now;
			cout << ">>> ";
			while (1) {
				int p = _getch();
				if (p == '\r') {
					if (now.length() > 0) {
						if (now[now.length() - 1] == ';') {
							concolor(WHITE, BLACK);
							cout << "\n";
							compile_and_run(now);
							_getch();
							now = "";
							system("cls");
							cout << ">>> ";
						}
						else {
							now += ";\n";
						}
					}
				}
				if (p == 8) {
					if (now.length() == 0) continue;
					now = now.substr(0, now.length() - 1);
				}
				else now += (char)p;
				tokens.clear();
				int a = OrsplitTokens(now, &tokens);
				system("cls");
				concolor(WHITE, BLACK);
				cout << ">>> ";
				if (a == 1) {
					concolor(LIGHTRED, BLACK);
					cout << now;
				}
				else {
					for (int i = 0; i < tokens.size(); i++) {
						if (tokens[i].type == 3) {
							concolor(BROWN, BLACK);
							string a = ReplaceAll(tokens[i].data, "\n", "(rep)");
							a = ReplaceAll(a, "\\", "(rep2)");

							a = ReplaceAll(a, "(rep)", "\\n");
							a = ReplaceAll(a, "(rep2)", "\\\\");
							cout << "\"" << a << "\"";
						}
						else if (tokens[i].type == 1) {
							concolor(CYAN, BLACK);
							cout << "" << tokens[i].data << "";
						}
						else if (tokens[i].type == 6) {
							concolor(LIGHTMAGENTA, BLACK);
							cout << "" << tokens[i].data << "";
						}
						else if (tokens[i].type == 2) {
							if (isKeyVariable(tokens[i].data)) concolor(LIGHTMAGENTA, BLACK);
							else concolor(LIGHTGREEN, BLACK);
							cout << "" << tokens[i].data << "";
						}
						else {
							concolor(WHITE, BLACK);
							cout << "" << tokens[i].data << "";
						}
					}
				}
			}
			break;
		}
	}
}
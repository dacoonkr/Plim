#include "plim.h"

string codes;

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
		cout << ">>> ";
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
				cout << ">>> ";
			}
		}
	}
}
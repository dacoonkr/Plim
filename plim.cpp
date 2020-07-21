#include "plim.h"

char buffer[10005];
string codes;

int main() {
	while (cout << ">>> ", cin.getline(buffer, 10005)) {
		codes = buffer;
		while (1) {
			cout << "  > ", cin.getline(buffer, 10005);
			string tmps = buffer;
			codes += ";";
			codes += buffer;
			if (tmps.length() > 0) { if (tmps[tmps.length() - 1] == ';') break; }
		}
		compile_and_run(codes);
	}
}
#include "plim.h"

char buffer[10005];
string codes;

int main() {
	while (cout << ">>> ", cin.getline(buffer, 10005)) {
		codes = buffer;
		while (codes[codes.length() - 1] != ';') {
			cout << "  > ", cin.getline(buffer, 10005);
			codes += ";";
			codes += buffer;
		}
		compile_and_run(codes);
	}
}
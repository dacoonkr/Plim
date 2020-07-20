#include "plim.h"

char buffer[10005];
string codes;

int main() {
	while (cout << ">>> ", cin.getline(buffer, 10005)) {
		codes = buffer;
		compile_and_run(codes);
	}
}
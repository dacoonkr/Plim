#define FAST_IO std::ios::sync_with_stdio(1); std::cin.tie(0); std::cout.tie(0);

#include <string>
#include <iostream>

#include "plim.hpp"

auto main() -> int {
	FAST_IO;

	std::cout << "Plim(PT-1) Interpreter";
	while (1) {
		std::string this_line;
		std::cout << "\n>>> ";
		std::getline(std::cin, this_line);

		pl::plim_run(this_line);
	}
}
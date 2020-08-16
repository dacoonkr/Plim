#pragma once

#include <string>
#include <iostream>

namespace pl {
	auto RtError(std::string content) -> void {
		std::cout << "\nRuntime Error:\n  " << content << "\n";
		exit(0);
	}

	auto CpError(std::string content) -> void {
		std::cout << "\nCompile Error:\n  " << content << "\n";
		exit(0);
	}

	auto ParameterRequireError(std::string at, int requireCnt) -> std::string {
		return at + " requires just " + std::to_string(requireCnt) + " parameters";
	}
	auto ParameterTypeError(std::string at, std::vector<std::string> requirement) -> std::string {
		at += " requires just {";
		for (int i = 0; i < requirement.size(); i++) {
			at += requirement[i];
			if (i != requirement.size() - 1) at += ", ";
		}
		at += "} parameters";
		return at;
	}
}
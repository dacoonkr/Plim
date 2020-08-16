#pragma once

#include <vector>
#include <stack>
#include "classes.hpp"
#include "error.hpp"

namespace pl {
	auto checkSyntax(std::vector<RtData>& this_line) -> int {
		std::stack<std::string> StBracket;
		for (int i = 0; i < this_line.size(); i++) {
			auto& now = this_line[i];
			auto& before = this_line[i];
			if (i > 0) before = this_line[i - 1];
			if (now.type == 1) {
				if (i > 0) if (before.type == 1) {
					CpError("Operators is continuous.");
				}
				if (now.data == "(") StBracket.push("(");
				if (now.data == "{") StBracket.push("{");

				if (now.data == ")") {
					if (StBracket.empty()) CpError("() is not matched.");
					if (StBracket.top() != "(") CpError("() is not matched.");;
					StBracket.pop();
				}
				if (now.data == "}") {
					if (StBracket.empty()) CpError("{} is not matched.");
					if (StBracket.top() != "{") CpError("{} is not matched.");
					StBracket.pop();
				}
			}
			else {
				if (i > 0) if (before.type != 1) {
					CpError("Values is continuous.");
				}
			}
		}
		if (!StBracket.empty()) {
			if (StBracket.top() == "{")
				CpError("{} is not matched.");
			if (StBracket.top() == "(")
				CpError("() is not matched.");
		}
	}
}
#pragma once

#include <vector>
#include "classes.hpp"
#include "operation.hpp"
#include "function.hpp"

namespace pl {

	auto RtExecute(std::vector<ParseTree>& parsedTree, std::map<std::string, pl::RtVar>& RtVars) -> void {
		for (size_t i = 0; i < parsedTree.size(); i++) {
			bool goDown = false;

			std::vector<RtData> commands = parsedTree[i].codes;
			std::stack<RtVar> RtStk;
			for (size_t i = 0; i < commands.size(); i++) {
				auto& now = commands[i];
				if (now.type == 3) { //const value
					RtStk.push(now.havingVar);
					continue;
				}
				else if (now.type == 5) { // param count
					continue;
				}
				else if (now.type == 1) { // operator
					operation(now.data, RtStk, RtVars);
					continue;
				}
				else if (now.type == 4) { // function
					function(now.data, RtStk, stoi(commands[i - 1].data), RtVars);
					continue;
				}
				else if (now.type == 2) { // variable
					RtStk.push(RtVars.find(now.data)->second);
					continue;
				}
			}

			if (goDown) {
				RtExecute(parsedTree[i].children, RtVars);
			}
		}
	}
}
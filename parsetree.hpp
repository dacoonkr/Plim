#pragma once

#include <vector>
#include "classes.hpp"

namespace pl {
	auto CpParseTree(std::vector<pl::RtData>& CpTokens, pl::ParseTree& parsedTree) -> void {
		std::vector<pl::RtData> tmp;
		for (size_t i = 0; i < CpTokens.size(); i++) {
			if (CpTokens[i].type == 1 && CpTokens[i].data == ";") {
				parsedTree.children.push_back(pl::ParseTree());
				for (auto& j : tmp) {
					parsedTree.children[parsedTree.children.size() - 1].codes.push_back(j);
				}
				tmp.clear();
				continue;
			}
			else tmp.push_back(CpTokens[i]);
		}
	}
}
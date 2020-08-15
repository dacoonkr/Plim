#pragma once

#include <vector>
#include "classes.hpp"

namespace pl {
	auto CpParseTree(std::vector<pl::RtData>& CpTokens, pl::ParseTree& parsedTree) -> void {
		parsedTree.children.push_back(pl::ParseTree());
		for (auto& j : CpTokens) {
			parsedTree.children[parsedTree.children.size() - 1].codes.push_back(j);
		}
		CpTokens.clear();
	}
}
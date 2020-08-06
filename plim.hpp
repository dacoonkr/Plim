#include <string>
#include "classes.hpp"
#include "tokens.hpp"
#include "parsetree.hpp"
#include "postfix.hpp"

std::vector<pl::RtData> CpTokens;
pl::ParseTree CpParsedTree;

namespace pl {
	auto plim_run(std::string this_line) -> void {
		CpParsedTree.name = "@workspace";
		CpParsedTree.codes.clear();
		CpParsedTree.children.clear();

		pl::CpSplitTokens(CpTokens, this_line);
		pl::CpParseTree(CpTokens, CpParsedTree);

		pl::CpPostFix(CpParsedTree.children);
	}
}
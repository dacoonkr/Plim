#include <string>
#include <map>
#include "classes.hpp"
#include "tokens.hpp"
#include "parsetree.hpp"
#include "postfix.hpp"
#include "run.hpp"

std::vector<pl::RtData> CpTokens;
std::map<std::string, pl::RtVar> RtVars;
pl::ParseTree CpParsedTree;

namespace pl {
	auto plim_run(std::string this_line) -> void {
		CpParsedTree.name = "@workspace";
		CpParsedTree.codes.clear();
		CpParsedTree.children.clear();

		pl::CpSplitTokens(CpTokens, this_line);
		pl::CpParseTree(CpTokens, CpParsedTree);

		pl::CpPostFix(CpParsedTree.children);

		pl::RtExecute(CpParsedTree.children, RtVars);
	}
}
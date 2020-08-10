#include <string>
#include <map>
#include "classes.hpp"
#include "tokens.hpp"
#include "parsetree.hpp"
#include "postfix.hpp"
#include "run.hpp"

std::map<std::string, pl::RtVar> RtVars;

namespace pl {
	auto plim_run(std::string this_line) -> void {
		std::vector<pl::RtData> CpTokens;
		pl::ParseTree CpParsedTree;

		CpParsedTree.name = "@workspace";
		CpParsedTree.codes.clear();
		CpParsedTree.children.clear();

		RtVars.insert(std::make_pair("void", RtVar(1, "0")));

		pl::CpSplitTokens(CpTokens, this_line);
		pl::CpParseTree(CpTokens, CpParsedTree);

		pl::CpPostFix(CpParsedTree.children);

		pl::RtExecute(CpParsedTree.children, RtVars);
	}
}
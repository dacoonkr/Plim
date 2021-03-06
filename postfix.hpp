#pragma once

#include <vector>
#include <stack>
#include <iostream>
#include "classes.hpp"
#include "priority.hpp"

namespace pl {
	auto CpClearOpratorStack(std::vector<pl::RtData>& CpPostfixing, std::stack<std::string>& CpOperator) -> void {
		while (!CpOperator.empty()) {
			if (CpOperator.top() == "(") return;
			if (CpOperator.top() == "{") return;
			CpPostfixing.push_back(RtData(1, CpOperator.top()));
			CpOperator.pop();
		}
	}

	auto CpPostFix(std::vector<pl::ParseTree>& parsedTree) -> void {
		for (size_t pst = 0; pst < parsedTree.size(); pst++) {
			auto& nowline = parsedTree[pst];
			std::vector<pl::RtData> CpPostfixing;
			std::stack<std::string> CpOperator;
			std::stack<size_t> CpParenthese;
			std::stack<size_t> CpBraces;

			for (size_t i = 0; i < nowline.codes.size(); i++) {
				auto& now = nowline.codes[i];

				if (now.type == 1) {
					if (now.data == ",") {
						size_t paramCnt = CpParenthese.top();
						CpParenthese.pop();
						CpParenthese.push(paramCnt + 1);
						CpClearOpratorStack(CpPostfixing, CpOperator);
					}
					else if (now.data == "{") {
						CpBraces.push(CpPostfixing.size());
						CpOperator.push("{");
					}
					else if (now.data == "}") {
						CpClearOpratorStack(CpPostfixing, CpOperator);
						RtVar commands(6, "<Commands>");
						size_t len = CpPostfixing.size() - CpBraces.top();
						size_t start = CpBraces.top();
						CpBraces.pop();
						for (size_t i = 0; i < len; i++) {
							commands.commands.push_back(CpPostfixing[start]);
							CpPostfixing.erase(CpPostfixing.begin() + start);
						}
						CpOperator.pop();
						CpPostfixing.push_back(RtData(3, commands));
					}
					else if (now.data == ";") {
						CpClearOpratorStack(CpPostfixing, CpOperator);
					}
					else if (now.data == "(") {
						CpOperator.push("(");
						CpParenthese.push(-1);
					}
					else if (now.data == ")") {
						size_t paramCnt = CpParenthese.top();
						CpParenthese.pop();

						if (paramCnt == -1) {
							CpClearOpratorStack(CpPostfixing, CpOperator);
							CpOperator.pop();
							continue;
						}

						CpClearOpratorStack(CpPostfixing, CpOperator);

						CpPostfixing.push_back(RtData(5, std::to_string(paramCnt)));

						CpOperator.pop();
						CpPostfixing.push_back(RtData(4, CpOperator.top()));
						CpOperator.pop();
					}
					else {
						while (true) {
							if (CpOperator.empty()) break;
							if (pl::priority(CpOperator.top()) >= pl::priority(now.data)) {
								CpPostfixing.push_back(RtData(1, CpOperator.top()));
								CpOperator.pop();
							}
							else break;
						}
						CpOperator.push(now.data);
						continue;
					}
				}
				else if (now.type == 4) {
					CpOperator.push(now.data);
					CpOperator.push("(");
					CpParenthese.push(1);
					i++;
				}
				else {
					CpPostfixing.push_back(now);
				}
			}
			CpClearOpratorStack(CpPostfixing, CpOperator);

			nowline.codes.clear();
			nowline.codes = CpPostfixing;
		}
	}
}
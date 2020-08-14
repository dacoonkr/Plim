#pragma once

#include <vector>
#include <string>
#include "classes.hpp"

char operators[] = { '(', ')', '+', '-', '*', '/', '^', ';', ',', '=', ':', '<', '>', '&', '|' };

std::string multiOperators[] = { "->", "==", "!=", "<=", ">=", "||", "&&", ">>", "<<" };

namespace pl {
	auto CpLastComplete(std::string CpNow, std::vector<pl::RtData>& CpTokens) -> void {
		if (CpNow.size() == 0) {
			CpNow.clear();
			return;
		}

		else if (CpNow[0] == '\"') {
			CpTokens.push_back(pl::RtData(3, pl::RtVar(3, CpNow.substr(1))));
			CpNow.clear();
			return;
		}

		else if ('0' <= CpNow[0] && CpNow[0] <= '9' || CpNow[0] == '-') {
			bool isFloat = false;
			for (auto& i : CpNow) {
				if (i == '.') {
					isFloat = true;
					break;
				}
			}
			if (isFloat) {
				CpTokens.push_back(pl::RtData(3, pl::RtVar(2, CpNow)));
			}
			else {
				CpTokens.push_back(pl::RtData(3, pl::RtVar(1, CpNow)));
			}
			CpNow.clear();
			return;
		}

		else {
			CpTokens.push_back(pl::RtData(2, CpNow));
			CpNow.clear();
		}
	}

	auto CpSplitTokens(std::vector<pl::RtData>& CpTokens, std::string this_line) -> void {
		std::string CpNow;
		bool isInStr = false;
		for (size_t i = 0; i < this_line.size(); i++) {
			if (this_line[i] == '\"') {
				if (isInStr) isInStr = false;
				else {
					isInStr = true;
					CpNow += this_line[i];
				}
				continue;
			}
			if (isInStr) {
				CpNow += this_line[i];
				continue;
			}
			if (this_line[i] == ' ' || this_line[i] == '\n') continue;
			else {
				bool isOperator = false;
				for (auto& j : operators) {
					if (this_line[i] == j) {
						isOperator = true;
						break;
					}
				}
				if (isOperator) {
					bool isMultiOperator = false;
					if (i != this_line.size() - 1) {
						for (auto& j : multiOperators) {
							if (this_line.substr(i, 2) == j) {
								if (CpNow.size() > 0) {
									pl::CpLastComplete(CpNow, CpTokens);
								}
								CpTokens.push_back(pl::RtData(1, j));
								i++;
								CpNow.clear();
								isMultiOperator = true;
								break;
							}
						}
					}
					if (isMultiOperator) continue;
					if (CpNow.size() > 0) {
						if (this_line[i] == '(')
							CpTokens.push_back(pl::RtData(4, CpNow));
						else pl::CpLastComplete(CpNow, CpTokens);
					}
					if (this_line[i] == ':') {
						CpNow = ':';
						continue;
					}
					std::string tmp;
					tmp += this_line[i];
					CpTokens.push_back(pl::RtData(1, tmp));
					CpNow.clear();
					continue;
				}
				else {
					CpNow += this_line[i];
					continue;
				}
			}
		}
		pl::CpLastComplete(CpNow, CpTokens);
	}
}
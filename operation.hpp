#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "classes.hpp"
#include "limit.hpp"

namespace pl {
	std::string dtos(double f) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(pl::limit::digit) << f;
		std::string s = ss.str();
		size_t point = s.find('.');
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);
		return (s[s.size() - 1] == '.') ? s.substr(0, s.size() - 1) : s;
	}

	auto operation(std::string oper, std::stack<RtVar>& RtStk, std::map<std::string, pl::RtVar>& RtVars) -> void {
		auto fValue = RtStk.top(); RtStk.pop();
		auto sValue = RtStk.top(); RtStk.pop();
		std::swap(fValue, sValue);

		if (oper == "+") {
			if (fValue.type == 3 && sValue.type == 3) {
				RtVar tmp(3, fValue.data + sValue.data);
				RtStk.push(tmp);
				return;
			}
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, std::to_string(stoi(fValue.data) + stoi(sValue.data)));
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, dtos(stod(fValue.data) + stod(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "-") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, std::to_string(stoi(fValue.data) - stoi(sValue.data)));
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, dtos(stod(fValue.data) - stod(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "*") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, std::to_string(stoi(fValue.data) * stoi(sValue.data)));
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, dtos(stod(fValue.data) * stod(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "/") {
			std::stringstream result;
			RtVar tmp(1, dtos(stod(fValue.data) / stod(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "->") {
			if (fValue.data.rfind("use", 0) == 0) {
				RtVar tmp(5, fValue.data + ':' + sValue.data);
				RtStk.push(tmp);
			}
			else {
				RtVar tmp(fValue.children[stod(sValue.data)]);
				RtStk.push(tmp);
			}
			return;
		}

		if (oper == "=") {
			if (fValue.data.rfind("alloc", 0) == 0) {
				RtVars.insert(make_pair(fValue.data.substr(5), sValue));
			}
			if (fValue.data.rfind("use", 0) == 0) {
				if (fValue.data.find(':') != fValue.data.npos) {
					RtVar* finded = nullptr;
					bool isFirst = true;
					std::string RtNow;
					for (int i = 3; i < fValue.data.length(); i++) {
						if (fValue.data[i] == ':') {
							if (isFirst) {
								isFirst = false;
								finded = &RtVars[RtNow];
							}
							else {
								if ('0' <= RtNow[0] && RtNow[0] <= '9')
									finded = &(finded->children[stod(RtNow)]);
								else finded = &(finded->member[RtNow]);
							}
							RtNow.clear();
						}
						else RtNow += fValue.data[i];
					}
					if (!RtNow.empty()) {
						if ('0' <= RtNow[0] && RtNow[0] <= '9')
							finded = &(finded->children[stod(RtNow)]);
						else finded = &(finded->member[RtNow]);
					}
					*finded = sValue;
				}
				else RtVars[fValue.data.substr(3)] = sValue;
			}
			return;
		}
	}
}
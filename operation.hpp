#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "classes.hpp"
#include "limit.hpp"
#include "memberPtr.hpp"

namespace pl {
	auto dtos(double f) -> std::string {
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
			RtVar tmp(2, dtos(stod(fValue.data) / stod(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "==") {
			RtVar tmp(1, (fValue.data == sValue.data && fValue.type == sValue.type) ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == "!=") {
			RtVar tmp(1, (fValue.data == sValue.data && fValue.type == sValue.type) ? "0" : "1");
			RtStk.push(tmp);
			return;
		}

		if (oper == "&&") {
			RtVar tmp(1, (fValue.data == "1" && sValue.data == "1") ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == "||") {
			RtVar tmp(1, (fValue.data == "1" || sValue.data == "1") ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == "&") {
			RtVar tmp(1, std::to_string(stoi(fValue.data) & stoi(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "|") {
			RtVar tmp(1, std::to_string(stoi(fValue.data) | stoi(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == ">>") {
			RtVar tmp(1, std::to_string(stoi(fValue.data) >> stoi(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "<<") {
			RtVar tmp(1, std::to_string(stoi(fValue.data) << stoi(sValue.data)));
			RtStk.push(tmp);
			return;
		}

		if (oper == "<") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, stoi(fValue.data) < stoi(sValue.data) ? "1" : "0");
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, stod(fValue.data) < stod(sValue.data) ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == ">") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, stoi(fValue.data) > stoi(sValue.data) ? "1" : "0");
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, stod(fValue.data) > stod(sValue.data) ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == "<=") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, stoi(fValue.data) <= stoi(sValue.data) ? "1" : "0");
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, stod(fValue.data) <= stod(sValue.data) ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == ">=") {
			if (fValue.type == 1 && sValue.type == 1) {
				RtVar tmp(1, stoi(fValue.data) >= stoi(sValue.data) ? "1" : "0");
				RtStk.push(tmp);
				return;
			}
			std::stringstream result;
			RtVar tmp(1, stod(fValue.data) >= stod(sValue.data) ? "1" : "0");
			RtStk.push(tmp);
			return;
		}

		if (oper == "->") {
			if (fValue.data.rfind("use", 0) == 0) {
				RtVar tmp;
				if (sValue.data.rfind("use", 0) == 0)
					tmp = RtVar(5, fValue.data + ':' + sValue.data.substr(3));
				else tmp = RtVar(5, fValue.data + ':' + sValue.data);
				RtStk.push(tmp);
			}
			else {
				RtVar tmp;
				if (sValue.data.rfind("use", 0) == 0)
					tmp = fValue.member[sValue.data.substr(3)];
				else if ('0' <= sValue.data[0] && sValue.data[0] <= '9')
					tmp = fValue.children[stoi(sValue.data)];
				else tmp = fValue.member[sValue.data];
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
					*getPtr(fValue.data, RtVars) = sValue;
				}
				else RtVars[fValue.data.substr(3)] = sValue;
			}
			return;
		}
	}
}
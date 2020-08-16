#pragma once

#include <vector>
#include "classes.hpp"
#include "operation.hpp"
#include "memberPtr.hpp"

namespace pl {
	auto function(std::string, std::stack<RtVar>&, int, std::map<std::string, pl::RtVar>&) -> void;

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
					pl::function(now.data, RtStk, stoi(commands[i - 1].data), RtVars);
					continue;
				}
				else if (now.type == 2) { // variable
					if (now.data.rfind("alloc", 0) == 0) {
						RtStk.push(RtVar(5, now.data));
						continue;
					}
					if (now.data.rfind("use", 0) == 0) {
						RtStk.push(RtVar(5, now.data));
						continue;
					}
					RtStk.push(RtVars.find(now.data)->second);
					continue;
				}
			}

			if (goDown) {
				RtExecute(parsedTree[i].children, RtVars);
			}
		}
	}

	auto getCommandsVar(RtVar commandsVar) -> std::vector<ParseTree> {
		std::vector<ParseTree> tmp;
		ParseTree tmp2;
		tmp2.codes = commandsVar.commands;
		tmp.push_back(tmp2);
		return tmp;
	}

	auto function(std::string func, std::stack<RtVar>& RtStk, int paramCnt, std::map<std::string, pl::RtVar>& RtVars) -> void {
		std::vector<RtVar> FcRtParams;
		for (int i = 0; i < paramCnt; i++) {
			FcRtParams.push_back(RtStk.top());
			RtStk.pop();
		}
		std::reverse(FcRtParams.begin(), FcRtParams.end());

		/* System Function */ {
			if (func == "exit") {
				exit(stoi(FcRtParams[0].data));
				return;
			}

			if (func == "out") {
				for (size_t i = 0; i < FcRtParams.size(); i++)
					std::cout << FcRtParams[i].data;
				return;
			}

			if (func == "Pack") {
				RtStk.push(RtVar(7, FcRtParams[0].data));
				return;
			}

			if (func == "execute") {
				auto tmp2 = getCommandsVar(FcRtParams[0]);
				RtExecute(tmp2, RtVars);
				return;
			}

			if (func == "repeat") {
				auto count = std::stoi(FcRtParams[0].data);
				for (int i = 0; i < count; i++) {
					auto tmp2 = getCommandsVar(FcRtParams[1]);
					RtExecute(tmp2, RtVars);
				}
				return;
			}

			if (func == "if") {
				if (FcRtParams[0].data != "0") {
					auto tmp2 = getCommandsVar(FcRtParams[1]);
					RtExecute(tmp2, RtVars);
				}
				return;
			}
		}

		/* package Con */ {
			if (func == ":printf") {
				auto& parent = RtStk.top();
				if (parent.type == 7 && parent.data == "ConIO") {
					for (size_t i = 0; i < FcRtParams.size(); i++) {
						std::cout << FcRtParams[i].data;
					}
					return;
				}
			}
		}

		/* package Array */ {
			if (func == "Array") {
				RtVar tmp(4, "<Array>");
				for (size_t i = 0; i < FcRtParams.size(); i++) {
					tmp.children.push_back(FcRtParams[i]);
				}
				RtStk.push(tmp);
				return;
			}

			/* Class Member Function */ {
				if (func == ":size") {
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						RtStk.push(RtVar(1, std::to_string(parent.children.size())));
						return;
					}
				}
				if (func == ":resize") {
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						while (parent.children.size() > (size_t)stoi(FcRtParams[0].data)) parent.children.pop_back();
						while (parent.children.size() < (size_t)stoi(FcRtParams[0].data)) parent.children.push_back(RtVar(1, "0"));
						return;
					}
				}
				if (func == ":print") {
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						std::cout << "[";
						for (size_t i = 0; i < parent.children.size(); i++) {
							std::cout << parent.children[i].data;
							if (i != parent.children.size() - 1) std::cout << ", ";
						}
						std::cout << "]";
						return;
					}
				}
			}
		}

		/* package Debug */ {
			if (func == "addMember") {
				auto* a = getPtr(FcRtParams[0].data, RtVars);
				std::pair<std::string, RtVar> b;
				if (FcRtParams[1].data.rfind("use", 0) == 0)
					b = make_pair(FcRtParams[1].data.substr(3), FcRtParams[2]);
				else b = make_pair(FcRtParams[1].data, FcRtParams[2]);
				a->member.insert(b);
			}
		}
	}
}
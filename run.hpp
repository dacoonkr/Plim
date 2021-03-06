#pragma once

#include <vector>
#include <map>
#include "classes.hpp"
#include "operation.hpp"
#include "memberPtr.hpp"
#include "error.hpp"

namespace pl {
	auto function(std::string, std::stack<RtVar>&, int, std::map<std::string, RtVar>&) -> void;

	auto RtExecute(std::vector<ParseTree>& parsedTree, std::map<std::string, RtVar>& RtVars) -> void {
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
				if (FcRtParams.size() != 1)
					RtError(ParameterRequireError("exit(int)", 1));
				if (FcRtParams[0].type != 1) {
					std::vector<std::string> params = { "int" };
					RtError(ParameterTypeError("exit(int)", params));
				}
				exit(stoi(FcRtParams[0].data));
				return;
			}

			if (func == "out") {
				for (size_t i = 0; i < FcRtParams.size(); i++)
					std::cout << FcRtParams[i].data;
				return;
			}

			if (func == "Pack") {
				if (FcRtParams.size() != 1)
					RtError(ParameterRequireError("Pack(string)", 1));
				if (FcRtParams[0].type != 3) {
					std::vector<std::string> params = { "string" };
					RtError(ParameterTypeError("Pack(string)", params));
				}
				RtStk.push(RtVar(7, FcRtParams[0].data));
				return;
			}

			if (func == "execute") {
				if (FcRtParams.size() != 1)
					RtError(ParameterRequireError("execute(<Commands>)", 1));
				if (FcRtParams[0].type != 6) {
					std::vector<std::string> params = { "<Commands>" };
					RtError(ParameterTypeError("execute(<Commands>)", params));
				}
				auto tmp2 = getCommandsVar(FcRtParams[0]);
				RtExecute(tmp2, RtVars);
				return;
			}

			if (func == "repeat") {
				if (FcRtParams.size() != 2)
					RtError(ParameterRequireError("repeat(int, <Commands>)", 2));
				if (FcRtParams[0].type != 1 || FcRtParams[1].type != 6) {
					std::vector<std::string> params = { "int", "<Commands>" };
					RtError(ParameterTypeError("repeat(int, <Commands>)", params));
				}
				auto count = std::stoi(FcRtParams[0].data);
				for (int i = 0; i < count; i++) {
					auto tmp2 = getCommandsVar(FcRtParams[1]);
					RtExecute(tmp2, RtVars);
				}
				return;
			}

			if (func == "if") {
				if (FcRtParams.size() != 2)
					RtError(ParameterRequireError("if(int, <Commands>)", 2));
				if (FcRtParams[0].type != 1 || FcRtParams[1].type != 6) {
					std::vector<std::string> params = { "int", "<Commands>" };
					RtError(ParameterTypeError("if(int, <Commands>)", params));
				}
				if (FcRtParams[0].data != "0") {
					auto tmp2 = getCommandsVar(FcRtParams[1]);
					RtExecute(tmp2, RtVars);
				}
				return;
			}
		}

		/* package ConIO */ {
			if (func == ":print") {
				auto& parent = RtStk.top();
				if (parent.type == 7 && parent.data == "ConIO") {
					for (size_t i = 0; i < FcRtParams.size(); i++) {
						std::cout << FcRtParams[i].data;
					}
					return;
				}
			}

			if (func == ":printf") {
				auto& parent = RtStk.top();
				if (parent.type == 7 && parent.data == "ConIO") {
					if (FcRtParams.size() < 1)
						RtError(ParameterRequireError("ConIO:printf(string, anytype...)", 2));
					if (FcRtParams[0].type != 3) {
						std::vector<std::string> params = { "string", "..." };
						RtError(ParameterTypeError("ConIO:printf(string, anytype...)", params));
					}
					int got = 0;
					for (size_t i = 0; i < FcRtParams[0].data.length(); i++) {
						if (FcRtParams[0].data[i] == '%') {
							if (FcRtParams[0].data[i + 1] == '%') {
								std::cout << "%";
							}
							else if (FcRtParams[0].data[i + 1] == 'r') {
								auto arr = FcRtParams[++got].children;
								std::cout << "[";
								for (int i = 0; i < arr.size(); i++) {
									std::cout << arr[i].data;
									if (i != arr.size() - 1) std::cout << ", ";
								}
								std::cout << "]";
							}
							else if (FcRtParams[0].data[i + 1] == 'c') {
								auto classes = FcRtParams[++got];
								std::cout << "<" << classes.data;
								for (auto it = classes.member.begin(); it != classes.member.end(); ++it) {
									std::cout << " " << it->first << "=" << it->second.data;
								}
								std::cout << ">";
							}
							else if (FcRtParams[0].data[i + 1] == 'v') {
								std::cout << FcRtParams[++got].data;
							}
							i++;
						}
						else std::cout << FcRtParams[0].data[i];
					}
					return;
				}
			}

			if (func == ":scanf") {
				auto& parent = RtStk.top();
				if (parent.type == 7 && parent.data == "ConIO") {
					if (FcRtParams.size() < 1)
						RtError(ParameterRequireError("ConIO:scanf(string, use anytype...)", 2));
					if (FcRtParams[0].type != 3) {
						std::vector<std::string> params = { "string", "..." };
						RtError(ParameterTypeError("ConIO:scanf(string, use anytype...)", params));
					}
					int got = 0;
					for (size_t i = 0; i < FcRtParams[0].data.length(); i++) {
						if (FcRtParams[0].data[i] == '%') {
							if (FcRtParams[0].data[i + 1] == 'i') {
								auto* want = getPtr(FcRtParams[++got].data, RtVars);
								want->type = 1;
								std::cin >> want->data;
							}
							else if (FcRtParams[0].data[i + 1] == 'f') {
								auto* want = getPtr(FcRtParams[++got].data, RtVars);
								want->type = 2;
								std::cin >> want->data;
							}
							else if (FcRtParams[0].data[i + 1] == 's') {
								auto* want = getPtr(FcRtParams[++got].data, RtVars);
								want->type = 3;
								std::cin >> want->data;
							}
							i++;
						}
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
					if (FcRtParams.size() != 1)
						RtError(ParameterRequireError("<Array>:resize(int)", 1));
					if (FcRtParams[0].type != 1) {
						std::vector<std::string> params = { "int" };
						RtError(ParameterTypeError("<Array>:resize(int)", params));
					}
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						while (parent.children.size() > (size_t)stoi(FcRtParams[0].data)) parent.children.pop_back();
						while (parent.children.size() < (size_t)stoi(FcRtParams[0].data)) parent.children.push_back(RtVar(1, "0"));
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
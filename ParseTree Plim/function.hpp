#pragma once

#include <algorithm>
#include <iostream>

namespace pl {
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
		}

		/* package Con */ {
			if (func == "print") {
				for (int i = 0; i < FcRtParams.size(); i++) {
					std::cout << FcRtParams[i].data;
				}
				return;
			}
		}

		/* package Array */ {
			if (func == "Array") {
				RtVar tmp(4, "<Array>");
				for (int i = 0; i < FcRtParams.size(); i++) {
					tmp.children.push_back(FcRtParams[i]);
				}
				RtStk.push(tmp);
				return;
			}

			/* Class Member Function */ {
				if (func == ":size") {
					auto& parent = RtStk.top();
					RtStk.push(RtVar(1, std::to_string(parent.children.size())));
					return;
				}
				if (func == ":resize") {
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						while (parent.children.size() > stod(FcRtParams[0].data)) parent.children.pop_back();
						while (parent.children.size() < stod(FcRtParams[0].data)) parent.children.push_back(RtVar(1, "0"));
					}
					return;
				}
				if (func == ":print") {
					auto& parent = RtStk.top();
					if (parent.type == 4) {
						std::cout << "[";
						for (int i = 0; i < parent.children.size(); i++) {
							std::cout << parent.children[i].data;
							if (i != parent.children.size() - 1) std::cout << ", ";
						}
						std::cout << "]";
					}
					return;
				}

				if (func == ":append") {
					auto& parent = RtStk.top();
					return;
				}
			}
		}
	}
}
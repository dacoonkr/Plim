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

		if (func == "print") {
			for (int i = 0; i < FcRtParams.size(); i++) {
				std::cout << FcRtParams[i].data;
			}
			return;
		}
		if (func == "make_array") {
			RtVar tmp(4, "");
			for (int i = 0; i < FcRtParams.size(); i++) {
				tmp.children.push_back(FcRtParams[i]);
			}
			RtStk.push(tmp);
			return;
		}
	}
}
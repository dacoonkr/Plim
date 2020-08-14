#pragma once

#include <string>
#include <map>
#include "classes.hpp"

namespace pl {
	auto getPtr(std::string name, std::map<std::string, pl::RtVar>& RtVars) -> RtVar* {
		RtVar* finded = nullptr;
		bool isFirst = true;
		std::string RtNow;
		for (size_t i = 3; i < name.length(); i++) {
			if (name[i] == ':') {
				if (isFirst) {
					isFirst = false;
					finded = &RtVars[RtNow];
				}
				else {
					if ('0' <= RtNow[0] && RtNow[0] <= '9')
						finded = &(finded->children[stoi(RtNow)]);
					else finded = &(finded->member[RtNow]);
				}
				RtNow.clear();
			}
			else RtNow += name[i];
		}
		if (!RtNow.empty()) {
			if (isFirst) {
				isFirst = false;
				finded = &RtVars[RtNow];
			}
			else {
				if ('0' <= RtNow[0] && RtNow[0] <= '9')
					finded = &(finded->children[stoi(RtNow)]);
				else finded = &(finded->member[RtNow]);
			}
		}
		return finded;
	}
}
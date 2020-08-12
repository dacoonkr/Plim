#pragma once

#include <string>
#include <vector>

namespace pl {
	class RtVar {
	public:
		int type = 0; // int: 1  float: 2  string: 3  array: 4  keyword: 5
		std::string data;

		std::vector<pl::RtVar> children;
		std::map<std::string, pl::RtVar> member;

		RtVar(int pr_type, std::string pr_data) {
			type = pr_type;
			data = pr_data;
		}

		RtVar() {
			type = 0;
		}
	};

	class RtData {
	public:
		int type = 0; // operator: 1  variable: 2  const: 3  function: 4  paramCnt: 5
		std::string data;
		pl::RtVar havingVar = pl::RtVar(1, "0");

		RtData(int pr_type, std::string pr_data) {
			type = pr_type;
			data = pr_data;
		}

		RtData(int pr_type, pl::RtVar pr_data) {
			type = pr_type;
			havingVar = pr_data;
		}
	};

	class ParseTree {
	public:
		std::string name;

		std::vector<RtData> codes;
		std::vector<pl::ParseTree> children;
	};
}
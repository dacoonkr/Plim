#pragma once

#include <string>

namespace pl {
	auto priority(std::string RtOperator) -> short {
		if (RtOperator == "->") return 18;
		if (RtOperator == "*") return 17;
		if (RtOperator == "/") return 17;
		if (RtOperator == "+") return 16;
		if (RtOperator == "-") return 16;
		if (RtOperator == "=") return 15;
		return -1;
	}
}
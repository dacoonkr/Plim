#pragma once

#include <string>

namespace pl {
	auto priority(std::string RtOperator) -> short {
		if (RtOperator == "->") return 19;

		if (RtOperator == "|") return 18;
		if (RtOperator == "&") return 18;
		if (RtOperator == ">>") return 18;
		if (RtOperator == "<<") return 18;

		if (RtOperator == "*") return 17;
		if (RtOperator == "/") return 17;

		if (RtOperator == "+") return 16;
		if (RtOperator == "-") return 16;

		if (RtOperator == "==") return 15;
		if (RtOperator == "!=") return 15;
		if (RtOperator == "<=") return 15;
		if (RtOperator == ">=") return 15;
		if (RtOperator == "<") return 15;
		if (RtOperator == ">") return 15;

		if (RtOperator == "&&") return 14;

		if (RtOperator == "||") return 13;

		if (RtOperator == "=") return 12;
		return -1;
	}
}
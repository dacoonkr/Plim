#pragma once

int priority(char ch) {
	switch (ch) {
	case '^':
		return 0x7fffffff - 15;
	case '*': case '/': case '%':
		return 0x7fffffff - 16;
	case '+': case '-':
		return 0x7fffffff - 17;
	case '=': case ':':
		return 0x7fffffff - 18;
	case '==': case '!=': case '<=': case '>=': case '<': case '>':
		return 0x7fffffff - 19;
	case '&&':
		return 0x7fffffff - 20;
	case '||':
		return 0x7fffffff - 21;
	default:
		return -1;
	}
}
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
using namespace std;

class Data {
public:
	int type = 1; // 0:Keyword  1:Function  2:Variable  3:String  4:Number  5:ParamCnt
	string data;
};
class Variable {
public:
	int type = 1; // 1:String  2:Number
	string data;
};

char keyWords[] = { '(',')',',','+','-','/','*','=' };
string types[6] = { "Keyword : ", "Function: ", "Variable: ", "String  : ", "Number  : ", "ParamCnt:" };

vector<Data> tokens;
vector<Data> postfixed;

stack<Data> runtime;
map<string, Variable> runtimeVariable;

string code;
string now;

int main() {
	while (cout << ">> ", cin >> code) {
		void splitTokens();
		void postfix();
		void run();
		now = "";

		splitTokens();
		postfix();
		run();

		for (int i = 0; i < runtime.size(); i++) {
			cout << types[runtime.top().type] << runtime.top().data << endl;
			runtime.pop();
		}

		tokens.clear();
		postfixed.clear();
		while (!runtime.empty()) runtime.pop();
	}
}

void run() {
	for (int i = 0; i < postfixed.size(); i++) {
		if (postfixed[i].type == 3 || postfixed[i].type == 4) {
			runtime.push(postfixed[i]);
		}
		else if (postfixed[i].type == 2) {
			Data tmp;
			tmp.data = runtimeVariable[postfixed[i].data].data;
			tmp.type = runtimeVariable[postfixed[i].data].type + 2;
			runtime.push(tmp);
		}
		else if (postfixed[i].type == 0) {
			Data a = runtime.top(); runtime.pop();
			Data b = runtime.top(); runtime.pop();
			swap(a, b);
			Data tmp;
			stringstream number_to_string;
			switch (postfixed[i].data[0]) {
			case '+':
				if (a.type == 3 || b.type == 3) {
					tmp.type = 3;
					tmp.data = a.data + b.data;
					runtime.push(tmp);
				}
				else if (a.type == 4 || b.type == 4) {
					tmp.type = 4;
					number_to_string << fixed << setprecision(15) << stod(a.data) + stod(b.data);
					tmp.data = number_to_string.str();
					while (tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.')
						tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
					runtime.push(tmp);
				}
				break;
			case '-':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) - stod(b.data);
				tmp.data = number_to_string.str();
				while (tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.')
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case '*':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) * stod(b.data);
				tmp.data = number_to_string.str();
				while (tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.')
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case '/':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) / stod(b.data);
				tmp.data = number_to_string.str();
				while (tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.')
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			}
		}
	}
}

void postfix() {
	int priority(char);
	stack<string> keyWordStack;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].type == 0) {
			if (tokens[i].data == ",") {
				while (!keyWordStack.empty()) {
					if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') break;
					if (keyWordStack.top() == ",") break;
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed.push_back(tmp);
					keyWordStack.pop();
				}
				keyWordStack.push(",");
				continue;
			}
			else if (tokens[i].data == "(") {
				continue;
			}
			else if (tokens[i].data == ")") {
				int paramcnt = 1;
				while (1) {
					if (keyWordStack.empty()) break;
					else if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') {
						Data tmp;
						tmp.data = keyWordStack.top().substr(0, keyWordStack.top().length() - 1);
						tmp.type = 1;
						postfixed.push_back(tmp);
						keyWordStack.pop();
						tmp.data = to_string(paramcnt);
						tmp.type = 5;
						postfixed.push_back(tmp);
						break;
					}
					else if (keyWordStack.top() == ",") {
						paramcnt++;
						keyWordStack.pop();
					}
					else {
						Data tmp;
						tmp.data = keyWordStack.top();
						tmp.type = 0;
						postfixed.push_back(tmp);
						keyWordStack.pop();
					}
				}
			}
			else {
				while (1) {
					if (keyWordStack.empty()) break;
					else if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') {
						break;
					}
					else if (keyWordStack.top() == ",") {
						break;
					}
					else if (priority(keyWordStack.top()[0]) < priority(tokens[i].data[0])) {
						break;
					}
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed.push_back(tmp);
					keyWordStack.pop();
				}
				keyWordStack.push(tokens[i].data);
			}
		}
		else if (tokens[i].type == 1) {
			keyWordStack.push(tokens[i].data + "(");
		}
		else {
			postfixed.push_back(tokens[i]);
		}
	}
	while (!keyWordStack.empty()) {
		Data tmp;
		tmp.data = keyWordStack.top();
		tmp.type = 0;
		postfixed.push_back(tmp);
		keyWordStack.pop();
	}
}

int priority(char ch) {
	switch (ch) {
	case '*': case '/':
		return 0x7fffffff;
	case '+': case '-':
		return 0x7fffffff - 1;
	case ':':
		return 0x7fffffff - 2;
	}
}

void splitTokens() {
	bool isInStr = false;
	for (int i = 0; code[i] != '\0'; i++) {
		if (code[i] == '\"') {
			isInStr = isInStr ? false : true;
			if (!isInStr) continue;
		}
		if (isInStr) {
			now += code[i];
		}
		else {
			bool isKeyWord = false;
			for (int j = 0; j < sizeof(keyWords); j++) {
				if (keyWords[j] == code[i]) {
					isKeyWord = true;
					break;
				}
			}
			if (isKeyWord) {
				if (now != "") {
					Data tmp;
					if (now[0] == '\"') {
						tmp.data = now.substr(1);
						tmp.type = 3;
					}
					else if (code[i] == '(') {
						tmp.data = now;
						tmp.type = 1;
					}
					else if ('-' == now[0] || ('0' <= now[0] && now[0] <= '9')) {
						tmp.data = now;
						tmp.type = 4;
					}
					else {
						tmp.data = now;
						tmp.type = 2;
					}
					now = "";
					tokens.push_back(tmp);
				}
				Data tmp;
				tmp.data = code[i];
				tmp.type = 0;
				tokens.push_back(tmp);
			}
			else {
				now += code[i];
			}
		}
	}
	if (now != "") {
		Data tmp;
		if (now[0] == '\"') {
			tmp.data = now.substr(1);
			tmp.type = 3;
		}
		else if ('-' == now[0] || ('0' <= now[0] && now[0] <= '9')) {
			tmp.data = now;
			tmp.type = 4;
		}
		else {
			tmp.data = now;
			tmp.type = 2;
		}
		tokens.push_back(tmp);
	}
}
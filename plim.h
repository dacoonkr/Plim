#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include "error.h"
#include "priority.h"
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

char keyWords[] = { '(',')',',','+','-','/','*','=','%','^',':',';' };
string types[6] = { "Keyword : ", "Function: ", "Variable: ", "String  : ", "Number  : ", "ParamCnt:" };

vector<Data> tokens;
vector<Data> postfixed;

stack<Data> runtime;
map<string, Variable> runtimeVariable;

string code;
string now;

void compile_and_run(string codes) {
	void compile();
	void run();
	void load();

	code = codes;
	now = "";

	compile();

	load();
	run();
	cout << '\n';

	tokens.clear();
	postfixed.clear();
	while (!runtime.empty()) runtime.pop();
}

void compile() {
	void splitTokens();
	void postfix();
	splitTokens();
	postfix();
	ofstream output("code.plm", ios::out | ios::binary);
	int tmp = (int)postfixed.size();
	output.write((char*)&tmp, sizeof(int));
	for (int i = 0; i < postfixed.size(); i++) {
		int type = postfixed[i].type;
		output.write((char*)&type, sizeof(int));
		int length = postfixed[i].data.length();
		output.write((char*)&length, sizeof(int));
		for (int j = 0; j < length; j++) {
			output.write(&postfixed[i].data[j], sizeof(char));
		}
	}
	output.close();
	postfixed.clear();
}

void run() {
	void error(string, string);
	void load();
	load();
	for (int i = 0; i < postfixed.size(); i++) {
		if (postfixed[i].type == 3 || postfixed[i].type == 4) {
			runtime.push(postfixed[i]);
		}
		else if (postfixed[i].data[0] == ';') {
			while (!runtime.empty()) runtime.pop();
		}
		else if (postfixed[i].type == 2 && postfixed[i].data[0] != '$') {
			Data tmp;
			tmp.data = runtimeVariable[postfixed[i].data].data;
			tmp.type = runtimeVariable[postfixed[i].data].type + 2;
			runtime.push(tmp);
		}
		else if (postfixed[i].type == 2) {
			Data tmp;
			tmp.data = postfixed[i].data;
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
					while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
						tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
					runtime.push(tmp);
				}
				break;
			case '-':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) - stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case '*':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) * stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case '/':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) / stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case '%':
				tmp.type = 4;
				tmp.data = to_string(stoi(a.data) % stoi(b.data));
				runtime.push(tmp);
				break;
			case '^':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << pow(stod(a.data), stod(b.data));
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime.push(tmp);
				break;
			case ':':
				if (a.data == "$new") {
					Variable tmp2;
					tmp2.data = "0";
					tmp2.type = 2;
					runtimeVariable.insert(make_pair(b.data.substr(1), tmp2));
					tmp.type = 2;
					tmp.data = b.data;
					runtime.push(tmp);
				}
				break;
			case '=':
				Variable tmp2;
				tmp2.data = b.data;
				tmp2.type = b.type - 2;
				runtimeVariable[a.data.substr(1)] = tmp2;
				tmp.type = b.type;
				tmp.data = b.data;
				runtime.push(tmp);
				break;
			}
		}
		else if (postfixed[i].type == 1) {
			stack<Data> tmparam;
			vector<Data> parameter;
			int paramCnt = stoi(runtime.top().data);
			runtime.pop();
			for (int j = 0; j < paramCnt; j++) {
				tmparam.push(runtime.top());
				runtime.pop();
			}
			for (int j = 0; j < paramCnt; j++) {
				parameter.push_back(tmparam.top());
				tmparam.pop();
			}

			if (postfixed[i].data == "exit") {
				if (paramCnt != 1) error(postfixed[i].data, pl_1000);
				if (parameter[0].type != 4) error(postfixed[i].data, pl_1001);
				exit(stoi(parameter[0].data));
			}
			if (postfixed[i].data == "system") {
				if (paramCnt != 1) error(postfixed[i].data, pl_1000);
				if (parameter[0].type != 3) error(postfixed[i].data, pl_1001);
				system(parameter[0].data.c_str());
			}
			if (postfixed[i].data == "print") {
				for (int m = 0; m < parameter.size(); m++) {
					cout << parameter[m].data;
				}
			}
			break;
		}
		else if (postfixed[i].type == 5) {
			runtime.push(postfixed[i]);
		}
	}
}

void load() {
	ifstream output("code.plm", ios::out | ios::binary);
	int s;
	output.read((char*)&s, sizeof(int));
	for (int i = 0; i < s; i++) {
		Data tmp;

		int type;
		output.read((char*)&type, sizeof(int));
		tmp.type = type;

		int length;
		output.read((char*)&length, sizeof(int));

		char buffer[10005]; int bufferlen = 0;
		for (int j = 0; j < length; j++) {
			char tmp;
			output.read(&tmp, sizeof(char));
			buffer[bufferlen++] = tmp;
		}
		buffer[bufferlen] = 0;
		tmp.data += buffer;
		postfixed.push_back(tmp);
	}
	output.close();
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
			else if (tokens[i].data == ";") {
				while (!keyWordStack.empty()) {
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed.push_back(tmp);
					keyWordStack.pop();
				}
				Data tmp;
				tmp.data = ";";
				tmp.type = 0;
				postfixed.push_back(tmp);
			}
			else if (tokens[i].data == "(") {
				keyWordStack.push("(");
				continue;
			}
			else if (tokens[i].data == ")") {
				while (!keyWordStack.empty()) {
					if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') break;
					if (keyWordStack.top() == ",") break;
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed.push_back(tmp);
					keyWordStack.pop();
				}
				int paramcnt = 1;
				while (1) {
					if (keyWordStack.empty()) break;
					else if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') {
						if (keyWordStack.top() != "(") {
							Data tmp;
							tmp.data = to_string(paramcnt);
							tmp.type = 5;
							postfixed.push_back(tmp);
							tmp.data = keyWordStack.top().substr(0, keyWordStack.top().length() - 1);
							tmp.type = 1;
							postfixed.push_back(tmp);
						}
						keyWordStack.pop();
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
			i++;
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
		else if (code[i] == ' ') continue;
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

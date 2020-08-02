#pragma once

#include <string>
#include <vector>
#include <stack>
#include "classes.h"
#include "syntax_checker.h"
using namespace std;

char keyWords[] = { '(',')',',','+','-','/','*','=','%','^',':',';','\n','}','{','|','&','!','<','>' };

int splitTK(bool showError, string code, vector<Data>* tokens);

void splitTokens(string code, vector<Data>* tokens) {
	splitTK(true, code, tokens);
}
int OrsplitTokens(string code, vector<Data>* tokens) {
	return splitTK(false, code, tokens);
}

int splitTK(bool showError, string code, vector<Data>* tokens) {
	string now;
	bool isInStr = false;
	for (int i = 0; code[i] != '\0'; i++) {
		if (code[i] == '\"') {
			isInStr = isInStr ? false : true;
			if (!isInStr) continue;
		}
		if (isInStr) {
			if (code[i] == '\\') {
				if (code[i + 1] == '\\')
					now += code[i], i++;
				else if (code[i + 1] == 'n')
					now += '\n', i++;
			}
			else now += code[i];
			continue;
		}
		else if (code[i] == ' ') {
			continue;
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
				if (code[i] == '\n') continue;
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
						bool isnumber = true;
						for (int j = 0; j < now.length(); j++) {
							if (!('0' <= now[j] && now[j] <= '9')) {
								isnumber = false;
								break;
							}
						}
						if (!isnumber) { 
							if (showError) error(now, sy_1003);
							else return 1;
						}
						tmp.data = now;
						tmp.type = 4;
					}
					else {
						tmp.data = now;
						tmp.type = 2;
					}
					now = "";
					tokens->push_back(tmp);
				}

				if (code[i] == '{') {
					Data tmp;
					tmp.data = "{";
					tmp.type = 6;
					tokens->push_back(tmp);
					continue;
				}
				else if (code[i] == '}') {
					Data tmp;
					tmp.data = "}";
					tmp.type = 6;
					tokens->push_back(tmp);
					continue;
				}
				else if (code[i] == '=' && code[i + 1] == '=') {
					Data tmp;
					tmp.data = "==";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				else if (code[i] == '!' && code[i + 1] == '=') {
					Data tmp;
					tmp.data = "!=";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				else if (code[i] == '!' && code[i + 1] == '(') {
					Data tmp;
					tmp.data = "!";
					tmp.type = 1;
					tokens->push_back(tmp);
					continue;
				}
				else if (code[i] == '<' && code[i + 1] == '=') {
					Data tmp;
					tmp.data = "<=";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				else if (code[i] == '>' && code[i + 1] == '=') {
					Data tmp;
					tmp.data = ">=";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				else if (code[i] == '&' && code[i + 1] == '&') {
					Data tmp;
					tmp.data = "&&";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				else if (code[i] == '|' && code[i + 1] == '|') {
					Data tmp;
					tmp.data = "||";
					tmp.type = 0;
					tokens->push_back(tmp);
					i++;
					continue;
				}
				Data tmp;
				tmp.data = code[i];
				tmp.type = 0;
				tokens->push_back(tmp);
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
			bool isnumber = true;
			for (int j = 0; j < now.length(); j++) {
				if (!(('0' <= now[j] && now[j] <= '9') || now[j] == '.')) {
					isnumber = false;
					break;
				}
			}
			if (!isnumber) {
				if (showError) error(now, sy_1003);
				else return 1;
			}
			tmp.data = now;
			tmp.type = 4;
		}
		else {
			tmp.data = now;
			tmp.type = 2;
		}
		now = "";
		tokens->push_back(tmp);
	}
	return syntax_check(tokens, showError);
}

void postfix(vector<Data>* tokens, vector<Data> *postfixed) {
	int priority(char);
	stack<string> keyWordStack;
	for (size_t i = 0; i < tokens->size(); i++) {
		if (tokens->at(i).type == 0) {
			if (tokens->at(i).data == ",") {
				while (!keyWordStack.empty()) {
					if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') break;
					if (keyWordStack.top() == ",") break;
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed->push_back(tmp);
					keyWordStack.pop();
				}
				keyWordStack.push(",");
				continue;
			}
			else if (tokens->at(i).data == "{") {
				Data tmp;
				tmp.data = "{";
				tmp.type = 6;
				postfixed->push_back(tmp);
			}
			else if (tokens->at(i).data == "}") {
				while (!keyWordStack.empty()) {
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed->push_back(tmp);
					keyWordStack.pop();
				}
				Data tmp;
				tmp.data = "}";
				tmp.type = 6;
				postfixed->push_back(tmp);
			}
			else if (tokens->at(i).data == ";") {
				while (!keyWordStack.empty()) {
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed->push_back(tmp);
					keyWordStack.pop();
				}
				Data tmp;
				tmp.data = ";";
				tmp.type = 0;
				postfixed->push_back(tmp);
			}
			else if (tokens->at(i).data == "(") {
				keyWordStack.push("(");
				continue;
			}
			else if (tokens->at(i).data == ")") {
				while (!keyWordStack.empty()) {
					if (keyWordStack.top()[keyWordStack.top().length() - 1] == '(') break;
					if (keyWordStack.top() == ",") break;
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed->push_back(tmp);
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
							postfixed->push_back(tmp);
							tmp.data = keyWordStack.top().substr(0, keyWordStack.top().length() - 1);
							tmp.type = 1;
							postfixed->push_back(tmp);
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
						postfixed->push_back(tmp);
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
					else if (keyWordStack.top()[0] == '^' && tokens->at(i).data[0] == '^') break;
					else if (priority(keyWordStack.top()[0]) < priority(tokens->at(i).data[0])) {
						break;
					}
					Data tmp;
					tmp.data = keyWordStack.top();
					tmp.type = 0;
					postfixed->push_back(tmp);
					keyWordStack.pop();
				}
				keyWordStack.push(tokens->at(i).data);
			}
		}
		else if (tokens->at(i).type == 1) {
			keyWordStack.push(tokens->at(i).data + "(");
			i++;
		}
		else {
			postfixed->push_back(tokens->at(i));
		}
	}
	while (!keyWordStack.empty()) {
		Data tmp;
		tmp.data = keyWordStack.top();
		tmp.type = 0;
		postfixed->push_back(tmp);
		keyWordStack.pop();
	}
}
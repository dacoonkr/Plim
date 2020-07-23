#pragma once

#include <vector>
#include <stack>
#include <string>
#include <map>
#include "error.h"
#include "classes.h"
using namespace std;

void run(stack<Data>* runtime, vector<Data>* postfixed, map<string, Variable>* runtimeVariable) {
	for (size_t i = 0; i < postfixed->size(); i++) {
		if (postfixed->at(i).type == 3 || postfixed->at(i).type == 4) {
			runtime->push(postfixed->at(i));
		}
		else if (postfixed->at(i).data[0] == ';') {
			while (!runtime->empty()) runtime->pop();
		}
		else if (postfixed->at(i).type == 2 && postfixed->at(i).data[0] != '$') {
			if (postfixed->at(i).data == "scanline") {
				Data tmp;
				getline(cin, tmp.data);
				tmp.type = 3;
				runtime->push(tmp);
			}
			else if (postfixed->at(i).data == "scanint") {
				Data tmp;
				int tmp2;
				if (cin >> tmp2) {
					tmp.data = to_string(tmp2);
					tmp.type = 4;
					runtime->push(tmp);
				}
				else error(postfixed->at(i).data, pl_1002);
			}
			else if (postfixed->at(i).data == "scanfloat") {
				stringstream number_to_string;
				Data tmp;
				double tmp2;
				if (cin >> tmp2) {
					tmp.data = to_string(tmp2);
					tmp.type = 4;
					number_to_string << fixed << setprecision(15) << tmp2;
					tmp.data = number_to_string.str();
					while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
						tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
					runtime->push(tmp);
				}
				else error(postfixed->at(i).data, pl_1003);
			}
			else {
				if (runtimeVariable->find(postfixed->at(i).get_data()) == runtimeVariable->end()) {
					error(postfixed->at(i).get_data(), pl_1005);
				}
				else {
					Data tmp;
					tmp.data = runtimeVariable->find(postfixed->at(i).data)->second.data;
					tmp.type = runtimeVariable->find(postfixed->at(i).data)->second.type + 2;
					runtime->push(tmp);
				}
			}
		}
		else if (postfixed->at(i).type == 2) {
			Data tmp;
			tmp.data = postfixed->at(i).data;
			runtime->push(tmp);
		}
		else if (postfixed->at(i).type == 0) {
			Data a = runtime->top(); runtime->pop();
			Data b = runtime->top(); runtime->pop();
			swap(a, b);
			Data tmp;
			stringstream number_to_string;
			switch (postfixed->at(i).data[0]) {
			case '+':
				if (a.type == 3 || b.type == 3) {
					tmp.type = 3;
					tmp.data = a.data + b.data;
					runtime->push(tmp);
				}
				else if (a.type == 4 || b.type == 4) {
					tmp.type = 4;
					number_to_string << fixed << setprecision(15) << stod(a.data) + stod(b.data);
					tmp.data = number_to_string.str();
					while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
						tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
					runtime->push(tmp);
				}
				break;
			case '-':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) - stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime->push(tmp);
				break;
			case '*':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) * stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime->push(tmp);
				break;
			case '/':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << stod(a.data) / stod(b.data);
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime->push(tmp);
				break;
			case '%':
				tmp.type = 4;
				tmp.data = to_string(stoi(a.data) % stoi(b.data));
				runtime->push(tmp);
				break;
			case '^':
				tmp.type = 4;
				number_to_string << fixed << setprecision(15) << pow(stod(a.data), stod(b.data));
				tmp.data = number_to_string.str();
				while ((tmp.data[tmp.data.length() - 1] == '0' || tmp.data[tmp.data.length() - 1] == '.') && tmp.data.find('.') != tmp.data.npos)
					tmp.data = tmp.data.substr(0, tmp.data.length() - 1);
				runtime->push(tmp);
				break;
			case ':':
				if (a.data == "$new") {
					Variable tmp2;
					tmp2.data = "0";
					tmp2.type = 2;
					runtimeVariable->insert(make_pair(b.data.substr(1), tmp2));
					tmp.type = 2;
					tmp.data = b.data;
					runtime->push(tmp);
				}
				break;
			case '=':
				Variable tmp2;
				tmp2.data = b.data;
				tmp2.type = b.type - 2;
				runtimeVariable->find(a.data.substr(1))->second = tmp2;
				tmp.type = b.type;
				tmp.data = b.data;
				runtime->push(tmp);
				break;
			}
		}
		else if (postfixed->at(i).type == 1) {
			stack<Data> tmparam;
			vector<Data> parameter;
			int paramCnt = stoi(runtime->top().data);
			runtime->pop();
			for (int j = 0; j < paramCnt; j++) {
				tmparam.push(runtime->top());
				runtime->pop();
			}
			for (int j = 0; j < paramCnt; j++) {
				parameter.push_back(tmparam.top());
				tmparam.pop();
			}

			if (postfixed->at(i).data == "exit") {
				if (paramCnt != 1) error(postfixed->at(i).data, pl_1000);
				if (parameter[0].type != 4) error(postfixed->at(i).data, pl_1001);
				exit(stoi(parameter[0].data));
			}
			else if (postfixed->at(i).data == "system") {
				if (paramCnt != 1) error(postfixed->at(i).data, pl_1000);
				if (parameter[0].type != 3) error(postfixed->at(i).data, pl_1001);
				system(parameter[0].data.c_str());
			}
			else if (postfixed->at(i).data == "print") {
				for (size_t m = 0; m < parameter.size(); m++) {
					cout << parameter[m].data;
				}
			}
			else error(postfixed->at(i).data, pl_1004);
		}
		else if (postfixed->at(i).type == 5) {
			runtime->push(postfixed->at(i));
		}
	}
}

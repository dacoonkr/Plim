#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "classes.h"
#include "error.h"
using namespace std;

void syntax_check(vector<Data> *tokens) {
	void bracket(vector<Data>*);
	bracket(tokens);
	return;
};

void bracket(vector<Data>* tokens) {
	stack<string> bracket_st;
	for (int i = 0; i < tokens->size(); i++) {
		if (tokens->at(i).get_data() == "(") bracket_st.push("(");
		if (tokens->at(i).get_data() == ")") {
			if (i > 0) {
				if (tokens->at(i - 1).get_data() == "(") error("()", sy_1002);
			}
			if (bracket_st.empty()) {
				error(")", sy_1000);
			}
			else if (bracket_st.top() == "(") {
				bracket_st.pop();
			}
			else {
				error(")", sy_1000);
			}
		}
	}
	if(!bracket_st.empty())
		error("¼Ò½º", sy_1001);
}
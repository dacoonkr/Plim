#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "classes.h"
#include "error.h"
using namespace std;

int syntax_check(vector<Data> *tokens, bool showError) {
	int bracket(vector<Data>*, bool showError);

	int a = bracket(tokens, showError);
	return a;
};

int bracket(vector<Data>* tokens, bool showError) {
	stack<string> bracket_st;
	for (int i = 0; i < tokens->size(); i++) {
		if (tokens->at(i).get_data() == "(") bracket_st.push("(");
		if (tokens->at(i).get_data() == ")") {
			if (i > 0) {
				if (tokens->at(i - 1).get_data() == "(") { 
					if (showError) error("()", sy_1002);
					else return 1;
				}
			}
			if (bracket_st.empty()) {
				if (showError) error(")", sy_1000);
				else return 1;
			}
			else if (bracket_st.top() == "(") {
				bracket_st.pop();
			}
			else {
				if (showError) error(")", sy_1000);
				else return 1;
			}
		}
	}
	if(!bracket_st.empty())
		if (showError) error("¼Ò½º", sy_1001);
		else return 1;
	return 0;
}
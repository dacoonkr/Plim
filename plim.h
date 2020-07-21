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
#include "compile.h"
#include "classes.h"
#include "load.h"
#include "run.h"
using namespace std;


string types[6] = { "Keyword : ", "Function: ", "Variable: ", "String  : ", "Number  : ", "ParamCnt:" };

vector<Data> tokens;
vector<Data> postfixed;

stack<Data> runtime;
map<string, Variable> runtimeVariable;

string code;

void compile_and_run(string codes) {
	code = codes;

	compile(code, &postfixed, &tokens);
	plmLoad(&postfixed);

	run(&runtime, &postfixed, &runtimeVariable);
	cout << '\n';

	tokens.clear();
	postfixed.clear();
	while (!runtime.empty()) runtime.pop();
}

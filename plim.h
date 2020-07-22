#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <time.h>
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
	clock_t start, end;
	start = clock();

	code = codes;
	string output("code.plm");

	compile(code, &postfixed, &tokens, output);
	plmLoad(&postfixed, output);

	run(&runtime, &postfixed, &runtimeVariable);
	cout << '\n';

	tokens.clear();
	postfixed.clear();
	while (!runtime.empty()) runtime.pop();

	end = clock();
	cout << "Done. " << end - start << "ms\n";
}

void compile_(string codes, string output) {
	clock_t start, end;
	start = clock();

	code = codes;

	compile(code, &postfixed, &tokens, output);

	tokens.clear();
	postfixed.clear();
	while (!runtime.empty()) runtime.pop();

	end = clock();
	cout << "Done. " << end - start << "ms\n";
}

void run_(string output) {
	clock_t start, end;
	start = clock();

	plmLoad(&postfixed, output);
	run(&runtime, &postfixed, &runtimeVariable);
	cout << '\n';
	tokens.clear();
	postfixed.clear();
	while (!runtime.empty()) runtime.pop();

	end = clock();
	cout << "Done. " << end - start << "ms\n";
}
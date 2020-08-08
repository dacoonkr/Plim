#pragma once

#include <map>
#include <string>
#include <fstream>
#include "classes.h"
using namespace std;

void save_Vars(map<string, Variable> *runtimeVariable, string outout) {
	ofstream output(outout, ios::out | ios::binary);
	for (int i = 0; i < runtimeVariable->size(); i++) {

	}
};
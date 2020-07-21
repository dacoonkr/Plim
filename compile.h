#pragma once

#include <fstream>
#include <vector>
#include "classes.h"
using namespace std;

void compile(vector<Data>* postfixed) {
	void splitTokens();
	void postfix();
	splitTokens();
	postfix();
	ofstream output("code.plm", ios::out | ios::binary);
	int tmp = (int)postfixed->size();
	output.write((char*)&tmp, sizeof(int));
	for (size_t i = 0; i < postfixed->size(); i++) {
		int type = postfixed->at(i).get_type();
		output.write((char*)&type, sizeof(int));
		int length = postfixed->at(i).get_data().length();
		output.write((char*)&length, sizeof(int));
		for (int j = 0; j < length; j++) {
			output.write(&(postfixed->at(i).get_data()[j]), sizeof(char));
		}
	}
	output.close();
	postfixed->clear();
}
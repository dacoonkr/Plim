#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "classes.h"
using namespace std;


void plmLoad(vector<Data> *postfixed, string outout) {
	ifstream output(outout, ios::out | ios::binary);
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
		postfixed -> push_back(tmp);
	}
	output.close();
}
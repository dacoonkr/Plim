#pragma once

#include <string>
using namespace std;

class Data {
public:
	int type = 1; // 0:Keyword  1:Function  2:Variable  3:String  4:Number  5:ParamCnt
	string data;

	int get_type() {
		return type;
	}
	string get_data() {
		return data;
	}
};

class Variable {
public:
	int type = 1; // 1:String  2:Number
	string data;
};

#pragma once

#include <string>
using namespace std;

class Data {
public:
	int type = 1; // 0:Keyword  1:Function  2:Variable  3:String  4:Number  5:ParamCnt  6:Brace
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
	bool isConst = false;
	string data;
};

class Pointer {
public:
	int pointer = 0;
};

class BlockHead {
public:
	string headtype;
	int returnPoint;
};
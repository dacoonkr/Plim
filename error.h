#pragma once

#include <string>
using namespace std;

#define pl_1000 "함수 인수가 너무 많거나 부족합니다."
#define pl_1001 "함수 인수의 타입이 맞지 않습니다."

void error(string run, string a) {
	cout << "에러 발생: " << run << "에서 " << a << "\n";
	exit(0);
}
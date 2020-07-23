#pragma once

#include <string>
using namespace std;

#define pl_1000 "함수 인수가 너무 많거나 부족합니다."
#define pl_1001 "함수 인수의 타입이 맞지 않습니다."
#define pl_1002 "정수 값이 입력되지 않았습니다."
#define pl_1003 "실수 값이 입력되지 않았습니다."
#define pl_1004 "함수를 찾을 수 없습니다."
#define pl_1005 "변수를 찾을 수 없습니다."

#define sy_1000 "괄호 짝을 찾을 수 없습니다."
#define sy_1001 "닫히지 않은 괄호가 남아있습니다."
#define sy_1002 "빈 괄호가 있습니다."
#define sy_1003 "알 수 없는 값이 있습니다."

void error(string run, string a) {
	cout << "에러 발생: \"" << run << "\"에서 " << a << "\n";
	exit(0);
}
#pragma once

#include <string>
using namespace std;

#define pl_1000 "�Լ� �μ��� �ʹ� ���ų� �����մϴ�."
#define pl_1001 "�Լ� �μ��� Ÿ���� ���� �ʽ��ϴ�."
#define pl_1002 "���� ���� �Էµ��� �ʾҽ��ϴ�."
#define pl_1003 "�Ǽ� ���� �Էµ��� �ʾҽ��ϴ�."
#define pl_1004 "�Լ��� ã�� �� �����ϴ�."
#define pl_1005 "������ ã�� �� �����ϴ�."

#define sy_1000 "��ȣ ¦�� ã�� �� �����ϴ�."
#define sy_1001 "������ ���� ��ȣ�� �����ֽ��ϴ�."
#define sy_1002 "�� ��ȣ�� �ֽ��ϴ�."
#define sy_1003 "�� �� ���� ���� �ֽ��ϴ�."

void error(string run, string a) {
	cout << "���� �߻�: \"" << run << "\"���� " << a << "\n";
	exit(0);
}
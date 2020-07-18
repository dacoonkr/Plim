#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Data {
public:
	int type = 1; // 0:Keyword  1:Function  2:Variable  3:String  4:Number
	string data;
};

char keyWords[] = { '(',')',',','+','-','/','*' };
string types[5] = { "Keyword : ", "Function: ", "Variable: ", "String  : ", "Number  : " };

vector<Data> tokens;

string code;
string now;

int main() {
	while (cin >> code) {
		void splitTokens();
		splitTokens();
	}
}

void splitTokens() {
	bool isInStr = false;
	for (int i = 0; code[i] != '\0'; i++) {
		if (code[i] == '\"') {
			isInStr = isInStr ? false : true;
			if (!isInStr) continue;
		}
		if (isInStr) {
			now += code[i];
		}
		else {
			bool isKeyWord = false;
			for (int j = 0; j < sizeof(keyWords); j++) {
				if (keyWords[j] == code[i]) {
					isKeyWord = true;
					break;
				}
			}
			if (isKeyWord) {
				if (now != "") {
					Data tmp;
					if (now[0] == '\"') {
						tmp.data = now.substr(1);
						tmp.type = 3;
					}
					else if (code[i] == '(') {
						tmp.data = now;
						tmp.type = 1;
					}
					else if ('-' == now[0] || ('0' <= now[0] && now[0] <= '9')) {
						tmp.data = now;
						tmp.type = 4;
					}
					else {
						tmp.data = now;
						tmp.type = 2;
					}
					now = "";
					tokens.push_back(tmp);
				}
				Data tmp;
				tmp.data = code[i];
				tmp.type = 0;
				tokens.push_back(tmp);
			}
			else {
				now += code[i];
			}
		}
	}
	if (now != "") {
		Data tmp;
		if (now[0] == '\"') {
			tmp.data = now.substr(1);
			tmp.type = 3;
		}
		else if ('-' == now[0] || ('0' <= now[0] && now[0] <= '9')) {
			tmp.data = now;
			tmp.type = 4;
		}
		else {
			tmp.data = now;
			tmp.type = 2;
		}
	}
}
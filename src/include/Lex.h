#pragma once

#include "basic.h"

char Keywords[10][20] = { "main","int","return","char","double","while","for","if","else","then" };
enum TokenType
{
	START = 0,
	MAIN, INT, RETURN, CHAR, DOUBLE, WHILE, FOR, IF, ELSE, THEN,
	ID,
	NUM,
	ADD, SUB, MUL, DIV, EVAL, EQU, NEQ, MOER, LESS, MOEREQU, LESSEQU,
	PERIOD, COLON, LB, RB, LC, RC, JH
};
TokenType tokenType;

struct SymbolTable
{
	int value;
	string name;
}symbolTables[MAX];
int cnt = 0;

int isLetter(char ch) {
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}

int isDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}

string chartoString(char ch) {
	string str = "";
	str = str + ch;
	return str;
}

void lex(FILE* fp) {
	char ch;
	ch = fgetc(fp);
	//cout << ch << endl;
	while (ch != EOF) {
		if (ch == '/') {
			ch = fgetc(fp);
			if (ch == '*') {
				ch = fgetc(fp);
				char save = ch;
				ch = fgetc(fp);
				while (save != '*' || ch != '/') {
					save = ch;
					ch = fgetc(fp);
				}
				ch = fgetc(fp);
			}
			else if (ch == '/') {
				ch = fgetc(fp);
				while (ch != '\n') {
					ch = fgetc(fp);
				}
			}
		}
		if (isLetter(ch)) {  //ch为字母，分析其是否为标识符或是保留字
			int i = 0;
			string word;
			word += ch;
			ch = fgetc(fp);
			while (isLetter(ch) || isDigit(ch)) {
				word += ch;
				ch = fgetc(fp);
			}
			int flag = 0; //记录字符是否为保留字
			for (int j = 0; j < 10; j++) {
				if (word == Keywords[j]) {
					flag = 1;
					symbolTables[cnt] = { j + 1,word };
					cnt++;
				}
			}
			if (flag == 0) {
				symbolTables[cnt] = { ID,word };
				cnt++;
			}
		}
		if (isDigit(ch)) {
			string digit;
			digit += ch;
			ch = fgetc(fp);
			int point = 0;
			while (isDigit(ch) || (ch=='.'&& point==0)) {
				if (ch == '.') {
					point = 1;
				}
				digit += ch;
				ch = fgetc(fp);
			}
			symbolTables[cnt] = { NUM,digit };
			cnt++;

		}
		if (ch == '+') {
			symbolTables[cnt] = { ADD,chartoString(ch) };
			cnt++;
		}
		if (ch == '-') {
			symbolTables[cnt] = { SUB,chartoString(ch) };
			cnt++;
		}
		if (ch == '*') {
			symbolTables[cnt] = { MUL,chartoString(ch) };
			cnt++;
		}
		if (ch == '/') {
			symbolTables[cnt] = { DIV,chartoString(ch) };
			cnt++;
		}
		if (ch == '=') {
			char save = ch;
			ch = fgetc(fp);
			if (ch == '=') {
				symbolTables[cnt] = { EQU,chartoString(save) + ch };
				cnt++;
			}
			else {
				symbolTables[cnt] = { EVAL,chartoString(save) };
				cnt++;
				continue;
			}
		}
		if (ch == '!') {
			char save = ch;
			ch = fgetc(fp);
			if (ch == '=') {
				symbolTables[cnt] = { NEQ,chartoString(save) + ch };
				cnt++;
			}
			else {
				continue;
			}
		}
		if (ch == '>') {
			char save = ch;
			ch = fgetc(fp);
			if (ch == '=') {
				symbolTables[cnt] = { MOEREQU,chartoString(save) + ch };
				cnt++;
			}
			else {
				symbolTables[cnt] = { MOER,chartoString(ch) };
				cnt++;
				continue;
			}
		}
		if (ch == '<') {
			char save = ch;
			ch = fgetc(fp);
			if (ch == '=') {
				symbolTables[cnt] = { LESSEQU,chartoString(save) + ch };
				cnt++;
			}
			else {
				symbolTables[cnt] = { LESS,chartoString(ch) };
				cnt++;
				continue;
			}
		}
		if (ch == ',') {
			symbolTables[cnt] = { PERIOD,chartoString(ch) };
			cnt++;
		}
		if (ch == ';') {
			symbolTables[cnt] = { COLON,chartoString(ch) };
			cnt++;
		}
		if (ch == '{') {
			symbolTables[cnt] = { LB,chartoString(ch) };
			cnt++;
		}
		if (ch == '}') {
			symbolTables[cnt] = { RB,chartoString(ch) };
			cnt++;
		}
		if (ch == '(') {
			symbolTables[cnt] = { LC,chartoString(ch) };
			cnt++;
		}
		if (ch == ')') {
			symbolTables[cnt] = { RC,chartoString(ch) };
			cnt++;
		}
		if (ch == '#') {
			symbolTables[cnt] = { JH,chartoString(ch) };
			cnt++;
		}
		if (ch == ' ') {
			ch = fgetc(fp);
			continue;
		}
		ch = fgetc(fp);
	}

}


#pragma once
#include "basic.h"
#include "Lex.h"
#include "SqStack.h"

TokenType E_First[MAX] = { LC,ID,NUM },
E2_First[MAX] = { ADD,SUB },
T_First[MAX] = { LC,ID,NUM },
T2_First[MAX] = { MUL,DIV },
F_First[MAX] = { LC,ID,NUM };

TokenType E_Follow[MAX] = { RC,JH },
E2_Follow[MAX] = { RC,JH },
T_Follow[MAX] = { ADD,SUB,JH },
T2_Follow[MAX] = { ADD,SUB,JH },
F_Follow[MAX] = { ADD,SUB,MUL,DIV,JH };

string Vn[5] = { "E","E'","T","T'","F" };
string Vt[9] = { "id","num","+","-","*","/","(",")","#" };
string str[11] = { "error","TE'","+TE'","—TE'","ε","FT'","*FT'","/FT'","(E)","id","num" };

int table[5][9] = { {1,1,0,0,0,0,1,0,0},   //预测分析表
					{0,0,2,3,0,0,0,4,4},
					{5,5,0,0,0,0,5,0,0},
					{0,0,4,4,6,7,0,4,4},
					{9,10,0,0,0,0,8,0,0} };

/* 1、E->TE'   0、error
*  2、E'->+TE'
*  3、E'->—TE'
*  4、ε //只出栈
*  5、T->FT'
*  6、T'->*FT' 
*  7、T'-> /FT'
*  8、F->(E)
*  9、F->id
*  10、F->num
*/

/*读取字符*/
int ip = 0;
string advance() {  //读取字符队列中的单词
	return symbolTables[ip].name;
}
int advance_value() {  //读取字符队列中的单词
	return symbolTables[ip].value;
}

int find_index(string x, string a,int value) {
	int index_x = 0, index_a = 0;
	for (int i = 0; i < 5; i++) {
		if (x == Vn[i]) {
			index_x = i;
			break;
		}
	}
	if (value == 11) {
		index_a = 0;
	}
	if (value == 12) {
		index_a = 1;
	}
	for (int i = 2; i < 9; i++) {
		if (a == Vt[i]) {
			index_a = i;
			break;
		}
	}
	return table[index_x][index_a];
}

void Push_expr(SqStack<string>*& st,string x, string a,int value) { //从分析表中替换产生式
	int index = find_index(x, a, value);
	switch (index)
	{
	case 0:cout << "错误的表达式" << endl; exit(0);
	case 1:Push(st, string("E'")); Push(st, string("T")); break;
	case 2:Push(st, string("E'")); Push(st, string("T")); Push(st, string("+")); break;
	case 3:Push(st, string("E'")); Push(st, string("T")); Push(st, string("-")); break;
	case 4:break;
	case 5:Push(st, string("T'")); Push(st, string("F")); break;
	case 6:Push(st, string("T'")); Push(st, string("F")); Push(st, string("*")); break;
	case 7:Push(st, string("T'")); Push(st, string("F")); Push(st, string("/")); break;
	case 8:Push(st, string(")")); Push(st, string("E")); Push(st, string("(")); break;
	case 9:Push(st, string("id")); break;
	case 10:Push(st, string("num")); break;
	}
}


void Parsing_V2() {
	string x, a;
	SqStack<string> *st;  //创建分析栈
	InitStack(st);
	Push(st, string("#")); //先将#进栈
	Push(st, string("E"));
	bool flag = true;
	while (flag) {
		a = advance();
		Pop(st, x);//"E","E'","T","T'","F"
		if (x == "E" || x == "E'" || x == "T" || x == "T'" || x == "F") { //x为非终结符
			Push_expr(st, x, a, advance_value()); //分析表，替换产生式
		}
		else if (advance_value() == 11 && x == "id") {	//匹配，下一个字符
			ip++;
			continue;
		}
		else if (advance_value() == 12 && x == "num") {
			ip++;
			continue;
		}
		else if (a == x) {
			if (a == x && a == "#") {
				flag = false;
			}
			ip++;
			continue;
		}
	}
	if (flag == false) {
		cout << "正确表达式" << endl;
	}
}




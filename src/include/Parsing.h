#pragma once

#include "basic.h"
#include "Lex.h"

/*	创建文法G(E)中非终结符的FIRST集合
	E->TE'
	E'->+TE' | —TE' |ε
	T->FT'
	T'->*FT' | /FT' |ε
	F->(E) | id | num   
	id: ID
	num: NUM
	(: LC
	): RC
	+: ADD
	-: SUB
	*: MUL
	/: DIV
*/

TokenType E_First[MAX] = { LC,ID,NUM },
E2_First[MAX] = { ADD,SUB },
T_First[MAX] = { LC,ID,NUM },
T2_First[MAX] = { MUL,DIV },
F_First[MAX] = { LC,ID,NUM },
ysf[MAX] = { ADD, SUB, MUL, DIV, EVAL, EQU, NEQ, MOER, LESS, MOEREQU, LESSEQU },
fh[MAX] = { PERIOD, COLON, LB, RB, LC,RC };

int isFirst(TokenType first[], int num) {
	for (int i = 0; i < MAX; i++) {
		if (num == first[i]&& first[i]!=first[199]) {
			return 1;
		}
	}
	return 0;
}

/*各个非终结符的子程序*/
int ip = -1;
int advance() {
	return symbolTables[ip].value;
}


void E();
void E2();
void T();
void T2();
void F();

void E() {
	T();
	E2();
}

void E2() {
	if (isFirst(E2_First,advance())) {
		ip++;
		T();
		E2();
	}
}

void T() {
	F();
	T2();
}

void T2() {
	if (isFirst(T2_First, advance())) {
		ip++;
		F();
		T2();
	}
}

void F() {
	if (advance()==LC) {
		ip++;
		E();
		if (advance() == RC) {
			ip++;
		}
		else {
			ip--;
			cout << symbolTables[ip].name << "后缺少右括号。" << endl;
			exit(0);
		}
	}
	else if (advance() == ID) {
		ip++;
	}
	else if (advance() == NUM) {
		ip++;
	}
	else {
		if (isFirst(ysf, advance())) {
			cout << symbolTables[ip].name << "前缺少运算数。" << endl;
			exit(0);
		}
		else if (isFirst(fh, advance())) {
			cout << symbolTables[ip].name << "为异常符号。" << endl;
			exit(0);
		}
	}
}

void Parsing() {
	ip++;
	E();
	if (advance() == JH ) {
		ip--;
		if (isFirst(ysf, advance())) {
			cout << symbolTables[ip].name << "后缺少运算数。" << endl;
		}
		else {
			cout << "正确的表达式。" << endl;
		}
			
	}
	else if (isFirst(fh, advance())) {
		cout << symbolTables[ip].name << "为异常符号。" << endl;
	}
	else{
		cout << "需要在表达式结尾加上#。" << endl;
	}
}









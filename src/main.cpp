#include "include/basic.h"
#include "include/Lex.h"
#include "include/Parsing.h"
#include "include/Parsing_v2.h"
#include "include/Parsing_SLR.h"



int main() {
	FILE* fp = NULL;
	fp = fopen("D:\\College\\大三上\\编译原理\\实验\\lab2\\test.txt", "r");
	lex(fp);   //词法分析
	//Parsing();  //递归下降分析器
	Parsing_V2(); //预测分析法语法分析器
	//Parsing_SLR(); //SLR语法分析器
	return 0;
}
#include "include/basic.h"
#include "include/Lex.h"
#include "include/Parsing.h"
#include "include/Parsing_v2.h"
#include "include/Parsing_SLR.h"



int main() {
	FILE* fp = NULL;
	fp = fopen("D:\\College\\������\\����ԭ��\\ʵ��\\lab2\\test.txt", "r");
	lex(fp);   //�ʷ�����
	//Parsing();  //�ݹ��½�������
	Parsing_V2(); //Ԥ��������﷨������
	//Parsing_SLR(); //SLR�﷨������
	return 0;
}
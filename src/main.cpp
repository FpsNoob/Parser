#include "include/basic.h"
#include "include/Lex.h"
#include "include/Parsing.h"



int main() {
	FILE* fp = NULL;
	fp = fopen("C:\\Users\\TANGNI\\Desktop\\编译原理实验二\\test2.txt", "r");
	lex(fp);   //词法分析
	//for (int i = 0; i < cnt; i++) {
	//	cout << "(" << symbolTables[i].value << ", " << symbolTables[i].name << ")" << endl;
	//}
	//fclose(fp);
	//ofstream fout;
	//fout.open("C:\\Users\\TANGNI\\Desktop\\编译原理实验二\\save.txt");
	//for (int i = 0; i < cnt; i++) {
	//	fout << "( " << symbolTables[i].value << ", " << symbolTables[i].name << ")" << endl;
	//}
	//fout.close();
	Parsing();  //递归下降分析器
	return 0;
}
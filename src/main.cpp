#include "include/basic.h"
#include "include/Lex.h"
#include "include/Parsing.h"



int main() {
	FILE* fp = NULL;
	fp = fopen("C:\\Users\\TANGNI\\Desktop\\����ԭ��ʵ���\\test2.txt", "r");
	lex(fp);   //�ʷ�����
	//for (int i = 0; i < cnt; i++) {
	//	cout << "(" << symbolTables[i].value << ", " << symbolTables[i].name << ")" << endl;
	//}
	//fclose(fp);
	//ofstream fout;
	//fout.open("C:\\Users\\TANGNI\\Desktop\\����ԭ��ʵ���\\save.txt");
	//for (int i = 0; i < cnt; i++) {
	//	fout << "( " << symbolTables[i].value << ", " << symbolTables[i].name << ")" << endl;
	//}
	//fout.close();
	Parsing();  //�ݹ��½�������
	return 0;
}
//#pragma once
//#include "basic.h"
//#include "Lex.h"
//#include "SqStack.h"
//
//string state[17] = { "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f","g" };
//string Vt[12] = { "id","num","+","-","*","/","(",")","#" ,"E","T","F" };
//string css[10] = { "S->E","E->E+T","E->E-T","E->T","T->T*F","T->T/F","T->F","F->(E)","F->i","F->n" };//����ʽ�ĳ���
//string now = ""; //��¼��ǰ״̬
//
//string table[17][12] = { {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e2", "e1", "1", "2", "3"},
//						 {"e3", "e3", "s7", "s8", "0", "0", "e3", "e2", "acc", "0", "0", "0"},
//						 {"e3", "e3", "r3", "r3", "s9", "sa", "e3", "r3", "r3", "0", "0", "0"},
//						 {"e3", "e3", "r6", "r6", "r6", "r6", "e3", "r6", "r6", "0", "0", "0"},
//						 {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e1", "e1", "b", "2", "3"},
//						 {"0", "0", "r8", "r8", "r8", "r8", "e3", "r8", "r8", "0", "0", "0"},
//						 {"e3", "0", "r9", "r9", "r9", "r9", "e3", "r9", "r9", "0", "0", "0"},
//						 {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e1", "e1", "0", "c", "3"},
//						 {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e1", "e1", "0", "d", "3"},
//						 {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e1", "e1", "0", "0", "e"},
//						 {"s5", "s6", "e1", "e1", "e1", "e1", "s4", "e1", "e1", "0", "0", "f"},
//						 {"e3", "e3", "s7", "s8", "0", "0", "e3", "sg", "e4", "0", "0", "0"},
//						 {"e3", "e3", "r1", "r1", "s9", "sa", "e3", "r1", "r1", "0", "0", "0"},
//						 {"e3", "e3", "r2", "r2", "s9", "sa", "e3", "r2", "r2", "0", "0", "0"},
//						 {"e3", "e3", "r4", "r4", "r4", "r4", "e3", "r4", "r4", "0", "0", "0"},
//						 {"e3", "e3", "r5", "r5", "r5", "r5", "e3", "r5", "r5", "0", "0", "0"},
//						 {"r7", "r7", "r7", "r7", "r7", "r7", "r7", "r7", "r7", "0", "0", "0"} };
//
///*��ȡ�ַ�*/
//int ip = 0;
//string advance() {  //��ȡ�ַ������еĵ���
//	return symbolTables[ip].name;
//}
//int advance_value() {  //��ȡ�ַ������еĵ���
//	return symbolTables[ip].value;
//}
//
//int string_int(string str) {
//	char ch = str[1];
//	//cout << ch << endl;
//	int ans = ch - '0';
//	if (ans > 16) {
//		ans -= 39;
//	}
//	return ans;
//}
//
//
//string find_index(string s, string a,int value) {
//	int index_x = 0, index_a = 0;
//	for (int i = 0; i < 17; i++) {
//		if (s == state[i]) {
//			index_x = i;
//			break;
//		}
//	}
//	if (value == 11) {
//		index_a = 0;
//	}
//	if (value == 12) {
//		index_a = 1;
//	}
//	for (int i = 2; i < 12; i++) {
//		if (a == Vt[i]) {
//			index_a = i;
//			break;
//		}
//	}
//	return table[index_x][index_a];
//}
//
//int action_goto(string s, string a, int value) {
//	now = find_index(s, a, value);
//	string action = now.substr(0, 1);
//	if (action == "0") {
//		return 0;
//	}
//	else if (action == "s") { //�ƽ�
//		return 1;
//	}
//	else if (action == "r") { //��Լ
//		return 2;
//	}
//	else if (action == "a") { //����
//		return 3;
//	}
//	else if (action == "e") { //����
//		return 4;
//	}
//	else {  //ת��
//		return 5;
//	}
//}
//
//void Parsing_SLR() {
//	SqStack<string>* st;
//	InitStack(st);
//	Push(st, string("0"));	//��״̬0��ջ
//	string s;
//	string a;
//	bool flag = true;
//	bool ok = false;
//	while (flag) {
//		GetTop(st, s); //��ջջ��״̬
//		a = advance();
//		int res = action_goto(s, a, advance_value());
//		switch (res) {
//		case 0:cout << "�ձ�" << endl; exit(0); //��������
//		case 1:Push(st, a); Push(st, now.substr(1, 1)); ip++; break; //�ƽ�
//		case 2:
//			for(int j=0;j<2*(css[string_int(now)].length()-3);j++){
//				Pop(st, s);
//			}
//			GetTop(st, s);
//			Push(st, css[string_int(now)].substr(0, 1));//����ʽ�������ջ
//			action_goto(s, css[string_int(now)].substr(0, 1), 0); //��ù�ͨ���
//			Push(st, now);//goto�����ջ
//			break;
//		case 3:flag = false; ok = true; break; //����
//		case 4:flag = false; ok = false; break;//����
//		}
//	}
//	if (ok == true) {
//		cout << "��ȷ�ı��ʽ" << endl;
//	}
//	else {
//		cout << "����ı��ʽ" << endl;
//	}
//}
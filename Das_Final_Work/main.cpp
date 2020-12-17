#include<iostream>
#include<fstream>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<iterator>
#include"HuffMan.h"
using namespace std;

int main() {
	ifstream fin1("source.txt", ios::in);
	ofstream fout1("CharNum.txt", ios::out);
	ofstream fout2("SortedCharNum.txt", ios::out);
	ofstream fout3("CharCode.txt", ios::out);
	ofstream fout4("encode.txt", ios::out);
	ofstream fout5("decode.txt", ios::out);


	//b)ͳ��source.txt�ļ��и��ַ��ĳ��ִ������漰���ļ���ͳ���ַ������������Ѹ����ַ������ֵĸ���д��CharNum.txt�ļ��С�
	char ch;
	unordered_map<char, int> ump;
	unordered_map<char, int>::iterator iter;
	while (fin1.get(ch))
	{
		int flag = 0;
		for (iter = ump.begin(); iter != ump.end(); iter++)
		{
			if (iter->first == ch)
			{
				iter->second++;
				flag = 1;
				break;
			}
		}
		if (flag == 0) ump.insert(make_pair(ch, 1));
	}
	for (iter = ump.begin(); iter != ump.end(); iter++)
	{
		fout1 << iter->first << "\t" << iter->second << endl;
	}
	cout << "ͳ���ַ������ɹ���" << endl;

	//c)�Ѹ����ַ������ִ��������������������浽SortedCharNum.txt�ļ��С�
	vector<pair<char, int>> tmp;
	for (auto& i : ump)
	{
		tmp.push_back(i);
	}
	sort(tmp.begin(), tmp.end(),
		[=](pair<char, int>& a, pair<char, int>& b) { return a.second > b.second; });//tmp�Ѿ���second���Ӵ�С�Ź�����
	vector<pair<char, int>>::iterator iter2;
	for (iter2 = tmp.begin(); iter2 != tmp.end(); iter2++)
	{
		fout2 << iter2->first << "\t" << iter2->second << endl;
	}
	cout << "����ɹ���" << endl;

	//d)���ļ��е��ַ����й��������룬���洢���ַ�����CharCode.txt�ļ��С�
	map<char, int> m;//�ڲ��Զ����򣬲��Ҳ��������ظ�Ԫ��
	for (iter2 = tmp.begin(); iter2 != tmp.end(); iter2++)//tmp�������ٰ����ŵ�map�У���Ҫ��Ϊʲô��
	{
		m[iter2->first] = iter2->second;
	}

	int n = m.size();

	HuffmanTree tree = new Node[2 * n];
	HuffmanCode code = new Code[n + 1];

	initTree(tree, code, m, n);
	createHuffmanTree(tree, n);
	HuffCode(tree, code, n);

	for (int i = 1; i <= n; i++)
	{
		fout3 << code[i].data << "\t" << code[i].code << endl;
	}
	cout << "HuffMan����ɹ���" << endl;

	//e)�����ַ������ļ�����source.txt�ı��ļ����ݽ��б��룬�������洢��encode.txt�ļ��С�
	map<char, string> codefile1;//�����ַ��ͱ���
	for (int i = 1; i <= n; i++)
	{
		codefile1[code[i].data] = code[i].code;
	}
	ifstream fin2("source.txt", ios::in);//���´��ļ�
	while (fin2.get(ch))
	{
		fout4 << codefile1[ch];
	}
	cout << "���ı��ļ�����ɹ���" << endl;

	//f)����CharCode.txt�ļ��е��ַ����룬���ѱ�����ļ�encode.txt���н��룬����֮��洢��decode.txt�ļ��С�
	//�д��Ż�
	fin1.close();
	fin2.close();
	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	ifstream fin3("encode.txt", ios::in);//���´��ļ�

	//map<char, string>::iterator iter3;

	//vector<pair<char, string>> codefile2;
	//for (auto& i : codefile1)
	//{
	//	codefile2.push_back(i);
	//}

	//vector<pair<char, string>>::iterator iter4;
	//string s = "";
	//while (fin3.get(ch))
	//{
	//	s += ch;
	//	cout << s;
	//	for (iter4 = codefile2.begin(); iter4 != codefile2.end(); iter4++)
	//	{
	//		if (s == iter4->second)
	//		{
	//			fout5 << iter4->first;
	//			s = "";
	//		}
	//	}
	//}
	string str;
	fin3>>str;
	fout5 << HuffDeCode(code,str,n);
	cout << "���ı��ļ�����ɹ���" << endl;

	fin3.close();
	fout5.close();
	return 0;
}

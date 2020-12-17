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


	//b)统计source.txt文件中各字符的出现次数（涉及读文件，统计字符个数）。并把各个字符及出现的个数写到CharNum.txt文件中。
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
	cout << "统计字符个数成功。" << endl;

	//c)把各个字符按出现次数进行排序，排序结果保存到SortedCharNum.txt文件中。
	vector<pair<char, int>> tmp;
	for (auto& i : ump)
	{
		tmp.push_back(i);
	}
	sort(tmp.begin(), tmp.end(),
		[=](pair<char, int>& a, pair<char, int>& b) { return a.second > b.second; });//tmp已经按second数从大到小排过序了
	vector<pair<char, int>>::iterator iter2;
	for (iter2 = tmp.begin(); iter2 != tmp.end(); iter2++)
	{
		fout2 << iter2->first << "\t" << iter2->second << endl;
	}
	cout << "排序成功。" << endl;

	//d)对文件中的字符进行哈夫曼编码，并存储入字符编码CharCode.txt文件中。
	map<char, int> m;//内部自动排序，并且不允许有重复元素
	for (iter2 = tmp.begin(); iter2 != tmp.end(); iter2++)//tmp已排序，再把它放到map中，不要问为什么。
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
	cout << "HuffMan编码成功。" << endl;

	//e)根据字符编码文件，对source.txt文本文件内容进行编码，编码结果存储到encode.txt文件中。
	map<char, string> codefile1;//储存字符和编码
	for (int i = 1; i <= n; i++)
	{
		codefile1[code[i].data] = code[i].code;
	}
	ifstream fin2("source.txt", ios::in);//重新打开文件
	while (fin2.get(ch))
	{
		fout4 << codefile1[ch];
	}
	cout << "对文本文件编码成功。" << endl;

	//f)根据CharCode.txt文件中的字符编码，对已编码的文件encode.txt进行解码，解码之后存储到decode.txt文件中。
	//有待优化
	fin1.close();
	fin2.close();
	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	ifstream fin3("encode.txt", ios::in);//重新打开文件

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
	cout << "对文本文件解码成功。" << endl;

	fin3.close();
	fout5.close();
	return 0;
}

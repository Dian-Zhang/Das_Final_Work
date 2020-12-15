#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
const int INF = 65535;

//��������
typedef struct Node {
	int weight;
	int parent;
	int lchild;
	int rchild;
}*HuffmanTree;

//����������
typedef struct Code {
	char data;
	int weight;
	string code;
}*HuffmanCode;

void initTree(HuffmanTree& tree, HuffmanCode& code, map<char, int> m, int n);
void Select(HuffmanTree& tree, int& a, int& b, int n);
void createHuffmanTree(HuffmanTree& tree, int n);
void HuffCode(HuffmanTree& tree, HuffmanCode& code, int n);
string HuffDeCode(HuffmanCode& code, string s, int n);
void printTest(HuffmanTree tree, HuffmanCode code, string s, map<char, int> m, int n);

int main()
{
	vector<string> vec;
	string s;
	string arr = "";
	cout << "�������������ַ���(��0����)��" << endl;//aaaaaaabbbbbccdddd
	while (true)
	{
		getline(cin, s);//��ȡ�����ո���ַ���
		if (s == "0")
			break;
		vec.push_back(s);
	}
	for (int i = 0; i < vec.size(); i++)
	{
		cout << endl;
		cout << "�ַ���" << i + 1 << endl;
		s = vec[i];
		map<char, int> m;//�ڲ��Զ����򣬲��Ҳ��������ظ�Ԫ��
		for (int i = 0; i < s.size(); i++)//ͳ���ַ����и����ַ����ֵĴ���
		{
			m[s[i]]++;
		}
		int n = m.size();
		HuffmanTree tree = new Node[2 * n];
		HuffmanCode code = new Code[n + 1];
		initTree(tree, code, m, n);
		createHuffmanTree(tree, n);
		HuffCode(tree, code, n);
		printTest(tree, code, s, m, n);
	}
	return 0;
}

//��ʼ������
void initTree(HuffmanTree& tree, HuffmanCode& code, map<char, int> m, int n)
{
	//��ʼ��Ȩ�ء����ӽڵ�ֵ
	map<char, int>::iterator it;
	it = m.begin();
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		if (i <= n)
		{
			tree[i].weight = it->second;
			code[i].weight = it->second;
			code[i].data = it->first;
			it++;
		}
		else
		{
			tree[i].weight = 0;
		}
		tree[i].parent = tree[i].lchild = tree[i].rchild = 0;
	}
}

//ѡ��������Сֵ
void Select(HuffmanTree& tree, int& a, int& b, int n)
{
	int minWeight = INF;
	//Ѱ����Сֵ Ȩֵ��С�����޸��ڵ�
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].weight < minWeight && tree[i].parent == 0)
		{
			minWeight = tree[i].weight;
			a = i;
		}
	}
	minWeight = INF;
	//Ѱ�Ҵ�Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].weight < minWeight && tree[i].parent == 0 && i != a)
		{
			minWeight = tree[i].weight;
			b = i;
		}
	}
}

//������������
void createHuffmanTree(HuffmanTree& tree, int n)
{
	int a, b;
	for (int i = n + 1; i <= 2 * n - 1; i++)//n*n
	{
		Select(tree, a, b, i - 1);//��i-1��Χѡ��������Сֵ
		tree[a].parent = i;
		tree[b].parent = i;
		tree[i].lchild = a;
		tree[i].rchild = b;
		tree[i].weight = tree[a].weight + tree[b].weight;
	}
}

//����������
void HuffCode(HuffmanTree& tree, HuffmanCode& code, int n)
{
	string s;
	int j, k;
	for (int i = 1; i <= n; i++)//n*logn
	{
		s = "";
		j = i;
		while (tree[j].parent != 0)//���ڵ�ĸ��ڵ�Ϊ0
		{
			k = tree[j].parent;
			if (j == tree[k].lchild)//����Ϊ0 �Һ���Ϊ1
			{
				s += "0";
			}
			else
			{
				s += "1";
			}
			j = tree[j].parent;//�򸸽ڵ����
		}
		reverse(s.begin(), s.end());//����s
		code[i].code = s;
	}
}

//����������
string HuffDeCode(HuffmanCode& code, string s, int n)
{
	string res = "";
	string temp = "";
	//����һ ��ÿ���ַ��γɵ��ַ�����code�б����ÿ�������Ʊ�����жԱ�
	//������ ���Ը��ݸ��ڵ�Ȼ�����亢�ӽڵ� �����0 ������ �����1���к��� ֱ�������Һ���Ϊ0Ϊֹ
	for (int i = 0; i < s.size(); i++)
	{
		temp += s[i];//ÿ���ַ������жԱ�
		for (int j = 1; j <= n; j++)//��ṹ���еı�����жԱ�
		{
			if (temp == code[j].code)
			{
				res += code[j].data;
				temp = "";
				break;
			}
		}
	}
	return res;
}

//����
void printTest(HuffmanTree tree, HuffmanCode code, string s, map<char, int> m, int n)
{
	string arr = "";
	cout << "�ַ����и�����ĸ���ֵ�Ƶ�ʣ�" << endl;
	map<char, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << ":" << it->second << " ";
	}
	cout << endl;
	cout << "���������Ĵ洢�ṹ��̬(Ȩֵ�����ڵ㡢���ӡ��Һ���)��" << endl;
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		cout << i << " " << tree[i].weight << " " << tree[i].parent << " " << tree[i].lchild << " " << tree[i].rchild << endl;
	}
	cout << "������ĸ��Ӧ�Ĺ��������룺" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << code[i].data << ":" << code[i].code << " ";
	}
	cout << endl;
	cout << "�ַ�����Ӧ�Ĺ���������Ϊ��" << endl;
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (s[i] == code[j].data)//ƥ�����ṹ���е��ַ��������Ӧ����
			{
				cout << code[j].code;
				arr += code[j].code;
				break;
			}
		}
	}
	cout << endl;
	cout << "�������������Ϊ��" << endl;
	cout << HuffDeCode(code, arr, n) << endl;
	cout << "����ѹ����Ϊ��" << ((float)arr.size() / s.size() * 8) << "%" << endl;
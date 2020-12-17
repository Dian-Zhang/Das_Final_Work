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
	char data;//�ַ�
	int weight;//Ȩ��
	string code;//����
}*HuffmanCode;

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
			tree[i].weight = 0;//
		}
		tree[i].parent = tree[i].lchild = tree[i].rchild = 0;//
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
		tree[a].parent = i;//�ýڵ��˫�׽ڵ��������е��±�
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
		while (tree[j].parent != 0)//���ڵ�ĸ��ڵ�Ϊ0,�����Ҹ��ڵ㡣
		{
			k = tree[j].parent;//���ڵ�
			if (j == tree[k].lchild)//����Ϊ0 �Һ���Ϊ1
			{
				s += "0";
			}
			else
			{
				s += "1";
			}
			j = k;//�򸸽ڵ����
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
	for (unsigned int i = 0; i < s.size(); i++)
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
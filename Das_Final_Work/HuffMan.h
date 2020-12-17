#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
const int INF = 65535;

//哈夫曼树
typedef struct Node {
	int weight;
	int parent;
	int lchild;
	int rchild;
}*HuffmanTree;

//哈夫曼编码
typedef struct Code {
	char data;//字符
	int weight;//权重
	string code;//编码
}*HuffmanCode;

//初始化参数
void initTree(HuffmanTree& tree, HuffmanCode& code, map<char, int> m, int n)
{
	//初始化权重、父子节点值
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

//选择两个最小值
void Select(HuffmanTree& tree, int& a, int& b, int n)
{
	int minWeight = INF;
	//寻找最小值 权值最小并且无父节点
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].weight < minWeight && tree[i].parent == 0)
		{
			minWeight = tree[i].weight;
			a = i;
		}
	}
	minWeight = INF;
	//寻找次小值
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].weight < minWeight && tree[i].parent == 0 && i != a)
		{
			minWeight = tree[i].weight;
			b = i;
		}
	}
}

//构建哈夫曼树
void createHuffmanTree(HuffmanTree& tree, int n)
{
	int a, b;
	for (int i = n + 1; i <= 2 * n - 1; i++)//n*n
	{
		Select(tree, a, b, i - 1);//从i-1范围选择两个最小值
		tree[a].parent = i;//该节点的双亲节点在数组中的下标
		tree[b].parent = i;
		tree[i].lchild = a;
		tree[i].rchild = b;
		tree[i].weight = tree[a].weight + tree[b].weight;
	}
}


//哈夫曼编码
void HuffCode(HuffmanTree& tree, HuffmanCode& code, int n)
{
	string s;
	int j, k;
	for (int i = 1; i <= n; i++)//n*logn
	{
		s = "";
		j = i;
		while (tree[j].parent != 0)//根节点的父节点为0,往上找根节点。
		{
			k = tree[j].parent;//父节点
			if (j == tree[k].lchild)//左孩子为0 右孩子为1
			{
				s += "0";
			}
			else
			{
				s += "1";
			}
			j = k;//向父节点遍历
		}
		reverse(s.begin(), s.end());//逆序s
		code[i].code = s;
	}
}

//哈夫曼解码
string HuffDeCode(HuffmanCode& code, string s, int n)
{
	string res = "";
	string temp = "";
	//方法一 将每个字符形成的字符串与code中保存的每个二进制编码进行对比
	//方法二 可以根据根节点然后找其孩子节点 如果是0 找左孩子 如果是1找有孩子 直到其左右孩子为0为止
	for (unsigned int i = 0; i < s.size(); i++)
	{
		temp += s[i];//每个字符都进行对比
		for (int j = 1; j <= n; j++)//与结构体中的编码进行对比
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
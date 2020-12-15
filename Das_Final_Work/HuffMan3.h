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
	cout << "请输入待编码的字符串(以0结束)：" << endl;//aaaaaaabbbbbccdddd
	while (true)
	{
		getline(cin, s);//获取包含空格的字符串
		if (s == "0")
			break;
		vec.push_back(s);
	}
	for (int i = 0; i < vec.size(); i++)
	{
		cout << endl;
		cout << "字符串" << i + 1 << endl;
		s = vec[i];
		map<char, int> m;//内部自动排序，并且不允许有重复元素
		for (int i = 0; i < s.size(); i++)//统计字符串中各个字符出现的次数
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
			tree[i].weight = 0;
		}
		tree[i].parent = tree[i].lchild = tree[i].rchild = 0;
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
		tree[a].parent = i;
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
		while (tree[j].parent != 0)//根节点的父节点为0
		{
			k = tree[j].parent;
			if (j == tree[k].lchild)//左孩子为0 右孩子为1
			{
				s += "0";
			}
			else
			{
				s += "1";
			}
			j = tree[j].parent;//向父节点遍历
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
	for (int i = 0; i < s.size(); i++)
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

//测试
void printTest(HuffmanTree tree, HuffmanCode code, string s, map<char, int> m, int n)
{
	string arr = "";
	cout << "字符串中各个字母出现的频率：" << endl;
	map<char, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << ":" << it->second << " ";
	}
	cout << endl;
	cout << "哈弗曼树的存储结构终态(权值、父节点、左孩子、右孩子)：" << endl;
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		cout << i << " " << tree[i].weight << " " << tree[i].parent << " " << tree[i].lchild << " " << tree[i].rchild << endl;
	}
	cout << "各个字母对应的哈夫曼编码：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << code[i].data << ":" << code[i].code << " ";
	}
	cout << endl;
	cout << "字符串对应的哈夫曼编码为：" << endl;
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (s[i] == code[j].data)//匹配编码结构体中的字符，输出对应编码
			{
				cout << code[j].code;
				arr += code[j].code;
				break;
			}
		}
	}
	cout << endl;
	cout << "哈夫曼编码解码为：" << endl;
	cout << HuffDeCode(code, arr, n) << endl;
	cout << "数据压缩比为：" << ((float)arr.size() / s.size() * 8) << "%" << endl;
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct HuffmanNode {
	int weight;
	char value;
	string code;
	int lIndex, rIndex, parentIndex;
};

class HuffmanCode {
public:
	explicit HuffmanCode(const string& str);
	~HuffmanCode();
	void setMin(int& lMinIndex, int& rMinIndex, int parentIndex);
	void merge(int lMinIndex, int rMinIndex, int parentIndex);
	void coding();
	void decode(const string& str);

private:
	int leafNumber; // 存储不同字符的个数也就是哈夫曼树叶子节点个数
	HuffmanNode* huffmanTree;
};

HuffmanCode::HuffmanCode(const string& str)
{
	huffmanTree = new HuffmanNode[256];
	leafNumber = 0;

	int length = str.size();
	int ascii[256], index;
	memset(ascii, 0, sizeof(ascii));

	for (int i = 0; i < (2 * length - 1); i++)
	{
		huffmanTree[i].parentIndex = huffmanTree[i].rIndex = huffmanTree[i].lIndex = -1;
		huffmanTree[i].code = "";
	}

	// 记录每个字符的权重
	for (int i = 0; i < length; ++i)
	{
		ascii[str[i]]++;
	}
	// 记录所有叶子节点的值和权重
	for (int i = 0; i < 256; i++)
	{
		if (ascii[i] != 0)
		{
			huffmanTree[leafNumber].value = (char)i;    // 值
			huffmanTree[leafNumber].weight = ascii[i];  // 权重
			++leafNumber;
		}
	}

	int lMinIndex, rMinIndex;
	for (int parentIndex = leafNumber; parentIndex < (2 * leafNumber - 1); ++parentIndex)
	{
		setMin(lMinIndex, rMinIndex, parentIndex);
		merge(lMinIndex, rMinIndex, parentIndex);
	}
}

HuffmanCode::~HuffmanCode()
{
	delete[]huffmanTree;
}

void HuffmanCode::setMin(int& lMinIndex, int& rMinIndex, int parentIndex)
{
	double weight = 0;
	for (int i = 0; i < parentIndex; ++i)
	{
		if (huffmanTree[i].parentIndex != -1)   // 已选过
			continue;

		if (weight == 0)
		{
			weight = huffmanTree[i].weight;
			lMinIndex = i;
		}
		else if (huffmanTree[i].weight < weight)
		{
			weight = huffmanTree[i].weight;
			lMinIndex = i;
		}
	}

	weight = 0;
	for (int i = 0; i < parentIndex; ++i)
	{
		if (huffmanTree[i].parentIndex != -1 || i == lMinIndex)   // 已选过
			continue;

		if (weight == 0)
		{
			weight = huffmanTree[i].weight;
			rMinIndex = i;
		}
		else if (huffmanTree[i].weight < weight)
		{
			weight = huffmanTree[i].weight;
			rMinIndex = i;
		}
	}
}

void HuffmanCode::merge(int lMinIndex, int rMinIndex, int parentIndex)
{
	huffmanTree[lMinIndex].parentIndex = huffmanTree[rMinIndex].parentIndex = parentIndex;
	huffmanTree[parentIndex].lIndex = lMinIndex;
	huffmanTree[parentIndex].rIndex = rMinIndex;
	huffmanTree[parentIndex].weight = huffmanTree[lMinIndex].weight + huffmanTree[rMinIndex].weight;
}

void HuffmanCode::coding()
{
	std::string code;
	int parentIndex, tempIndex;
	// 从叶子结点出发
	for (int i = 0; i < leafNumber; ++i)
	{
		code = "";
		tempIndex = i;

		while (huffmanTree[tempIndex].parentIndex != -1)
		{
			parentIndex = huffmanTree[tempIndex].parentIndex;
			if (tempIndex == huffmanTree[parentIndex].lIndex)
				code += "0";
			else
				code += "1";

			tempIndex = parentIndex;
		}
		// 把编码倒过来
		for (int j = (int)code.size() - 1; j >= 0; --j)
		{
			huffmanTree[i].code += code[j];
		}

		std::cout << "字符：" << huffmanTree[i].value << " 的编码为：" << huffmanTree[i].code << std::endl;
	}
}

void HuffmanCode::decode(const std::string& str)
{
	std::string decode, tempCode;
	decode = tempCode = "";
	int length = (int)str.size();

	int i, j;
	for (i = 0; i < length; ++i)
	{
		tempCode += str[i];
		for (j = 0; j < leafNumber; ++j)
		{
			if (huffmanTree[j].code == tempCode)
			{
				decode += huffmanTree[j].value;
				tempCode = "";
				break;
			}
		}

		if (i == length - 1 && j == leafNumber)
		{
			std::cout << "解码出错！" << std::endl;
			return;
		}
	}
	std::cout << decode << std::endl;
}


int main()
{
	std::string str;

	std::cout << "请输入字符串进行编码：" << std::endl;
	std::cin >> str;
	HuffmanCode huffman(str);

	std::cout << "对字符串编码情况如下：" << std::endl;
	huffman.coding();
	std::cout << std::endl;

	std::cout << "请输入要解码的二进制编码:" << std::endl;
	std::cin >> str;
	std::cout << "解码如下：" << std::endl;
	huffman.decode(str);

	return 0;
}
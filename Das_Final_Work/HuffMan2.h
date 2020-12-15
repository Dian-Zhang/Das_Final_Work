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
	int leafNumber; // �洢��ͬ�ַ��ĸ���Ҳ���ǹ�������Ҷ�ӽڵ����
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

	// ��¼ÿ���ַ���Ȩ��
	for (int i = 0; i < length; ++i)
	{
		ascii[str[i]]++;
	}
	// ��¼����Ҷ�ӽڵ��ֵ��Ȩ��
	for (int i = 0; i < 256; i++)
	{
		if (ascii[i] != 0)
		{
			huffmanTree[leafNumber].value = (char)i;    // ֵ
			huffmanTree[leafNumber].weight = ascii[i];  // Ȩ��
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
		if (huffmanTree[i].parentIndex != -1)   // ��ѡ��
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
		if (huffmanTree[i].parentIndex != -1 || i == lMinIndex)   // ��ѡ��
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
	// ��Ҷ�ӽ�����
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
		// �ѱ��뵹����
		for (int j = (int)code.size() - 1; j >= 0; --j)
		{
			huffmanTree[i].code += code[j];
		}

		std::cout << "�ַ���" << huffmanTree[i].value << " �ı���Ϊ��" << huffmanTree[i].code << std::endl;
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
			std::cout << "�������" << std::endl;
			return;
		}
	}
	std::cout << decode << std::endl;
}


int main()
{
	std::string str;

	std::cout << "�������ַ������б��룺" << std::endl;
	std::cin >> str;
	HuffmanCode huffman(str);

	std::cout << "���ַ�������������£�" << std::endl;
	huffman.coding();
	std::cout << std::endl;

	std::cout << "������Ҫ����Ķ����Ʊ���:" << std::endl;
	std::cin >> str;
	std::cout << "�������£�" << std::endl;
	huffman.decode(str);

	return 0;
}
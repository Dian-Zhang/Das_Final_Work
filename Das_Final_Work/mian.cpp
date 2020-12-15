#include<iostream>
#include<fstream>
#include<unordered_map>
#include<algorithm>
#include<map>
#include<iterator>
#include<string>
using namespace std;

int main() {
	ifstream fin("source.txt", ios::in);
	ofstream fout1("CharNum.txt", ios::out);
	ofstream fout2("SortedCharNum.txt", ios::out);
	ofstream fout3("CharCode.txt", ios::out);

	//CharNum.txt
	char ch;
	unordered_map<char, int> ump;
	unordered_map<char, int>::iterator iter;
	while (fin.get(ch))
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
	cout << "I'm spend five hours.I'm so happy!" << endl;

	//SortedCharNum.txt
	vector<pair<char, int>> tmp;
	for (auto& i : ump)
	{
		tmp.push_back(i);
	}

	sort(tmp.begin(), tmp.end(),
		[=](pair<char, int>& a, pair<char, int>& b) { return a.second > b.second; });

	vector<pair<char, int>>::iterator iter2;
	for (iter2 = tmp.begin(); iter2 != tmp.end(); iter2++)
	{
		fout2 << iter2->first << "\t" << iter2->second << endl;
	}
	cout << "YES!" << endl;

	//CharCode.txt


	fin.close();
	fout1.close();
	fout2.close();
	return 0;
}

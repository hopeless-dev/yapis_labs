#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// ������ � �������
vector<string> readTableFromFile(const string);
map<string, int> readHistory(string);
void writeHistory(const map<string, int>&, string);

// �������� ��������
pair<int, int> binarySearch(const vector<string>&, const string&);
int countAverageNumber(const map<string, int>&);

int main()
{
	setlocale(LC_ALL, "Russian");
	string identifier, fileToAverage = "history.log";
	pair<int, int> result;
	
	// ����������� � ���� ������ 
	vector<string> table = readTableFromFile("input.txt");
	// �������������� � ���� ����������� �������
	sort(table.begin(), table.end());

	cout << "������� �����������: ";
	cin >> identifier;
	result = binarySearch(table, identifier);
	cout << "������� � �������: " << result.first << endl;
	cout << "���������� ���������: " << result.second << endl;

	map<string, int> history = readHistory(fileToAverage);
	if (result.first != -1)
	{
		history[table[result.first]] = result.second;
		writeHistory(history, fileToAverage);
	}
	cout << "������� ����� ���������: " << countAverageNumber(history) << endl;

	cout << endl << "������������ ��������������� ��� ������� �������: " << endl;
	for (pair<string, int> record : history) {
		cout << record.first << ' ' << record.second << endl;
	}
	system("pause");
	return 0;
}

vector<string> readTableFromFile(const string nameOfFile)
{
	vector<string> table;
	ifstream fin(nameOfFile);
	for (istream_iterator<string> iter(fin), end; iter != end; iter++) {
		table.push_back(*iter);
	}
	return table;
}

// ��������������� �����
pair<int, int> binarySearch(const vector<string>& table, const string& word)
{
	int num = 0, left = 0, right = table.size(), pos = -1;
	while (left < right) 
	{
		num++;
		int mid = left + (right - left) / 2;
		if (word == table[mid])
		{
			pos = mid;
			break;
		}
		else if (word <= table[mid]) 
		{
			right = mid;
		}
		else 
		{
			left = mid + 1;
		}
	}
	return make_pair(pos, num);
}

int countAverageNumber(const map<string, int>& history)
{
	int average = 0;
	for (pair<string, int> record : history) 
	{
		average += record.second;
	}
	average /= history.size();
	return average;
}

map<string, int> readHistory(const string nameOfFile)
{
	map<string, int> history;
	ifstream fin(nameOfFile);

	while (!fin.eof())
	{
		string word;
		int num;
		fin >> word >> num;
		if (word != "") 
		{
			history[word] = num;
		}
	}
	return history;
}

void writeHistory(const map<string, int>& history, const string nameOfFile)
{
	ofstream fout(nameOfFile);

	for (pair<string, int> record : history) 
	{
		fout << record.first << ' ' << record.second << endl;
	}
}
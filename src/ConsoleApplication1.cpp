// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdlib> 
using namespace std;

void printvec(vector<string> &vec)
{
	for_each(vec.begin(), vec.end(), [](string s) {cout << s << endl; });
	system("pause");
}
void Bubble_sort(vector<string> &vec, function<bool(string, string)> f)
{
	int vec_size = vec.size();
	string tmp;
	bool swapped = false;
	for (int i = 0; i < vec_size; i++)
	{
		for (int j = 0; j < (vec_size - i - 1); j++)
		{
			if (f(vec[j], vec[j + 1]))
			{
				tmp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = tmp;
				swapped = true;
			}
		}
		if (swapped == false)
		{
			break;
		}
	}
}

int main()
{
	vector<string> v = { "One", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	printvec(v);
	Bubble_sort(v, [](string a, string b) {return (a.size()<b.size()); });
	printvec(v);
	Bubble_sort(v, [](string a, string b) {return (a.size()>b.size()); });
	printvec(v);
	Bubble_sort(v, [](string a, string b) {return ((int)a[0]>(int)b[0]); });
	printvec(v);
	Bubble_sort(v, [](string a, string b) {return ((int)a[0]<(int)b[0]); });
	printvec(v);
}


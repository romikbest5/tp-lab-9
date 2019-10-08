// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>


using namespace std;

bool finished(false), printed(false), procced(true);
mutex mx;
condition_variable cv;

void Bubble_sort(vector<string>* v, function<bool(string, string)> f)
{
	int vec_size = v->size();
	vector<string>& vec = *v;
	string tmp;
	bool sorting = true;
	for (int i = 0; i < vec_size && sorting; i++)
	{
		unique_lock<mutex> lk(mx);
		cv.wait(lk, [] {return (printed); });

		sorting = false;
		for (int j = 0; j < (vec_size - i - 1); j++)
		{
			if (f(vec[j], vec[j + 1]))
			{
				tmp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = tmp;
				sorting = true;
			}
		}

		procced = true;
		printed = false;
		cout << "End of sorting cycle" << endl;
		lk.unlock();
		cv.notify_all();
	}
	finished = true;
}

int main()
{
	vector<string> v = { "One", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	thread tr(Bubble_sort, &v,
		[](string a, string b) {return (a.size()<b.size()); });
	while (true)
	{
		unique_lock<mutex> lk(mx);
		cv.wait(lk, [] {return (procced); });
		if (finished)
		{
			cout << "Sorted" << endl;
			break;
		}
		procced = false;
		for_each(v.begin(), v.end(), [](string s) {cout << s << " "; });
		cout << endl;
		printed = true;
		lk.unlock();
		cv.notify_all();
	}
	tr.join();
	system("pause");

}


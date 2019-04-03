
#include <iostream>

#include <stdio.h>
#include <vector>

using namespace std;

int subMaxNumber(int number)
{
	if (number < 10)
		return number;
	int temp = number;
	std::vector<int> data;
	while (temp != 0)
	{
		data.insert(data.begin(), temp % 10);
		temp = temp / 10;
	}
	bool bFind = false;
	int last = data[0];
	int res = 0;
	for (int i = 1; i<data.size(); i++)
	{
		if (bFind)
		{
			res = res * 10 + data[i];
			continue;
		}
		if (last <= data[i])
		{
			bFind = true;
			res = res * 10 + data[i];
			continue;
		}
		else {
			res = res * 10 + last;
			last = data[i];
		}
	}

	return res;
}

int main(void)
{


	unsigned int input = 765484;
	unsigned int number = 1;
	cin >> input;
	cin >> number;

	unsigned int res = input;
	for (unsigned int i = 0; i<number; i++)
	{
		res = subMaxNumber(res);
	}
	cout << res;
	return 0;
}
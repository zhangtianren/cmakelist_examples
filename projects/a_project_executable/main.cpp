
#include <iostream>

#include <stdio.h>
#include <vector>

using namespace std;
void printv(const vector<int>& num)
{
    for (int i=0;i< num.size();i++)
    {
        printf(" %d ", num.at(i));
    }
}

int maxof(const vector<int>& num, int start, int end)
    {
        int max = num.at(start);
        for (int i=start;i<=end;i++)
        {
            if (num.at(i) > max)
                max = num.at(i);
        }
        return max;
    }
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> result;
        if (size == 1)
        {
            result.insert(result.begin(), num.begin(), num.end());
            return result;
        }
        if (num.size() == 0)
            return result;
        if (num.size() <= size)
        {
            result.push_back(maxof(num, 0, num.size() - 1));
            return result;
        }
        
        for (int i = 0;i<= num.size() - size;i++)
        {
            result.push_back(maxof(num, i, i+ size -1));
        }
        
        return result;
        
        
    }
int main(void)
{
	int n[] = {2,3,4,2,6,2,5,1};
	std::vector<int> v;
	v.insert(v.begin(), n, n+8);

    printv(v);
	printv(maxInWindows(v, 0));
	
	return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int min(vector<int> vec)
{
    if (vec.size() == 0)
    {
        cout << "Vector is empty. Cannot find minimum element." << endl;
        return INT_MIN;
    }
    int min = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < min)
        {
            min = vec[i];
        }
    }
    return min;
}

int findelement(vector<int> vec, int ele)
{
    if (vec.size() == 0)
    {
        cout << "Vector is empty. Cannot find element." << endl;
        return -1;
    }
    int ind = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == ele)
        {
            ind = i;
        }
    }
    return ind;
}

int main()
{
    vector<int> vec = {10, -56, 204, 0, -782, 345};
    int num = 11;
    cout << min(vec) << endl;
    if (findelement(vec, num) == -1)
    {
        cout << "Element not found in the vector." << endl;
    }
    else
    {
        cout << findelement(vec, num) << endl;
    }
}
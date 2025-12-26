#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int> vec)
{
}

int main()
{
    vector<int> vec = {};
    sort(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}
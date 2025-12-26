#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int> &vec)
{
    if (vec.size() == 0)
    {
        cout << "Cannot sort an empty vector." << endl;
        return;
    }
    else if (vec.size() == 1)
    {
        return;
    }
    int pivot = vec[0];
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] <= pivot)
        {
        }
        else if (vec[i] > pivot)
        {
        }
    }
}

int main()
{
    vector<int> vec = {1, -23, 120, -4, 100, 1098, 130, 107};
    sort(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}
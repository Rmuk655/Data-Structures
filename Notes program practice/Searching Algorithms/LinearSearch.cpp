#include <iostream>
#include <vector>

using namespace std;

bool search(vector<int> vec, int num)
{
    if (vec.size() == 0)
    {
        cout << "Empty array! Cannot search for " << num << endl;
        return false;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == num)
        {
            return true;
        }
    }
    return false;
}

int count(vector<int> vec, int num)
{
    if (vec.size() == 0)
    {
        cout << "Empty array! Cannot search for " << num << endl;
        return 0;
    }
    else if (!search(vec, num))
    {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == num)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    vector<int> vec = {1, -23, 120, -4, 100, 1098, 130, 107};
    int num = 10;
    if (search(vec, num))
    {
        cout << "Found " << count(vec, num) << " times." << endl;
    }
    else if (vec.size() != 0)
    {
        cout << "Not Found" << endl;
    }
}
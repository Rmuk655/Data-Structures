#include <iostream>
#include <vector>

using namespace std;

bool search(vector<int> vec, int start, int end, int num)
{
    if (vec.size() == 0)
    {
        cout << "Empty array! Cannot search for " << num << endl;
        return false;
    }
    else if (start == end)
    {
        return false;
    }
    int mid = (start + end) / 2;
    if (vec[mid] == num)
    {
        return true;
    }
    else if (vec[mid] > num)
    {
        return search(vec, start, mid, num);
    }
    else
    {
        return search(vec, mid + 1, end, num);
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
    else if (!search(vec, 0, vec.size() - 1, num))
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

void shiftasc(vector<int> &vec, int index)
{
    for (int i = index; i > 0; i--)
    {
        if (vec[i] < vec[i - 1])
        {
            int temp = vec[i - 1];
            vec[i - 1] = vec[i];
            vec[i] = temp;
        }
    }
}

void sort(vector<int> &vec)
{
    if (vec.size() == 0)
    {
        cout << "Empty array!" << endl;
        return;
    }
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] < vec[i - 1])
        {
            shiftasc(vec, i);
        }
    }
}

int main()
{
    vector<int> vec = {1, -23, 120, -4, 100, 1098, 130, 107};
    int num = 100;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    sort(vec);
    if (search(vec, 0, vec.size() - 1, num))
    {
        cout << "Found " << count(vec, num) << " times." << endl;
    }
    else if (vec.size() != 0)
    {
        cout << "Not Found" << endl;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}
#include <iostream>
#include <vector>

using namespace std;
// CLRS P2.2-2

void sort(vector<int> &vec)
{
    int min_ind;
    for (int i = 0; i < vec.size(); i++)
    {
        min_ind = i;
        for (int j = i; j < vec.size(); j++)
        {
            if (vec[j] < vec[min_ind])
            {
                min_ind = j;
            }
        }
        int temp = vec[min_ind];
        vec[min_ind] = vec[i];
        vec[i] = temp;
    }
}

int main()
{
    vector<int> vec = {14, 45, -65, 3, -4, 0, 135, -109};
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    sort(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}
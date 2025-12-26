#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

#define n 800
using namespace std;
// Time complexity = O(n)
// Space complexity = O(m)

struct hash_function
{
    int m;
    int a;
    int b;
};

int hash_func(struct hash_function *hash, int ele)
{
    return (hash->a * ele + hash->b) % hash->m;
}

struct hash_function *create_hash(int m)
{
    struct hash_function *new_hash = new struct hash_function();
    new_hash->m = m;
    new_hash->a = rand() % m;
    new_hash->b = rand() % m;
    return new_hash;
}

struct bloom_filter
{
    int k;
    int size;
    int *arr;
    vector<struct hash_function *> hash;
};

struct bloom_filter *create_bloom(int m)
{
    struct bloom_filter *bloom_filter = new struct bloom_filter();
    bloom_filter->k = floor(m / n * log(2));
    bloom_filter->size = m;
    int arr[m];
    for (int i = 0; i < m; i++)
    {
        arr[i] = 0;
    }
    bloom_filter->arr = arr;
    vector<struct hash_function *> hash;
    for (int i = 0; i < bloom_filter->k; i++)
    {
        hash.push_back(create_hash(m));
    }
    bloom_filter->hash = hash;
    return bloom_filter;
}

void bloom(struct bloom_filter *&bloom_filter, int ele)
{
    for (int i = 0; i < bloom_filter->k; i++)
    {
        bloom_filter->arr[hash_func(bloom_filter->hash[i], ele)] = 1;
    }
}

bool is_present_bloom_filter(struct bloom_filter *bloom_filter, int ele)
{
    for (int i = 0; i < bloom_filter->k; i++)
    {
        if (bloom_filter->arr[hash_func(bloom_filter->hash[i], ele)] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream file1("dataset.txt");
    int num;
    vector<int> inputset;
    while (file1 >> num)
    {
        inputset.push_back(num);
    }
    file1.close();

    ifstream file2("query_positive.txt");
    vector<int> testset_1;
    while (file2 >> num)
    {
        testset_1.push_back(num);
    }
    file2.close();

    ifstream file3("query_negative.txt");
    vector<int> testset_2;
    while (file3 >> num)
    {
        testset_2.push_back(num);
    }
    file3.close();

    int m[3] = {3000, 4000, 5000}, confusion_matrix[2][2];
    for (int i = 0; i < 3; i++)
    {
        int tp = 0, tn = 0, fp = 0, fn = 0;
        struct bloom_filter *bloom_filter = create_bloom(m[i]);
        for (int i = 0; i < inputset.size(); i++)
        {
            bloom(bloom_filter, inputset[i]);
        }

        for (int i = 0; i < testset_1.size(); i++)
        {
            if (is_present_bloom_filter(bloom_filter, testset_1[i]))
            {
                tp++;
            }
            else
            {
                fn++;
            }
        }

        for (int i = 0; i < testset_2.size(); i++)
        {
            if (is_present_bloom_filter(bloom_filter, testset_2[i]))
            {
                fp++;
            }
            else
            {
                tn++;
            }
        }

        confusion_matrix[0][0] = tp;
        confusion_matrix[0][1] = tn;
        confusion_matrix[1][0] = fp;
        confusion_matrix[1][1] = fn;
        cout << "For m = " << m[i] << endl;
        cout << "True positive = " << confusion_matrix[0][0] << endl;
        cout << "True negative = " << confusion_matrix[0][1] << endl;
        cout << "False positive = " << confusion_matrix[1][0] << endl;
        cout << "False negative = " << confusion_matrix[1][1] << endl;
    }
}
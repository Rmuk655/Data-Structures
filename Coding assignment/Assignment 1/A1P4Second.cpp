#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <math.h>

using namespace std;
constexpr long long SIZE = 10000000000LL;
#define START SIZE + 1

struct person
{
    long long int NHS_No;
    string name;
    string email;
    string gender;
};

vector<struct person *> read()
{
    vector<struct person *> vec;
    ifstream file("Data.csv");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        struct person *person;
        vector<string> row;
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        person->NHS_No = stoll(row[1]);
        person->name = row[2];
        person->email = row[3];
        person->gender = row[4];
        vec.push_back(person);
    }
    return vec;
}

bool is_prime(long long int x)
{
    if (x <= 1)
    {
        return false;
    }
    else if (x == 2)
    {
        return true;
    }
    for (long long int i = 0; i < sqrt(x); i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}

long long int get_p()
{
    long long int p = START;
    while (!is_prime(p))
    {
        p = p + 2;
    }
    return p;
}

long long int get_a()
{
    long long int a = START;
    return a;
}

int calc_r(long long int p)
{
    return (int)(log(SIZE) / log(p));
}

vector<long long int> base_m(long long int x, long long int p)
{
    vector<long long int> vec;
    if (x < p)
    {
        vec.push_back(x);
        return vec;
    }
    while (x > 0)
    {
        vec.push_back(x % p);
        x = x / p;
    }
    return vec;
}

long long int key(long long int NHS_No, long long int a, long long int p)
{
}

struct person *search(long long int NHS_No)
{
    vector<struct person *> vec = read();
    return vec[key(NHS_No, get_a(), get_p())];
}

int main()
{
    long long int NHS_No;
    cin >> NHS_No;
    struct person *ans = search(NHS_No);
    if (ans)
    {
        cout << ans->name << "," << ans->email << "," << ans->gender << endl;
    }
    else
    {
        cout << "Key not found" << endl;
    }
}
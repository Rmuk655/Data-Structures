#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

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

void insertionsortasc(vector<int> &vec)
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

void shiftdesc(vector<int> &vec, int index)
{
    for (int i = index; i > 0; i--)
    {
        if (vec[i] > vec[i - 1])
        {
            int temp = vec[i - 1];
            vec[i - 1] = vec[i];
            vec[i] = temp;
        }
    }
}

void insertionsortdesc(vector<int> &vec)
{
    if (vec.size() == 0)
    {
        cout << "Empty array!" << endl;
        return;
    }
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] > vec[i - 1])
        {
            shiftdesc(vec, i);
        }
    }
}

int sumarray(vector<int> vec)
{
    int sum = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

// Helper to compare vectors and print test results
bool runTest(const std::string &testName, std::vector<int> input, const std::vector<int> &expected)
{
    insertionsortasc(input);
    if (input == expected)
    {
        std::cout << "[PASS] " << testName << "\n";
        return true;
    }
    else
    {
        std::cout << "[FAIL] " << testName << "\n";
        std::cout << "   Got:      ";
        for (int x : input)
            std::cout << x << " ";
        std::cout << "\n   Expected: ";
        for (int x : expected)
            std::cout << x << " ";
        std::cout << "\n";
        return false;
    }
}

bool runTest2(const std::string &testName, std::vector<int> input, const std::vector<int> &expected)
{
    insertionsortdesc(input);
    if (input == expected)
    {
        std::cout << "[PASS] " << testName << "\n";
        return true;
    }
    else
    {
        std::cout << "[FAIL] " << testName << "\n";
        std::cout << "   Got:      ";
        for (int x : input)
            std::cout << x << " ";
        std::cout << "\n   Expected: ";
        for (int x : expected)
            std::cout << x << " ";
        std::cout << "\n";
        return false;
    }
}

void test()
{
    int passed = 0, total = 0;

    // Test cases
    total++;
    if (runTest("Empty array", {}, {}))
        passed++;
    total++;
    if (runTest("Single element", {5}, {5}))
        passed++;
    total++;
    if (runTest("Already sorted", {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}))
        passed++;
    total++;
    if (runTest("Reverse sorted", {5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}))
        passed++;
    total++;
    if (runTest("Random order", {3, 1, 4, 5, 2}, {1, 2, 3, 4, 5}))
        passed++;
    total++;
    if (runTest("With duplicates", {4, 2, 4, 3, 2}, {2, 2, 3, 4, 4}))
        passed++;
    total++;
    if (runTest("All equal", {7, 7, 7, 7}, {7, 7, 7, 7}))
        passed++;
    total++;
    if (runTest("Negative numbers", {-3, -1, -4, 2, 0}, {-4, -3, -1, 0, 2}))
        passed++;
    total++;
    if (runTest("Mixed positives & negatives", {3, -2, -5, 1, 0}, {-5, -2, 0, 1, 3}))
        passed++;
    total++;
    if (runTest("Large numbers", {1000, 50, 5000, 1}, {1, 50, 1000, 5000}))
        passed++;

    std::cout << "\nSummary: " << passed << " / " << total << " tests passed.\n";
}

void test2()
{
    int passed = 0, total = 0;

    // Test cases
    total++;
    if (runTest2("Empty array", {}, {}))
        passed++;
    total++;
    if (runTest2("Single element", {5}, {5}))
        passed++;
    total++;
    if (runTest2("Already sorted desc", {5, 4, 3, 2, 1}, {5, 4, 3, 2, 1}))
        passed++;
    total++;
    if (runTest2("Reverse sorted (asc)", {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}))
        passed++;
    total++;
    if (runTest2("Random order", {3, 1, 4, 5, 2}, {5, 4, 3, 2, 1}))
        passed++;
    total++;
    if (runTest2("With duplicates", {4, 2, 4, 3, 2}, {4, 4, 3, 2, 2}))
        passed++;
    total++;
    if (runTest2("All equal", {7, 7, 7, 7}, {7, 7, 7, 7}))
        passed++;
    total++;
    if (runTest2("Negative numbers", {-3, -1, -4, 2, 0}, {2, 0, -1, -3, -4}))
        passed++;
    total++;
    if (runTest2("Mixed positives & negatives", {3, -2, -5, 1, 0}, {3, 1, 0, -2, -5}))
        passed++;
    total++;
    if (runTest2("Large numbers", {1000, 50, 5000, 1}, {5000, 1000, 50, 1}))
        passed++;

    std::cout << "\nSummary: " << passed << " / " << total << " tests passed.\n";
}

int main()
{
    test();
    test2();
    vector<int> vec = {31, 41, 59, 26, 41, 58};
    insertionsortasc(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    insertionsortdesc(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}
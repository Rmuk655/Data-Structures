#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

void insertionsortasc(vector<int> &vec)
{
    for (int i = 1; i < vec.size(); i++)
    {
        int key = vec[i], j = i - 1;
        while (j >= 0 && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
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

int main()
{
    test();
    vector<int> vec = {10, -23, 4, 0, -56, 13};
    insertionsortasc(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}
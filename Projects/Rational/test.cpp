#include <iostream>
#include <sstream>
#include "Rational.h"
#include "test.h"
#include <cassert>

bool checkResult(const std::string &actual, const std::string &expected, const std::string &testName)
{
    if (actual != expected)
    {
        std::cerr << "Test failed: " << testName << "\nExpected: " << expected << "\nActual: " << actual << std::endl;
        return false;
    }
    return true;
}

int test::basictests()
{
    bool allPassed = true;
    Rational r1(1, 2), r2(3, 4);

    std::ostringstream oss;
    oss << (r1 + r2);
    allPassed &= checkResult(oss.str(), "5/4", "1/2 + 3/4"); // 1/2 + 3/4 = 2/4 + 3/4 = 5/4
    oss.str("");
    oss.clear();

    oss << (r1 - r2);
    allPassed &= checkResult(oss.str(), "-1/4", "1/2 - 3/4"); // 1/2 - 3/4 = 2/4 - 3/4 = -1/4
    oss.str("");
    oss.clear();

    oss << (r1 * r2);
    allPassed &= checkResult(oss.str(), "3/8", "1/2 * 3/4"); // 1/2 * 3/4 = 3/8
    oss.str("");
    oss.clear();

    try
    {
        oss << (r1 / r2);
        allPassed &= checkResult(oss.str(), "2/3", "1/2 / 3/4"); // (1/2) / (3/4) = (1/2)*(4/3) = 4/6 = 2/3
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Unexpected exception in test: 1/2 / 3/4" << std::endl;
        allPassed = false;
    }

    return allPassed ? 0 : 1;
}

int test::advancedtests()
{
    bool allPassed = true;
    Rational r1(2, -10), r2(4, -20);

    std::ostringstream oss;
    oss << (r1 + r2);
    allPassed &= checkResult(oss.str(), "-2/5", "2/-10 + 4/-20"); // 2/-10 + 4/-20 = -1/5 + -1/5 = -2/5
    oss.str("");
    oss.clear();

    oss << (r1 - r2);
    allPassed &= checkResult(oss.str(), "0", "2/-10 - 4/-20"); // -1/5 - (-1/5) = 0
    oss.str("");
    oss.clear();

    oss << (r1 * r2);
    allPassed &= checkResult(oss.str(), "1/25", "2/-10 * 4/-20"); // (2/-10)*(4/-20) = (2*4)/(-10*-20) = 8/200 = 1/25
    oss.str("");
    oss.clear();

    try
    {
        oss << (r1 / r2);
        allPassed &= checkResult(oss.str(), "1", "2/-10 / 4/-20"); // (2/-10)/(4/-20) = (2/-10)*(-20/4) = (2*-20)/(-10*4) = -40/-40 = 1
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Unexpected exception in test: 2/-10 / 4/-20" << std::endl;
        allPassed = false;
    }

    return allPassed ? 0 : 1;
}

int test::boundarytests()
{
    bool allPassed = true;
    Rational r1(-1, 2), r2(0, -4);

    std::ostringstream oss;
    oss << (r1 + r2);
    allPassed &= checkResult(oss.str(), "-1/2", "-1/2 + 0/-4"); // -1/2 + 0 = -1/2
    oss.str("");
    oss.clear();

    oss << (r1 - r2);
    allPassed &= checkResult(oss.str(), "-1/2", "-1/2 - 0/-4"); // -1/2 - 0 = -1/2
    oss.str("");
    oss.clear();

    oss << (r1 * r2);
    allPassed &= checkResult(oss.str(), "0", "-1/2 * 0/-4"); // -1/2 * 0 = 0
    oss.str("");
    oss.clear();

    try
    {
        oss << (r1 / r2);
        std::cerr << "Test failed: -1/2 / 0/-4\nExpected: exception\nActual: " << oss.str() << std::endl;
        allPassed = false;
    }
    catch (const std::invalid_argument &e)
    {
        // Expected exception
    }

    return allPassed ? 0 : 1;
}

int test::additionaltestcases()
{
    bool allPassed = true;

    Rational r1(3, 1), r2(1, 2);
    std::ostringstream oss;
    oss << (r1 + r2);
    allPassed &= checkResult(oss.str(), "7/2", "3 + 1/2"); // 3 + 1/2 = 6/2 + 1/2 = 7/2
    oss.str("");
    oss.clear();

    Rational r3(0, 5), r4(2, 3);
    oss << (r3 + r4);
    allPassed &= checkResult(oss.str(), "2/3", "0 + 2/3"); // 0 + 2/3 = 2/3
    oss.str("");
    oss.clear();

    Rational r5(-2, 4), r6(1, -2);
    oss << (r5 + r6);
    allPassed &= checkResult(oss.str(), "-1", "-1/2 + (-1/2)"); // -1/2 + -1/2 = -1
    oss.str("");
    oss.clear();

    Rational r7(7, 4), r8(3, 4);
    oss << (r7 + r8);
    allPassed &= checkResult(oss.str(), "5/2", "7/4 + 3/4"); // 7/4 + 3/4 = 10/4 = 5/2
    oss.str("");
    oss.clear();

    Rational r9(1, 2), r10(1, 3), r11(1, 6);
    Rational result = r9 + r10 - r11;
    oss << result;
    allPassed &= checkResult(oss.str(), "2/3", "1/2 + 1/3 - 1/6"); // 1/2 + 1/3 = 3/6 + 2/6 = 5/6; 5/6 - 1/6 = 4/6 = 2/3
    oss.str("");
    oss.clear();

    Rational r12(0, 1), r13(5, 6);
    oss << (r12 * r13);
    allPassed &= checkResult(oss.str(), "0", "0 * 5/6"); // 0 * 5/6 = 0
    oss.str("");
    oss.clear();

    Rational r14(3, 4), r15(1, 2);
    oss << (r14 / r15);
    allPassed &= checkResult(oss.str(), "3/2", "3/4 / 1/2"); // (3/4) / (1/2) = (3/4)*(2/1) = 6/4 = 3/2
    oss.str("");
    oss.clear();

    Rational r16(2, 4), r17(1, 2);
    bool equalityCheck = (r16.getNumerator() == r17.getNumerator() && r16.getDenominator() == r17.getDenominator());
    allPassed &= checkResult(equalityCheck ? "True" : "False", "True", "2/4 == 1/2"); // 2/4 reduces to 1/2

    try
    {
        Rational r18(1, 2), r19(0, 1);
        Rational div = r18 / r19;
        std::cerr << "Test failed: 1/2 / 0\nExpected: exception\nActual: " << div << std::endl;
        allPassed = false;
    }
    catch (const std::invalid_argument &e)
    {
        // Expected exception
    }

    return allPassed ? 0 : 1;
}

void testComparisonOperators()
{
    Rational r1(1, 2);
    Rational r2(2, 4);
    Rational r3(3, 4);

    assert(r1 == r2);
    assert(!(r1 != r2));
    assert(r1 < r3);
    assert(r1 <= r2);
    assert(r3 > r2);
    assert(r3 >= r1);
    assert(Rational(1, 2) == Rational(2, 4));
    assert(Rational(3, 5) != Rational(2, 5));
    assert(Rational(1, 3) < Rational(2, 3));
    assert(Rational(3, 6) <= Rational(1, 2));
    assert(Rational(-1, 2) < Rational(1, 2));
    assert(Rational(0, 1) == Rational(0, 5));
}

int test::runtests()
{
    bool allPassed = true;
    allPassed &= (basictests() == 0);
    allPassed &= (advancedtests() == 0);
    allPassed &= (boundarytests() == 0);
    allPassed &= (additionaltestcases() == 0);
    testComparisonOperators();

    if (allPassed)
    {
        std::cout << "All tests passed successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Some tests failed. Please check the output above." << std::endl;
    }

    return allPassed ? 0 : 1;
}
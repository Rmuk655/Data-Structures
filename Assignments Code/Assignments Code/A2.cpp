#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <random>

#define MAX_ATTEMPTS 1000
using namespace std;

class Person
{
public:
    long long int NHS_number;
    string first_name;
    string email;
    string gender;
    Person(long long int _NHS_number = 0, string _first_name = "", string _email = "", string _gender = "")
        : NHS_number(_NHS_number), first_name(_first_name), email(_email), gender(_gender) {};
    friend ostream &operator<<(ostream &os, const Person &p)
    {
        os << "NHS Number: " << p.NHS_number << ", "
           << "First Name: " << p.first_name << ", "
           << "Email: " << p.email << ", "
           << "Gender: " << p.gender << endl;
        return os;
    }
};

class DotProductHashFunction
{
private:
    unsigned long long prime;           // a large prime
    unsigned int numBuckets;            // number of buckets
    vector<long long> dotProductCoeffs; // Random set of "r" dotProduct Coeffs.
    int r;                              // Computed based on universe size ; u = M^r

    unsigned int computeR(int base, long long universeSize)
    {
        // Example implementation: r = ceil(log_base(universeSize))
        return static_cast<unsigned int>(ceil(log(static_cast<double>(universeSize)) / log(static_cast<double>(base))));
    }

    vector<int> extract(long long int key, int r, int base)
    {
        vector<int> result;
        long long int key_copy = key;
        int len = 0;
        while (key_copy >= 1)
        {
            key_copy = key_copy / base;
            len++;
        }
        result.resize(len);
        key_copy = key;
        int k = 0;
        while (key_copy >= 1)
        {
            result[len - 1 - k] = key_copy % base;
            key_copy = key_copy / base;
            k++;
        }
        vector<int> extracted(r, 0);
        int a = 0, c = 0, e = 0;
        for (int i = 0; i < len; i = i + ceil((float)len / (float)r))
        {
            for (int j = ceil((float)len / (float)r) - 1; j >= 0; j--)
            {
                if (i + j < len && c == 0)
                {
                    extracted[a] = extracted[a] + pow(10, ceil((float)len / (float)r) - 1 - j) * result[j + i];
                }
                else if (i + j >= len)
                {
                    c = 1;
                }
                else if (i + j < len && c == 1)
                {
                    extracted[a] = extracted[a] + pow(10, e) * result[j + i];
                    e++;
                }
            }
            key = key % static_cast<long long int>(pow(10, ceil((float)len / (float)r)));
            a++;
        }
        return extracted;
    }

    long long int cphash(vector<int> extracted_numbers)
    {
        long long int hash = 0;
        for (int i = 0; i < extracted_numbers.size(); i++)
        {
            hash = hash + extracted_numbers[i] * dotProductCoeffs[i];
            hash = hash % prime; // Ensure the hash does not overflow
        }
        hash = hash % numBuckets; // Modulo operation to keep the hash within bounds
        if (hash < 0 || hash > numBuckets - 1)
        {
            printf("Hash out of bounds: %lld, resetting to 0\n", hash);
            hash = 0; // Reset to 0 if out of bounds
        }
        return hash;
    }

public:
    int base;               // key will be converted to this base
    long long universeSize; // Default 10^10
    // Default constructor
    DotProductHashFunction()
    {
        // Provide some default values or leave uninitialized if appropriate
    }
    // constructor
    DotProductHashFunction(int nBuckets, long long _universeSize = 10000000000LL, int _base = 11)
        : numBuckets(nBuckets), universeSize(_universeSize), base(_base)
    {
        prime = 9999999967LL; // a large prime
        // write a  function to Compute r based on universe size and base
        r = computeR(base, universeSize);
        // Add Error handling and set r= 33 if r goes out of bounds

        // initiatilize dotProductCoeffs of size r to random numbers from 0 to base -1
        random_device rd;
        mt19937 gen(rd());                        // Seed with a fixed value for reproducibility
        uniform_int_distribution<> dis(0, prime); // Adjust the range as needed

        for (int i = 0; i < r; i++)
        {
            int coeff = dis(gen);
            dotProductCoeffs.push_back(coeff);
        }
    }

    unsigned int hash(long long int NHS_number)
    {
        // long long int n = baseconverter(NHS_number, base);
        vector<int> number = extract(NHS_number, r, base);
        unsigned int bucket = cphash(number);
        return bucket; // Ensure the bucket is within the range of numBuckets
    }

    void testextract()
    {
        // Case 1
        {
            long long int key = 123456;
            int r = 2, base = 10;
            vector<int> result = extract(key, r, base);
            assert(result.size() == 2);
            assert(result[0] == 123);
            assert(result[1] == 456);
        }

        // Case 2
        {
            long long int key = 70001;
            int r = 2, base = 10;
            vector<int> result = extract(key, r, base);
            assert(result.size() == 2);
            assert(result[0] == 700);
            assert(result[1] == 01);
        }

        // Case 3
        {
            long long int key = 990;
            int r = 2, base = 11;
            vector<int> result = extract(key, r, base);
            assert(result.size() == 2); // 990 in base 11 = 820, break into 2-digit chunks
            assert(result[0] == 82);
            assert(result[1] == 0);
        }

        // Case 4
        {
            long long int key = 0;
            int r = 2, base = 10;
            vector<int> result = extract(key, r, base);
            assert(result.size() == 2);
            assert(result[0] == 0);
            assert(result[1] == 0);
        }

        // Case 5
        {
            long long int key = 1023;
            int r = 3, base = 2;
            vector<int> result = extract(key, r, base);
            assert(!result.empty()); // Should produce a vector of 3-bit binary groups
            assert(result.size() == 3);
            assert(result[0] == 1111);
            assert(result[1] == 1111);
            assert(result[2] == 11);
        }

        // Case 6
        {
            long long int key = 987654321;
            int r = 3, base = 101;
            vector<int> result = extract(key, r, base);
            // for (int i = 0; i < result.size(); i++)
            // {
            //     cout << "Result[" << i << "]: " << result[i] << endl;
            // }
            assert(!result.empty()); // Should produce a vector of 3-bit binary groups
            assert(result.size() == 3);
            assert(result[0] == 139);
            assert(result[1] == 646);
            assert(result[2] == 66);
        }
        cout << "All test cases passed!" << endl;
    }
};

class Bucket
{
public:
    vector<Person> table;
    vector<Person> secondary_hash; // Random set of "r" dotProduct Coeffs.
    DotProductHashFunction h2;
};

class PerfectHashTable
{
public:
    vector<Bucket> buckets; // First-level buckets
    // Each bucket contains a second-level hash table with its own hash function
    int numBuckets; // Number of first-level buckets
    DotProductHashFunction h1;
    PerfectHashTable(int nBuckets, DotProductHashFunction &hashFunction)
        : numBuckets(nBuckets), h1(hashFunction) // Initialize with the provided hash function
    {
        buckets.resize(numBuckets); // Resize the buckets vector to the number of buckets
    }
    int build(const std::vector<Person> &records)
    {
        long long int sum = 0, iter = 0;
        // vector<vector<int>> sec_hash; // Random set of "r" dotProduct Coeffs.

        while (true)
        {
            DotProductHashFunction dphash(numBuckets, h1.universeSize, h1.base); // Example initialization
            h1 = dphash;
            for (int i = 0; i < records.size(); i++)
            {
                unsigned int bucket = dphash.hash(records[i].NHS_number);
                if (records[i].NHS_number == 3077399474)
                {
                    cout << "Bucket number: " << bucket << " Key: " << records[i].NHS_number << endl;
                }
                if (bucket < 0 || bucket >= numBuckets)
                {
                    cout << "Hash out of bounds for NHS Number: " << records[i].NHS_number << endl;
                    continue; // Skip if the hash is out of bounds
                }
                // cout << "NHS Number: " << dictionary[i].NHS_number << ", Bucket: " << bucket << endl;
                buckets[bucket].table.push_back(records[i]); // Add the record to the corresponding bucket
            }
            for (int i = 0; i < buckets.size(); i++)
            {
                if ((int)buckets[i].table.size() == 0)
                {
                    continue; // Skip empty buckets
                }
                sum = sum + (int)buckets[i].table.size() * (int)buckets[i].table.size();
                // cout << "Bucket " << i << ": " << (int)buckets[i].table.size() << " sum: " << sum << endl;
            }
            iter++;
            // cout << "Iteration: " << iter << " Sum: " << sum << endl;
            if (sum < numBuckets)
            {
                break;
            }
            sum = 0;
        }

        // cout << "Number of iterations: " << iter << endl;

        bool collision = false;
        int num_collisions = 0, max_collisions = 0;
        for (int i = 0; i < buckets.size(); i++)
        {
            if ((int)buckets[i].table.size() <= 1)
            {
                continue; // Skip empty or 1 element buckets
            }
            int no_of_attempts = 0;
            if (num_collisions > max_collisions)
            {
                max_collisions = num_collisions;
            }
            num_collisions = 0;
            do
            {
                collision = false;
                // cout << "Bucket " << i << ": " << (int)buckets[i].table.size() << endl;
                int size = buckets[i].table.size();
                buckets[i].h2 = DotProductHashFunction(10 * size * size, h1.universeSize, h1.base);
                buckets[i].secondary_hash.resize(10 * size * size); // Resize the secondary hash table

                for (int j = 0; j < size; j++)
                {
                    unsigned int sec_bucket = buckets[i].h2.hash(buckets[i].table[j].NHS_number);
                    // cout << "Secondary bucket number: " << sec_bucket << endl;

                    if (sec_bucket < 0 || sec_bucket >= 10 * size * size)
                    {
                        cout << "Secondary hash out of bounds for NHS Number: " << buckets[i].table[j].NHS_number << endl;
                        continue; // Skip if the secondary hash is out of bounds
                    }

                    if (buckets[i].secondary_hash[sec_bucket].NHS_number != 0)
                    {
                        num_collisions++;
                        cout << "Collision detected in secondary hash for NHS Number: " << buckets[i].table[j].NHS_number << endl;
                        collision = true;
                        no_of_attempts++;
                        buckets[i].secondary_hash.clear();
                        cout << "NHS Number: " << buckets[i].table[j].NHS_number << " No of attempts: " << no_of_attempts << endl;
                        // Example of using NHS_number as a coefficient
                        break;
                    }

                    buckets[i].secondary_hash[sec_bucket] = buckets[i].table[j]; // Add the record to the second-level table
                    if (buckets[i].table[j].NHS_number == 3077399474)
                    {
                        cout << "Bucket number: " << sec_bucket << " Key: " << buckets[i].table[j].NHS_number << endl;
                    }
                    // cout << "NHS Number: " << buckets[i].table[j].NHS_number << " No of attempts: " << no_of_attempts << endl;
                }
            } while (collision == true && no_of_attempts < MAX_ATTEMPTS);
        }
        cout << "Maximum no of collisions: " << max_collisions << endl;
        return 0; // Return 0 to indicate successful build
    }
    Person *search(long long int key)
    {
        unsigned int m = h1.hash(key);
        if (m >= buckets.size())
            return nullptr;
        Bucket &bucket = buckets[m];
        if (buckets[m].table.size() == 0)
        {
            return nullptr;
        }
        else if (buckets[m].table.size() == 1)
        {
            const Person &candidate1 = buckets[m].table[0];
            return const_cast<Person *>(&candidate1);
        }
        unsigned int n = bucket.h2.hash(key); // Second-level hash
        if (n >= bucket.secondary_hash.size())
            return nullptr;
        const Person &candidate = bucket.secondary_hash[n];
        if (candidate.NHS_number == key)
        {
            // Match found
            return const_cast<Person *>(&candidate);
        }
        else
        {
            // Key not found
            return nullptr;
        }
    } // Placeholder for search function
};

void loaddictionary(vector<struct Person> &dictionary)
{
    ifstream file("Data.csv");

    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    std::getline(file, line);
    while (getline(file, line))
    {
        struct Person person;
        stringstream ss(line);
        long long NHS_number;
        string NHS_number_string, first_name, email, gender, sl_number_string;

        getline(ss, sl_number_string, ','); // Skip the SL number
        getline(ss, NHS_number_string, ',');
        getline(ss, first_name, ',');
        getline(ss, email, ',');
        getline(ss, gender, ',');

        NHS_number = stoll(NHS_number_string);
        person.NHS_number = NHS_number;
        person.first_name = first_name;
        person.email = email;
        person.gender = gender;

        dictionary.push_back(person);
    }
    file.close();
}

void printdictionary(const vector<struct Person> &dictionary)
{
    for (const auto &person : dictionary)
    {
        cout << person << endl;
    }
}

int main()
{
    vector<Person> dictionary;
    loaddictionary(dictionary);
    unsigned int numrecords = dictionary.size(), numBuckets = 5 * numrecords;
    unsigned long long int universeSize = pow(10, 10);
    int base = 5;

    DotProductHashFunction dphash(numBuckets, universeSize, base); // Example initialization
    // dphash.testbaseconverter();
    dphash.testextract();

    PerfectHashTable pht(numBuckets, dphash); // Set the number of buckets in the perfect hash table
    pht.build(dictionary);                    // Build the perfect hash table with the dictionary
    long long int NHS_no;
    cout << "Enter the NHS_number: ";
    cin >> NHS_no;
    Person *p = pht.search(NHS_no);
    if (p != nullptr)
    {
        cout << *p << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
}
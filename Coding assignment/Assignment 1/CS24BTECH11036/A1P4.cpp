#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <random>

// We define a macros MAX_ATTEMPTS so that we do not exceed memory or time limits.
#define MAX_ATTEMPTS 1000
using namespace std;

// We create a class Person which stores the respective NHS_number, first_name, email, gender of each person instance.
class Person
{
public:
    long long int NHS_number;
    string first_name;
    string email;
    string gender;
    // Initializing a new member of class Person with 0, empty strings respectively..
    Person(long long int _NHS_number = 0, string _first_name = "", string _email = "", string _gender = "")
        : NHS_number(_NHS_number), first_name(_first_name), email(_email), gender(_gender) {};
};

// We create a class DotProductHashFunction which stores important numbers needed for the hashing function.
class DotProductHashFunction
{
private:
    unsigned long long prime;           // a large prime
    unsigned int numBuckets;            // number of buckets
    vector<long long> dotProductCoeffs; // Random set of "r" dotProduct Coeffs.
    int r;                              // Computed based on universe size ; u = M^r

    // Function designed to compute and return the value of r.
    // M^r = U, r = log U/log M
    unsigned int computeR(int base, long long universeSize)
    {
        // Example implementation: r = ceil(log_base(universeSize))
        return static_cast<unsigned int>(ceil(log(static_cast<double>(universeSize)) / log(static_cast<double>(base))));
    }

    // Function extract breaks down a key in base b so that we can perform dot product hash function for the digits of
    // the key in base b by storing it in result.
    vector<int> extract(long long int key, int r, int base)
    {
        // We store result in the vector result.
        vector<int> result;
        // We store a copy of the key in key_copy as we will perform operations on key_copy changing it's value.
        long long int key_copy = key;
        // We calculate and store the number of digits in base r representation for key.
        int len = 0;
        while (key_copy >= 1)
        {
            key_copy = key_copy / base;
            len++;
        }
        // Resizing the result vector to store len number of digits.
        result.resize(len);
        key_copy = key;
        // We use int k to store the correct digit in the correct position in the vector.
        int k = 0;
        // We store the base r representation as len number of entries in vector result.
        while (key_copy >= 1)
        {
            result[len - 1 - k] = key_copy % base;
            key_copy = key_copy / base;
            k++;
        }
        // We initialize a vector extracted of size r with all 0s.
        vector<int> extracted(r, 0);
        // Index -> index of extracted which we are filling.
        int index = 0;
        // Flag -> 0 means normal case, 1 means we have gone past the last element of the vector.
        // So we might have missed some numbers in the vector in between.
        int flag = 0;
        // Leftover -> no of leftover digits remaining which we did not process. This is to ensure every digit is processed.
        int leftover = 0;
        // We split the vector result into blocks of size len/r.
        for (int i = 0; i < len; i = i + ceil((float)len / (float)r))
        {
            // We iterate over each block backwards.
            for (int j = ceil((float)len / (float)r) - 1; j >= 0; j--)
            {
                // If we are at normal indices < len (no of digits).
                if (i + j < len && flag == 0)
                {
                    // We store the value of the digit multiplied by its place value.
                    extracted[index] = extracted[index] + pow(10, ceil((float)len / (float)r) - 1 - j) * result[j + i];
                }
                // If we have crossed the last index (len: no of digits), we set flag to 1.
                else if (i + j >= len)
                {
                    flag = 1;
                }
                // If we crossed the last index in the past but presently we are within bounds.
                else if (i + j < len && flag == 1)
                {
                    // We store the value of the digit multiplied by its place value.
                    // Since we have gone out of bounds before, we are dealing with left overs currently.
                    extracted[index] = extracted[index] + pow(10, leftover) * result[j + i];
                    leftover++;
                }
            }
            // We remove the r digits which we have already processed and focus on the next r digits of the key.
            key = key % static_cast<long long int>(pow(10, ceil((float)len / (float)r)));
            index++;
        }
        // Return the vector for dot product hashing.
        return extracted;
    }

    // cphash functions takes the extract numbers and performs the dot product hash on it.
    long long int cphash(vector<int> extracted_numbers)
    {
        // Performing dot product hash and generating the hash result and storing it in hash.
        long long int hash = 0;
        for (int i = 0; i < extracted_numbers.size(); i++)
        {
            hash = hash + extracted_numbers[i] * dotProductCoeffs[i];
            hash = hash % prime;
        }
        // Modulo operation to keep the hash within bounds.
        hash = hash % numBuckets;
        // Checking if the hash is within bounds or not.
        if (hash < 0 || hash > numBuckets - 1)
        {
            printf("Hash out of bounds: %lld, resetting to 0\n", hash);
            hash = 0; // Reset to 0 if out of bounds
        }
        return hash;
    }

public:
    int base;               // Key will be converted to this base
    long long universeSize; // Default value is 10^10

    // Default constructor for this class.
    DotProductHashFunction()
    {
        // Provide some default values or leave uninitialized if appropriate
    }

    // Constructor for an instance of this class.
    DotProductHashFunction(int nBuckets, long long _universeSize = 10000000000LL, int _base = 11)
        : numBuckets(nBuckets), universeSize(_universeSize), base(_base)
    {
        prime = 9999999967LL; // a large prime
        // We write a  function to compute r based on universe size and base
        r = computeR(base, universeSize);

        // We initiatilize dotProductCoeffs of size r to random numbers from 0 to base - 1
        random_device rd;
        // We seed with a fixed value for reproducibility
        mt19937 gen(rd());
        // We adjust the range as needed
        uniform_int_distribution<> dis(0, prime);

        // We use the above given random seed and generate random r numbers used for dotProduct hashing.
        // We store these r numbers in a vector<int> dotProductCoeffs for calculations.
        for (int i = 0; i < r; i++)
        {
            int coeff = dis(gen);
            dotProductCoeffs.push_back(coeff);
        }
    }

    // Hash function extracts the numbers, stores it in a vector and performs the hash function on the vector to
    // return the bucket in which the data corresponding to the given NHS_number will be stored in.
    unsigned int hash(long long int NHS_number)
    {
        vector<int> number = extract(NHS_number, r, base);
        unsigned int bucket = cphash(number);
        return bucket;
    }

    // testextract() function which contains a set of test cases which verifies if the code is correct or not.
    // void testextract()
    // {
    //     // Case 1
    //     {
    //         long long int key = 123456;
    //         int r = 2, base = 10;
    //         vector<int> result = extract(key, r, base);
    //         assert(result.size() == 2);
    //         assert(result[0] == 123);
    //         assert(result[1] == 456);
    //     }

    //     // Case 2
    //     {
    //         long long int key = 70001;
    //         int r = 2, base = 10;
    //         vector<int> result = extract(key, r, base);
    //         assert(result.size() == 2);
    //         assert(result[0] == 700);
    //         assert(result[1] == 01);
    //     }

    //     // Case 3
    //     {
    //         long long int key = 990;
    //         int r = 2, base = 11;
    //         vector<int> result = extract(key, r, base);
    //         assert(result.size() == 2); // 990 in base 11 = 820, break into 2-digit chunks
    //         assert(result[0] == 82);
    //         assert(result[1] == 0);
    //     }

    //     // Case 4
    //     {
    //         long long int key = 0;
    //         int r = 2, base = 10;
    //         vector<int> result = extract(key, r, base);
    //         assert(result.size() == 2);
    //         assert(result[0] == 0);
    //         assert(result[1] == 0);
    //     }

    //     // Case 5
    //     {
    //         long long int key = 1023;
    //         int r = 3, base = 2;
    //         vector<int> result = extract(key, r, base);
    //         assert(!result.empty()); // Should produce a vector of 3-bit binary groups
    //         assert(result.size() == 3);
    //         assert(result[0] == 1111);
    //         assert(result[1] == 1111);
    //         assert(result[2] == 11);
    //     }

    //     // Case 6
    //     {
    //         long long int key = 987654321;
    //         int r = 3, base = 101;
    //         vector<int> result = extract(key, r, base);
    //         // for (int i = 0; i < result.size(); i++)
    //         // {
    //         //     cout << "Result[" << i << "]: " << result[i] << endl;
    //         // }
    //         assert(!result.empty()); // Should produce a vector of 3-bit binary groups
    //         assert(result.size() == 3);
    //         assert(result[0] == 139);
    //         assert(result[1] == 646);
    //         assert(result[2] == 66);
    //     }
    //     cout << "All test cases passed!" << endl;
    // }
};

// We define a class Bucket which is used to store the hash values for both primary hash, dot product values for secondary hash.
class Bucket
{
public:
    // Stores the list of keys which collided in first hash.
    vector<Person> table;
    // We use it to store the rehashed keys which collided in first hash using secondary hash.
    vector<Person> secondary_hash;
    // Secondary hash function for each bucket involved in the collision.
    DotProductHashFunction h2;
};

// We define a class PerfectHashTable which is used to perform both primary and secondary hash.
class PerfectHashTable
{
public:
    vector<Bucket> buckets; // First-level buckets
    // Each bucket contains a second-level hash table with its own hash function
    int numBuckets; // Number of first-level buckets
    DotProductHashFunction h1;
    // We initialize with the provided hash function
    PerfectHashTable(int nBuckets, DotProductHashFunction &hashFunction)
        : numBuckets(nBuckets), h1(hashFunction)
    {
        // We resize the buckets vector to the number of buckets
        buckets.resize(numBuckets);
    }
    // build function is used to build the dictionary using primary and secondary hash.
    int build(const std::vector<Person> &records)
    {
        // Sum stores sigma li^2 and check if it < num_buckets, else rehash.
        // Iter stores the number of iterations of the while loop to make sure it doesnt exceed max_iterations.
        long long int sum = 0, iter = 0;

        // Keep hashing until sum < num_buckets or iter < max_iterations.
        while (true)
        {
            // We initialize the hash function and store it in h1.
            DotProductHashFunction dphash(numBuckets, h1.universeSize, h1.base);
            h1 = dphash;
            // For each record, we hash the record, get its hash value and store it in the bucket class's table.
            for (int i = 0; i < records.size(); i++)
            {
                unsigned int bucket = dphash.hash(records[i].NHS_number);
                if (bucket < 0 || bucket >= numBuckets)
                {
                    // Skip if the hash is out of bounds
                    continue;
                }
                // Add the record to the corresponding bucket
                buckets[bucket].table.push_back(records[i]);
            }
            // After hashing and storing the hashed keys in buckets, we find the sum = sigma li^2.
            for (int i = 0; i < buckets.size(); i++)
            {
                if ((int)buckets[i].table.size() == 0)
                {
                    // We skip empty buckets
                    continue;
                }
                sum = sum + (int)buckets[i].table.size() * (int)buckets[i].table.size();
            }
            iter++;
            // We check if the sum is less than the num_buckets. If it is we break, else we rehash entirely.
            if (sum < numBuckets)
            {
                break;
            }
            // Reinitialize sum to 0.
            sum = 0;
        }

        // We now check for collisions and perform secondary hash wherever collisions exist.
        bool collision = false;
        // We store the num_collisions so that we can secondary hash on the collided keys.
        // We calculate the max_collisions for our reference.
        int num_collisions = 0, max_collisions = 0;
        for (int i = 0; i < buckets.size(); i++)
        {
            if ((int)buckets[i].table.size() <= 1)
            {
                // Skip empty or 1 element buckets
                continue;
            }
            // We calculate the number of attempts so that we can rehash if the number of attempts exceeds max_attempts.
            int no_of_attempts = 0;
            // Updating max_collisions value.
            if (num_collisions > max_collisions)
            {
                max_collisions = num_collisions;
            }
            // We start with 0 collisions.
            num_collisions = 0;
            do
            {
                // We assume there is no collision.
                collision = false;
                // size is the number of elements involved in collision.
                int size = buckets[i].table.size();
                // For each bucket of a primary hash with 2 or more keys, we perform a secondary hash.
                buckets[i].h2 = DotProductHashFunction(10 * size * size, h1.universeSize, h1.base);
                // Resize the secondary hash table to 10 * li^2
                buckets[i].secondary_hash.resize(10 * size * size);

                // We loop through each key involved in collision.
                for (int j = 0; j < size; j++)
                {
                    // We get the bucket for each key through secondary hash.
                    unsigned int sec_bucket = buckets[i].h2.hash(buckets[i].table[j].NHS_number);

                    if (sec_bucket < 0 || sec_bucket >= 10 * size * size)
                    {
                        // Skip if the secondary hash is out of bounds, which indicates an error.
                        continue;
                    }

                    // If the NHS_number from a secondary bucket is non zero, indicates there is a collision in secondary hash.
                    if (buckets[i].secondary_hash[sec_bucket].NHS_number != 0)
                    {
                        // We have hit a key involved in a collision and re-hash it.
                        // We keep track of the number of collisions and set collision to true.
                        num_collisions++;
                        collision = true;
                        no_of_attempts++;
                        buckets[i].secondary_hash.clear();
                        break;
                    }
                    // Add the record to the second-level table
                    buckets[i].secondary_hash[sec_bucket] = buckets[i].table[j];
                }
            } while (collision == true && no_of_attempts < MAX_ATTEMPTS);
            // Loop till no collisions are present/no of attempts < max attempts.
        }
        return 0; // Return 0 to indicate successful build
    }

    // Main search function used to search for a given record based on the key = NHS_No.
    Person *search(long long int key)
    {
        // We perform primary hash and if m exceeds bucket size, it means that the NHS_No is not present.
        unsigned int m = h1.hash(key);
        if (m >= buckets.size())
            return nullptr;
        // If we hash a key to a bucket but find that the bucket has no elements, it means that the NHS_No is not present.
        Bucket &bucket = buckets[m];
        if (buckets[m].table.size() == 0)
        {
            return nullptr;
        }
        // If only 1 element exists from primary hash, then we return that struct person.
        else if (buckets[m].table.size() == 1)
        {
            const Person &candidate1 = buckets[m].table[0];
            return const_cast<Person *>(&candidate1);
        }
        // Otherwise we perform the secondary hash function to deal with collisions.
        unsigned int n = bucket.h2.hash(key); // Second-level hash
        // If it exceeds secondary hash bucket size, means that the NHS_No is invalid.
        if (n >= bucket.secondary_hash.size())
            return nullptr;
        const Person &candidate = bucket.secondary_hash[n];
        // If a match is found we return the candidate (as a struct Person* data type).
        if (candidate.NHS_number == key)
        {
            return const_cast<Person *>(&candidate);
        }
        // Else if key is not found, we return nullptr.
        // We print Key not found in the main function by checking if the returned person pointer is nullptr or not.
        else
        {
            return nullptr;
        }
    }
};

// Function used to read, extract information from the csv file and store it in a vector<struct Person>.
void loaddictionary(vector<struct Person> &dictionary)
{
    // Input file stream for the file Data.csv.
    ifstream file("Data.csv");

    // Safety if check to check if the file is open and if the input stream can read from it correctly or not.
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    // We extract each line separately and store it in a string line.
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        // We create a struct Person to store the info extracted from the line in it and append it to the vector<Person>.
        struct Person person;
        // Reading line from the string stream.
        stringstream ss(line);
        // Variables used to store the extracted info.
        long long NHS_number;
        string NHS_number_string, first_name, email, gender, sl_number_string;

        // We split the line by ',' and extract and store each info separately.
        getline(ss, sl_number_string, ','); // Skip the SL number
        getline(ss, NHS_number_string, ',');
        getline(ss, first_name, ',');
        getline(ss, email, ',');
        getline(ss, gender, ',');

        // Converting NHS_number_string to an long long integer as it is an long long int key for the dictionary.
        NHS_number = stoll(NHS_number_string);
        // Storing the elements in the person struct.
        person.NHS_number = NHS_number;
        person.first_name = first_name;
        person.email = email;
        person.gender = gender;

        // Pushing the struct person into the vector<struct Person> dictionary.
        dictionary.push_back(person);
    }
    // We close the file for safety purposes.
    file.close();
}

int main()
{
    // We extract and store the info from the file in the vector<Person> dictionary.
    vector<Person> dictionary;
    loaddictionary(dictionary);
    // We set the numBuckets as 5*numrecords (m = 5*n as per the question).
    unsigned int numrecords = dictionary.size(), numBuckets = 5 * numrecords;
    // We set universeSize and base value.
    unsigned long long int universeSize = pow(10, 10);
    int base = 5;

    // We initialize and instance of the DotProductHashFunction class with the above values.
    DotProductHashFunction dphash(numBuckets, universeSize, base); // Example initialization
    // dphash.testextract();

    // We set the number of buckets in the perfect hash table
    PerfectHashTable pht(numBuckets, dphash);
    // We now build the perfect hash table with the dictionary
    pht.build(dictionary);
    // Input for the NHS_no to be searched in the dictionary.
    long long int NHS_no;
    cin >> NHS_no;
    // We search for the person from the dictionary using the search function.
    Person *p = pht.search(NHS_no);
    // If the record is found, p != nullptr and hence we print the details of the person.
    if (p != nullptr)
    {
        cout << p->first_name << ", " << p->email << ", " << p->gender << endl;
    }
    // Else we print "Key not found" as instructed.
    else
    {
        cout << "Key not found" << endl;
    }
}
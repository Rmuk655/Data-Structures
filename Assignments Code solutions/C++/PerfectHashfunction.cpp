// Perfect Hash Table with Multiple Hash Functions and Performance Comparison
// This code implements a perfect hash table using multiple hash functions
// It allows for benchmarking different hash functions and their combinations

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <array>
#include <iomanip>

#define MAX_ATTEMPTS 1000

// Record stores NHS details
struct Record {
    long long id;
    std::string name;
    std::string email;
    std::string gender;
    bool isActive;
};


// Summary Table:
// Hash Function	Universal?	Randomized?	        Good in Practice?	    Notes
// MAD	            ✅ Yes	    ✅ Yes	            ✅ Yes	            Theoretical guarantees
// XOR-Based	    ❌ No	    ❌ No	            ⚠️ Sometimes	     Weak on structured keys
// Tabulation	    ❌ No*	    ✅ Yes	            ✅ Yes	            Strong empirical distribution
// Polynomial	    ✅*/❌	   ✅ Yes	           ✅ Yes	          Universal under certain setups
// Fibonacci	    ❌ No	    ❌ No	            ✅ Mostly	        Deterministic, good spacing
// DJBX33A	        ❌ No	    ❌ No	            ✅ For strings	    Fast but not collision resistant

// ✅ Summary Table
// Hash Type    	    Universal?	    Probabilistic Guarantee	                        Use Case
// MAD	                ✅ Yes	        2-universal (≤ 1/m collision)	               General-purpose universal hashing
// Polynomial Hash	    ✅ Yes	        2-universal	                                   Strings, rolling hashes
// Multiply-Shift	    ✅ Yes	        2-universal for w-bit keys	                   Fast hashing in RAM models
// Tabulation Hash	    ✅ Yes	        3-universal (can be boosted)	               High-speed hashing
// Pair-Multiply-Shift	✅ Yes	        Strongly universal	                           Composite keys (tuples, pairs)


// Supported hash function types
enum HashType {
    MAD,           // Multiply-Add-Divide: Good universal hash
    XOR_BASED,     // Bitwise XOR-based: Fast, weak for structured keys
    TABULATION,    // Precomputed table: Good empirical performance
    POLYNOMIAL,    // Polynomial rolling hash: Common for strings
    FIBONACCI,     // Knuth's Fibonacci hashing: Simple, decent spread
    DJBX33A,       // Classic string hash: used in Python/Perl
    JENKINS,       // Jenkins one-at-a-time: Excellent distribution
    IDENTITY,      // identity mod m: useful for testing bad hash
    LOWER_BITS,     // Picks lower few bits: prone to collisions
    CARTER_WEGMAN, // Polynomial hash mod large prime, strong universal
    TABULATION_SALTED,
    POLY_MOD_P_4WISE
};

// Convert HashType to string name
std::string hashTypeName(HashType type) {
    switch (type) {
        case MAD: return "MAD (Multiply-Add-Divide)";
        case XOR_BASED: return "XOR-Based";
        case TABULATION: return "Tabulation Hashing";
        case POLYNOMIAL: return "Polynomial Hashing";
        case FIBONACCI: return "Fibonacci Hashing";
        case DJBX33A: return "DJBX33A";
        case JENKINS: return "Jenkins";
        case IDENTITY: return "Identity Modulo";
        case LOWER_BITS: return "Lower Bits Only";
        case CARTER_WEGMAN: return "Carter-Wegman";
        case TABULATION_SALTED: return "Salted Tabulation";
        case POLY_MOD_P_4WISE: return "4-wise Poly Mod Prime";
        default: return "Unknown";
    }
}

long long random_range(long long max) {
    return (rand() % (max - 1)) + 1;
}

class HashFunction {
public:
    long long a, b, p;
    int m;
    HashType type;
    std::array<std::array<uint8_t, 256>, 8> tab; // for tabulation hashing
    std::array<uint8_t, 8> salt; // for salted tabulation
    // For 4-wise polynomial hashing, we need coefficients
    std::vector<long long> coeffs; // for 4-wise


    HashFunction(int _m, HashType type = MAD) : m(_m), type(type) {
        p = 1000000009LL;
        a = random_range(p);
        b = random_range(p);
        if (type == TABULATION) {
            for (auto& row : tab) for (int i = 0; i < 256; ++i) row[i] = rand() % 256;
        }
        if(type == TABULATION_SALTED) {
            for (int i = 0; i < 8; ++i) salt[i] = rand() % 256;
        }

        if (type == POLY_MOD_P_4WISE) {
            coeffs.resize(4);
            for (auto& c : coeffs)
                c = random_range(p);
        }
    }

    long long apply(long long key) const {
        switch (type) {
            case MAD:
            // Multiply-Add-Divide hashing
            // h(x) = ((a * x + b) mod p) mod m
            // where:
            // a is a random multiplier in [1, p-1]
            // b is a random offset in [0, p-1]
            // p is a large prime (1e9+9)
            // m is the size of the hash table
            // This method is fast and provides good distribution of hash values.
            // It is particularly effective for random or uniformly distributed keys.            
                return ((a * key + b) % p) % m;
            // XOR-based hashing uses bitwise operations to combine bits of the key
            // The key is shifted left and right, and the bits are XORed together  
            // The result is then taken modulo m to ensure it fits within the hash table size.
            // This method is fast and works well for many types of keys, but may not provide
            // the best distribution for structured keys.
            // It is particularly effective for random or uniformly distributed keys.
            case XOR_BASED:
                return (((key >> 5) ^ (key << 3)) % m);

            // Tabulation hashing uses a precomputed table to hash each byte of the key
            // The table is a 2D array of 8 rows and 256 columns,   
            // where each row corresponds to a byte of the key, and each column corresponds
            // to a byte value from 0 to 255.
            // The hash function applies the tabulation hash to the key, using the byte values
            // from the table to compute a hash value.
            // The hash value is computed by XORing the values from the table for each byte of the key.
            // The result is then taken modulo m to ensure it fits within the hash table size.
            // This method is efficient and provides good distribution of hash values.
            case TABULATION: {
                uint64_t result = 0;
                for (int i = 0; i < 8; ++i) result ^= tab[i][(key >> (i * 8)) & 0xFF];
                return result % m;
            }

            // The salt is an array of 8 bytes, one for each byte of the key
            // The salt is generated randomly and stored in the hash function object
            // The tabulation table is a 2D array of 8 rows and 256 columns
            // Each row corresponds to a byte of the key, and each column corresponds to a byte
            // value from 0 to 255
            // The table is filled with random byte values from 0 to 255
            // The hash function applies the tabulation hash to the key, using the salt to modify
            // the byte values before indexing into the table
            case TABULATION_SALTED: {
                uint64_t result = 0;
                for (int i = 0; i < 8; ++i)
                    result ^= tab[i][((key >> (i * 8)) & 0xFF) ^ salt[i]];
                return result % m;
            }
            // Polynomial hashing uses a polynomial function to compute the hash value
            // The polynomial function is defined as:
            // h(x) = (c₀ * aⁿ⁻¹ + c₁ * aⁿ⁻² + ... + cₙ₋₁) mod p mod m
            // where:
            // a is a random multiplier in [1, p-1]
            // p is a large prime (1e9+9)
            // m is the size of the hash table
            // c₀, c₁, ..., cₙ₋₁ are the coefficients of the polynomial
            // The coefficients are generated randomly and stored in the hash function object
            // The hash function applies the polynomial hash to the key, using the coefficients
            // to compute a hash value.
            // The hash value is computed by multiplying each byte of the key by the corresponding
            // coefficient, raising the result to the power of the byte index, and summing the  
            // results. The final result is then taken modulo p and m to ensure it fits within
            // the hash table size.
            case POLYNOMIAL: {
                std::string s = std::to_string(key);
                long long hash = 0, power = 1;
                for (char c : s) {
                    hash = (hash + (c * power) % m) % m;
                    power = (power * a) % m;
                }
                return hash;
            }

            // 4-wise polynomial hashing uses a polynomial function to compute the hash value
            // The polynomial function is defined as:
            // h(x) = (c₀ + c₁ * x + c₂ * x² + c₃ * x³) mod p mod m
            // where:
            // p is a large prime (1e9+9)
            // m is the size of the hash table
            // c₀, c₁, c₂, c₃ are the coefficients of the polynomial
            // The coefficients are generated randomly and stored in the hash function object
            // The hash function applies the polynomial hash to the key, using the coefficients to compute a hash value.
            
            case POLY_MOD_P_4WISE: {
                long long x = key % p;
                long long x2 = (x * x) % p;
                long long x3 = (x2 * x) % p;
                long long res = (coeffs[0] + coeffs[1] * x + coeffs[2] * x2 + coeffs[3] * x3) % p;
                return res % m;
            }
            // Fibonacci hashing uses a simple formula to compute the hash value
            // The formula is based on the golden ratio and is defined as:
            // h(x) = (x * 11400714819323198485) >> (64 - log2(m)) mod m
            // where:
            // 11400714819323198485 is a constant derived from the golden ratio
            // m is the size of the hash table
            // This method is fast 
            case FIBONACCI:
                return ((key * 11400714819323198485ull) >> (64 - (int)std::log2(m))) % m;
            // DJBX33A is a classic hash function used in many programming languages
            // It uses a simple formula to compute the hash value   
            // The formula is defined as:
            // h(x) = ((h << 5) + h) + c
            // where:
            // h is the current hash value (initialized to 5381)
            // c is the current character of the key
            // The hash value is computed by shifting the current hash value left by 5 bits,
            // adding the current hash value, and then adding the current character.
            // The result is then taken modulo m to ensure it fits within the hash table size.
            // This method is fast 
            case DJBX33A: {
                std::string s = std::to_string(key);
                unsigned long hash = 5381;
                for (char c : s) hash = ((hash << 5) + hash) + c;
                return hash % m;
            }

            // Jenkins hash function is a widely used hash function that provides good distribution
            // It uses a simple formula to compute the hash value
            // The formula is defined as:
            // h(x) = (h + c) + ((h << 10) ^    (h >> 6))
            // where:   
            // h is the current hash value (initialized to 0)
            // c is the current character of the key
            // The hash value is computed by adding the current character to the current hash value,
            // shifting the current hash value left by 10 bits, and XORing it with the current hash value
            // shifted right by 6 bits. The result is then taken modulo m to ensure it
            // fits within the hash table size.
            // This method is fast
            case JENKINS: {
                std::string s = std::to_string(key);
                uint32_t hash = 0;
                for (char c : s) {
                    hash += c;
                    hash += (hash << 10);
                    hash ^= (hash >> 6);
                }
                hash += (hash << 3);
                hash ^= (hash >> 11);
                hash += (hash << 15);
                return hash % m;
            }
            // Identity hashing simply returns the key modulo m
            // This method is useful for testing purposes, but it is not a good hash function
            case IDENTITY:
                return key % m;
            // Lower bits hashing uses only the lower bits of the key to compute the hash value
            // This method is prone to collisions, especially for structured keys
            case LOWER_BITS:
                return (key & (m - 1));
            // Carter-Wegman hashing is a polynomial hash function that uses a large prime number
            // to compute the hash value
            case CARTER_WEGMAN: {
                /*h(x) = (c₀ * aⁿ⁻¹ + c₁ * aⁿ⁻² + ... + cₙ₋₁) mod p mod m
                    Where:
                        a is a random multiplier in [1, p-1]
                        p is a large prime (already defined as 1e9+9)
                        m is the hash table size*/
                std::string s = std::to_string(key);
                long long hash = 0;
                long long base = a; // Random multiplier
                for (char c : s) {
                    hash = (hash * base + c) % p; // Polynomial mod prime
                }
                return hash % m;
        }

            default:
                return key % m;
        }
    }
};

struct SecondLevel {
    std::vector<Record> table;
    HashFunction h2;
    SecondLevel() : h2(1) {}
    SecondLevel(int size, HashType type) : h2(size, type) {
        table.resize(size);
    }
};

class PerfectHashTable {
private:
    std::vector<SecondLevel> buckets;
    int n;
    HashFunction h1;
    HashType h1Type, h2Type;
    int totalSecondLevelSize = 0;
    int totalCollisions = 0;
    int maxRetries = 0;

public:


    int getSecondLevelSize() const { return totalSecondLevelSize; }
    int getCollisions() const { return totalCollisions; }   
    int getMaxRetries() const { return maxRetries; }
    PerfectHashTable(int n, HashType h1Type, HashType h2Type) : n(n), h1(5 * n, h1Type), h1Type(h1Type), h2Type(h2Type) {
        buckets.resize(5 * n);
    }

    long long universal_hash(long long key, const HashFunction& hf) const {
        return hf.apply(key);
    }

    int build(const std::vector<Record>& records) {
        std::vector<std::vector<Record>> tempBuckets(buckets.size());
        totalSecondLevelSize = 0; totalCollisions = 0; maxRetries = 0;

        for (const auto& rec : records) {
            int idx = universal_hash(rec.id, h1);
            tempBuckets[idx].push_back(rec);
        }

        for (size_t i = 0; i < tempBuckets.size(); ++i) {
            int n_i = static_cast<int>(tempBuckets[i].size());
            if (n_i == 0) continue;

            int m_i = n_i * n_i;
            totalSecondLevelSize += m_i;
            bool collision;
            int attempts = 0;

            do {
                attempts++;
                buckets[i].h2 = HashFunction(m_i, h2Type);
                buckets[i].table.assign(m_i, {0, "", "", "", false});
                collision = false;

                for (const auto& rec : tempBuckets[i]) {
                    int pos = universal_hash(rec.id, buckets[i].h2);
                    if (buckets[i].table[pos].isActive) {
                        collision = true;
                        break;
                    }
                    buckets[i].table[pos] = rec;
                }
            } while (collision && attempts < MAX_ATTEMPTS);

 
            totalCollisions += (attempts - 1);
            maxRetries = std::max(maxRetries, attempts);
            
            if (collision) {
                //std::cout << "Failed to build perfect hash table for bucket " << i
                //          << " after " << attempts << " attempts.\n";
                return 0;
            }

        }
        return 1;
    }

    void printStats() const {
        std::cout << "\n=== Hash Function 1 Type: " << hashTypeName(h1Type) << " ===\n";
        std::cout << "\n=== Hash Function 2 Type: " << hashTypeName(h2Type) << " ===\n";
        std::cout << "Total second-level space used: " << totalSecondLevelSize << "\n";
        std::cout << "Total extra attempts (collisions handled): " << totalCollisions << "\n";
        std::cout << "Max retries for any bucket: " << maxRetries << "\n";
    }

    Record* search(long long key) const {
        int bucketIdx = universal_hash(key, h1);
        if (bucketIdx < 0 || bucketIdx >= (int)buckets.size()) return nullptr;
        const auto& bucket = buckets[bucketIdx];
        if (bucket.table.empty()) return nullptr;
        int pos = universal_hash(key, bucket.h2);
        if (pos < 0 || pos >= (int)bucket.table.size()) return nullptr;
        const Record& rec = bucket.table[pos];
        if (rec.isActive && rec.id == key) return (Record*)&rec;
        return nullptr;
    }
};

static inline std::string trim(const std::string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end) ? std::string(start, end) : "";
}

void loadDictionary(const std::string& filename, std::vector<Record>& records) {
    std::ifstream file(filename);
    if (!file.is_open()) { std::cerr << "Error opening file: " << filename << "\n"; return; }
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        std::getline(ss, token, ','); long long id = std::stoll(trim(token));
        std::getline(ss, token, ','); std::string name = trim(token);
        std::getline(ss, token, ','); std::string email = trim(token);
        std::getline(ss, token, ','); std::string gender = trim(token);
        records.push_back({id, name, email, gender, true});
        //if (records.size() > 5) {
        //    std::cout << "Warning: More than 10 records loaded, skipping the rest.\n";
        //    break;
        //}
    }
    file.close();
}


struct HashResult {
    HashType h1;
    HashType h2;
    long long buildTime;
    int secondLevelSize;
    int collisions;
    int maxRetries;
    bool success;
};

void benchmarkAllHashFunctionCombinations(const std::vector<Record>& records, const std::vector<HashType>& types) {

    std::cout << std::left 
              << std::setw(35) << "h1 Type " 
              << std::setw(35) << "h2 Type" 
              << std::setw(20) << "Build Time (us)"
              << std::setw(15) << "2nd Space"
              << std::setw(15) << "Collisions"
              << std::setw(15) << "MaxRetries"
              << "Status\n";

    // Underline
    std::cout << std::string(35, '-')
              << std::string(35, '-')
              << std::string(20, '-')
              << std::string(15, '-')
              << std::string(15, '-')
              << std::string(15, '-')
              << "------\n";

    
    std::vector<HashResult> results;
    for (size_t i = 0; i < types.size(); ++i) {
        for (size_t j = 0; j < types.size(); ++j) {
            HashType h1Type = types[i];
            HashType h2Type = types[j];
            auto start = std::chrono::high_resolution_clock::now();
            PerfectHashTable pht(records.size(), h1Type, h2Type);
            int success = pht.build(records);
            auto end = std::chrono::high_resolution_clock::now();
            long long time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            results.push_back({
            h1Type, h2Type, time,
            pht.getSecondLevelSize(),
            pht.getCollisions(),
            pht.getMaxRetries(),
            static_cast<bool>(success)
        });
            std::cout << std::left 
                      << std::setw(25) << hashTypeName(h1Type) << " +  "
                      << std::setw(25) << hashTypeName(h2Type)
                      << std::setw(20) << time
                      << std::setw(15) << pht.getSecondLevelSize()
                      << std::setw(15) << pht.getCollisions()
                      << std::setw(15) << pht.getMaxRetries()
                      << (success ?     "Success" : "Failed") << "\n";
        }
    }

    std::sort(results.begin(), results.end(), [](const HashResult& a, const HashResult& b) {
        if (a.success != b.success) return a.success > b.success; // All successes first
        if (a.secondLevelSize != b.secondLevelSize) return a.secondLevelSize < b.secondLevelSize;
        return a.buildTime < b.buildTime;
    });

    std::cout << "\n=== Summary of All Combinations ===\n";
    std::cout << std::left << std::setw(30) << "h1 Type"
          << std::setw(30) << "h2 Type"
          << std::setw(20) << "Build Time (us)"
          << std::setw(15) << "2nd Space"
          << std::setw(15) << "Collisions"
          << std::setw(15) << "MaxRetries"
          << "Status\n";

    std::cout << std::string(125, '-') << "\n";

    for (const auto& r : results) {
        std::cout << std::left << std::setw(30) << hashTypeName(r.h1)
              << std::setw(30) << hashTypeName(r.h2)
              << std::setw(20) << r.buildTime
              << std::setw(15) << r.secondLevelSize
              << std::setw(15) << r.collisions
              << std::setw(15) << r.maxRetries
              << (r.success ? "Success" : "Failed") << "\n";
    }

}

int main() {

    srand(42);
    std::vector<Record> records;
    loadDictionary("dictionary.csv", records);
    // Try all hash types one-by-one
    std::vector<HashType> types = {MAD, XOR_BASED, TABULATION, POLYNOMIAL, FIBONACCI, DJBX33A, JENKINS, IDENTITY, 
        LOWER_BITS,CARTER_WEGMAN,TABULATION_SALTED,POLY_MOD_P_4WISE};
    benchmarkAllHashFunctionCombinations(records, types);
 
        std::cout << "Testing search functionality with your choice of hash function.\n";
        std::cout << "Enter the hash function 1 type (0 for MAD, 1 for XOR, 2 for Tabulation, 3 for Polynomial, "
              << "4 for Fibonacci, 5 for DJBX33A,  6 for Jenkins, 7 for Identity, \n                            8 for Lower Bits, 9 for CARTER_WEGMAN, 10 for TABULATION_SALTED, 11 for POLY_MOD_P_4WISE): ";
        int choice1;
        std::cin >> choice1;
        if (choice1 < 0 || choice1 >= (int)types.size()) {
            std::cerr << "Invalid choice! Using MAD as default.\n";
            choice1 = 0;
        }   
        HashType type1 = types[choice1];
        std::cout << "Enter the hash function 2 type (0 for MAD, 1 for XOR, 2 for Tabulation, 3 for Polynomial, "
              << "4 for Fibonacci, 5 for DJBX33A,  6 for Jenkins, 7 for Identity, \n                            8 for Lower Bits, 9 for CARTER_WEGMAN, 10 for TABULATION_SALTED, 11 for POLY_MOD_P_4WISE): ";
        
        int choice2;
        std::cin >> choice2;
        if (choice2 < 0 || choice2 >= (int)types.size()) {
            std::cerr << "Invalid choice! Using MAD as default.\n";
            choice2 = 0;
        }   
        HashType type2 = types[choice2];

        PerfectHashTable pht(records.size(), type1, type2);
        int success = pht.build(records);
        if (!success) {
            std::cerr   << "Failed to build perfect hash table with chosen types: " << hashTypeName(type1)
                        <<" & "<< hashTypeName(type2) << "\n";
            return 1;
        }
        while (true) {
             std::cout << "Enter NHS No: ";
             long long nhs;
             std::cin >> nhs;
             if (nhs == -1) break;

             auto start = std::chrono::high_resolution_clock::now();
             Record* rec = pht.search(nhs);
             auto end = std::chrono::high_resolution_clock::now();
             auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
             std::cout << "Search time: " << duration_us << " micro seconds\n";

             if (rec) {
                 std::cout << "Found: " << rec->name << ", " << rec->email << ", " << rec->gender << "\n";
             } else {
                 std::cout << "Not found.\n";
             }
         }

    return 0;
}
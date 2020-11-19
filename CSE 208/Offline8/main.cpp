#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int u64;

// Offline Specification Data
#define DATASET_SIZE 100
#define STRING_SIZE 7
#define NULL_VALUE INT_MIN

const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


bool stringExists(string key, string dataSet[], int arraySize) {
    for (int i=0; i < arraySize; i++) {
        if (dataSet[i] == key) {
            return true;
        }
    }
    return false;
}

void createDataset(int sampleSize, string dataSet[], int arraySize) {
    string sample = "";

    for (int i=0; i < sampleSize; i++) {
        sample += ALPHABET[rand() % ALPHABET.size()];
    }

    int uniqueCounter = 0;
    dataSet[uniqueCounter++] = sample;
    int repeat = 0;

    while (uniqueCounter < arraySize) {

        for (int i=0; i < sampleSize; i++) {
            sample[i] = ALPHABET[rand() % ALPHABET.size()];
        }

        if (!stringExists(sample, dataSet, arraySize)) {
            dataSet[uniqueCounter++] = sample;
        }
        else{
            repeat++;
        }
    }

    cout << "String generation ended" << endl;
    cout << "Total number of unique strings: " << uniqueCounter << endl;
    cout << "Repeatation during generation: " << repeat << endl;
    cout << "\n\n\n";
}

// PolynomialRollHashFunction
u64 polyRollHashFunc(string s) {
    u64 hash_value = 0;
    int PRC = 61;

    for (int i=0; i < s.size(); i++) {
        hash_value += int(s[i]) * pow(PRC, i);
    }
    return hash_value;
}


// PowerHash Function
u64 powerHashFunc(string s) {
    u64 hash_value = 0;
    for (int i=0; i < s.size(); i++) {
        hash_value += pow(int(s[i]), i);
    }
    return hash_value;
}

// Jenkins Hash Function
u64 jenkinsHashFunc(string s) {
    u64 hash_value = 0;

    for (int i=0; i < s.size(); i++) {
        hash_value += s[i];
        hash_value += (hash_value << 10);
        hash_value ^= (hash_value >> 6);
    }
    hash_value += (hash_value << 3);
    hash_value ^= (hash_value >> 11);
    hash_value += (hash_value << 15);

    return hash_value;
}


u64 FNVHashFunc(string s) {
    u64 hash_value = 0;
    const u64 FNV_PRIME = 16777619;

    for (int i=0; i < s.size(); i++) {
        hash_value = hash_value * FNV_PRIME;
        hash_value ^= s[i];
    }
    return hash_value;
}


bool isPrime(u64 num) {

    if (num == 2 || num == 3) {
        return true;
    }

    if (num == 1 || num % 2 == 0) {
        return false;
    }

    for (int i = 3; i*i <= num; i += 2) {
        if (num % i == 0){
            return false;
        }
    }
    return true;
}


u64 previousPrime (u64 num) {

    if (num % 2 == 0) {
        num--;
    }

    for ( ; !isPrime(num); num -= 2) { ; }

    return num;
}

u64 nextPrime (u64 num) {

    if (num % 2 == 0) {
        num++;
    }

    for ( ; !isPrime(num); num += 2) { ; }

    return num;
}



class PairNode {
public:
    string key;
    int value;

    PairNode() {
        key = "";
        value = NULL_VALUE;
    }

    PairNode(string _key, int _value) {
        key = _key;
        value = _value;
    }

    void print() {
        cout << "Key: " << key << " Value: " << value << endl;
    }
};


class HashTable {
    vector<PairNode> *table;

    int PREVIOUS_PRIME;
    int NEXT_PRIME;
    int TABLE_SIZE;

public:

    int chainCollisionCounter;
    int doubleHashCounter;
    int customProbCounter;

    HashTable(int tableSize) {

        NEXT_PRIME = nextPrime(tableSize);
        PREVIOUS_PRIME = previousPrime(tableSize);

        TABLE_SIZE = NEXT_PRIME;
        table = new vector<PairNode>[TABLE_SIZE];

        chainCollisionCounter = 0;
        doubleHashCounter = 0;
        customProbCounter = 0;
    }

    void insertChainHash (u64 (*hashFunc) (string), string key, int value) {

        if (searchChainHash(*hashFunc, key) != NULL_VALUE) {
            cout << "The key is already present in hash table." << endl;
        }
        else {
            u64 hash_index = hashFunc(key) % TABLE_SIZE;
            int hash_index_size = table[hash_index].size();

            if (hash_index_size > 0) {
                chainCollisionCounter++;
            }
            table[hash_index].push_back(PairNode(key, value));
        }
    }

    int searchChainHash (u64 (*hashFunc)(string), string key) {
        u64 hash_index = hashFunc(key) % TABLE_SIZE;
        for (int i=0; i < table[hash_index].size(); i++) {
            if (table[hash_index].at(i).key == key) {
                return table[hash_index].at(i).value;
            }
        }
        return NULL_VALUE;
    }

    void deleteChainHash (u64 (*hashFunc)(string), string key) {
        if (searchChainHash(*hashFunc, key) == NULL_VALUE) {
            cout << "This key isn't present in hash table. Unable to delete" << endl;
        }
        else {
            u64 hash_index = hashFunc(key) % TABLE_SIZE;
            for (int i=0; i < table[hash_index].size(); i++) {
                if (table[hash_index].at(i).key == key) {
                    table[hash_index].erase(table[hash_index].begin() + i);
                    cout << "The element has been erased from hash table" << endl;
                }
            }
        }
    }

    int searchDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = doubleHash(hashFunc, key, i);

        if (table[hash_index].empty()) {
            return NULL_VALUE;
        }
        else {
            while (true) {
                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = doubleHash(hashFunc, key, i);

                if (table[hash_index].empty()) {
                    break;
                }
            }
        }
        return NULL_VALUE;
    }

    void insertDoubleHash (u64 (*hashFunc)(string), string key, int value) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = doubleHash(hashFunc, key, i);
            //cout << "index: " << hash_index << endl;
            if (table[hash_index].empty()) {
                table[hash_index].push_back(PairNode(key, value));
                //cout << "inserted" << endl;
                break;
            }
            else {
                doubleHashCounter++;
            }
            i++;
        }
    }

    void deleteDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = doubleHash(hashFunc, key, i);

            if (table[hash_index].empty()) {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else {
                if (table[hash_index].at(0).key == key) {
                    table[hash_index].erase(table[hash_index].begin());
                    cout << "The key has been delete from hash table" << endl;
                    break;
                }
                i++;
            }
        }
    }

    u64 customProbHash(u64 (*hashFunc)(string), string key, int i) {
        u64 hash_value = 0;
        int C1 = 2, C2 = 3;
        hash_value = (hashFunc(key) + C1*i*auxHashFunc(key) + C2*i*i) % TABLE_SIZE;
        return hash_value;
    }

    u64 doubleHash(u64 (*hashFunc)(string), string s, int i) {
        u64 hash_value = 0;
        hash_value = (FNVHashFunc(s) + i * auxHashFunc(s)) % TABLE_SIZE;
        return hash_value;
    }

    u64 auxHashFunc(string s) {
        u64 hash_value = 0;
        for (int i=0; i < s.size(); i++) {
            hash_value += int(s[i]);
        }
        //hash_value = previousPrime(hash_value);
        hash_value = PREVIOUS_PRIME - (hash_value % PREVIOUS_PRIME);
        return hash_value;
    }

    int searchCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = customProbHash(hashFunc, key, i);

        if (table[hash_index].empty()) {
            return NULL_VALUE;
        }
        else {

            while (true) {
                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = customProbHash(hashFunc, key, i);

                if (table[hash_index].empty()) {
                    break;
                }
            }
        }
        return NULL_VALUE;
    }

    void insertCustomProbHash(u64 (*hashFunc)(string), string key, int value) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = customProbHash(hashFunc, key, i);
            //cout << "hash-index: " << hash_index << endl;

            if (table[hash_index].empty()) {
                table[hash_index].push_back(PairNode(key, value));
                //cout << "inserted:2" << endl;
                break;
            }
            else {
                customProbCounter++;
            }
            i++;
        }
    }

    void deleteCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = customProbHash(hashFunc, key, i);

            if (table[hash_index].empty()) {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else {
                if (table[hash_index].at(0).key == key) {
                    table[hash_index].erase(table[hash_index].begin());
                    cout << "The key has been delete from hash table" << endl;
                    break;
                }
                i++;
            }
        }
    }

    void printHashTable() {
        int emptyRow  = 0;

        for (int i=0; i < TABLE_SIZE; i++) {
            if (table[i].empty())
                emptyRow++;

            for (int k=0; k < table[i].size(); k++) {
            //    table[i].at(k).print();
            //    cout << "\t";
            }
            //cout << endl;
        }
        cout << "Empty row: " << emptyRow << endl;
    }

    float getChainCollisionPercentage() {
        return (100.00*chainCollisionCounter)/TABLE_SIZE;
    }

};



int main() {
    srand(time(NULL));

    int dataSetSize;

    cout << "Enter Dataset size: ";
    cin >> dataSetSize;

    string dataSet[dataSetSize];

    createDataset(STRING_SIZE, dataSet, dataSetSize);

    HashTable htc(dataSetSize);
    HashTable htd(dataSetSize);
    HashTable htp(dataSetSize);

    for (int i=0; i < dataSetSize; i++) {
        htc.insertChainHash(polyRollHashFunc, dataSet[i], i+1);
        htd.insertDoubleHash(polyRollHashFunc, dataSet[i], i+1);
        htp.insertCustomProbHash(polyRollHashFunc, dataSet[i], i+1);
    }

    cout << "Collision Rates (1)" << endl;
    cout << "Chain Hash: " << htc.chainCollisionCounter << endl;
    cout << "Double Hash: " << htd.doubleHashCounter << endl;
    cout << "Custom Probe Hash: " << htp.customProbCounter << endl;
    
    cout << "\n\n";

    HashTable htc2(dataSetSize);
    HashTable htd2(dataSetSize);
    HashTable htp2(dataSetSize);

    for (int i=0; i < dataSetSize; i++) {
        htc2.insertChainHash(FNVHashFunc, dataSet[i], i+1);
        htd2.insertDoubleHash(FNVHashFunc, dataSet[i], i+1);
        htp2.insertCustomProbHash(FNVHashFunc, dataSet[i], i+1);
    }

    cout << "Collision Rates (2)" << endl;
    cout << "Chain Hash: " << htc2.chainCollisionCounter << endl;
    cout << "Double Hash: " << htd2.doubleHashCounter << endl;
    cout << "Custom Probe Hash: " << htp2.customProbCounter << endl;
    cout << "\n\n\n";

    return 0;
}


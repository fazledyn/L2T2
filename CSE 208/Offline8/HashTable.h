#include <limits>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long int u64;

#define NULL_VALUE INT_MIN


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
    bool *elementWasHere;

    int PREVIOUS_PRIME, NEXT_PRIME, TABLE_SIZE;
    int collisionCounter, probeCounter;
    
    u64 customProbHash(u64 (*hashFunc)(string), string key, int i) {
        u64 hash_value = 0;
        int C1 = 2, C2 = 3;
        hash_value = (hashFunc(key) + C1*i*auxHashFunc(key) + C2*i*i) % TABLE_SIZE;
        return hash_value;
    }

    u64 doubleHash(u64 (*hashFunc)(string), string s, int i) {
        u64 hash_value = 0;
        hash_value = (hashFunc(s) + i * auxHashFunc(s)) % TABLE_SIZE;
        return hash_value;
    }

    u64 auxHashFunc(string s) {
        u64 hash_value = 0;
        for (int i=0; i < s.size(); i++) {
            hash_value += int(s[i]);
        }
        hash_value = PREVIOUS_PRIME - (hash_value % PREVIOUS_PRIME);
        return hash_value;
    }

public:

    HashTable(int tableSize) {
        NEXT_PRIME = nextPrime(tableSize);
        PREVIOUS_PRIME = previousPrime(tableSize);

        TABLE_SIZE = NEXT_PRIME;
        table = new vector<PairNode>[TABLE_SIZE];
        elementWasHere = new bool[TABLE_SIZE];

        for (int i=0; i < TABLE_SIZE; i++) {
            elementWasHere[i] = false;
        }

        collisionCounter = 0;
        probeCounter = 0;
    }

    int getCollisionCounter() { return collisionCounter; }
    int getProbeCounter() { return probeCounter; }

    /*
    #########################################
                Chaining Method
    #########################################
     */


    int searchChainHash (u64 (*hashFunc)(string), string key) {
        u64 hash_index = hashFunc(key) % TABLE_SIZE;
        for (int i=0; i < table[hash_index].size(); i++) {
            if (table[hash_index].at(i).key == key) {
                return table[hash_index].at(i).value;
            }
            probeCounter++;
        }
        return NULL_VALUE;
    }

    void insertChainHash (u64 (*hashFunc) (string), string key, int value) {
        u64 hash_index = hashFunc(key) % TABLE_SIZE;
        int hash_index_size = table[hash_index].size();

        if (hash_index_size > 0) {
            collisionCounter++;
        }
        table[hash_index].push_back(PairNode(key, value));
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

    /*
    #########################################
            Double Hashing Method
    #########################################
     */

    int searchDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = doubleHash(hashFunc, key, i);

        if (table[hash_index].empty() && !elementWasHere[hash_index]) {
            return NULL_VALUE;
        }
        else {
            while (true) {
                probeCounter++;

                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = doubleHash(hashFunc, key, i);

                // if any element wasn't there and the place is empty, then break it
                if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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
                elementWasHere[hash_index] = true;
                // the element is here now
                //cout << "inserted" << endl;
                break;
            }
            else {
                collisionCounter++;
            }
            i++;
        }
    }

    void deleteDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = doubleHash(hashFunc, key, i);

            if (table[hash_index].empty() && !elementWasHere[hash_index]) {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else {
                if (table[hash_index].size() > 0) {
                    if (table[hash_index].at(0).key == key) {
                        table[hash_index].erase(table[hash_index].begin());
                        cout << "The key has been delete from hash table" << endl;
                        break;
                    }
                }                
                i++;
            }
        }
    }

    /*
    #########################################
            Custom Probing Method
    #########################################
     */

    int searchCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = customProbHash(hashFunc, key, i);

        if (table[hash_index].empty() && !elementWasHere[hash_index]) {
            return NULL_VALUE;
        }
        else {
            while (true) {
                probeCounter++;

                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = customProbHash(hashFunc, key, i);

                if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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
                elementWasHere[hash_index] = true;
                //cout << "inserted:2" << endl;
                break;
            }
            else {
                collisionCounter++;
            }
            i++;
        }
    }

    void deleteCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = customProbHash(hashFunc, key, i);

            if (table[hash_index].empty() && !elementWasHere[hash_index]) {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else {
                if (table[hash_index].size() > 0) {    
                    if (table[hash_index].at(0).key == key) {
                        table[hash_index].erase(table[hash_index].begin());
                        cout << "The key has been delete from hash table" << endl;
                        break;
                    }
                }
                i++;
            }
        }
    }
    
    /*
    #########################################
        Diagnostics For Report Generation
    #########################################
     */

    void probeDataGeneration(u64 (*hashFunc)(string), string *dataSet, int dataSetSize, int method) {

        bool visited[dataSetSize];
        for (int i=0; i < dataSetSize; i++) {
            visited[i] = false;
        }

        int inserted = 0, idx;
        while(inserted < 1000) {
            idx = rand() % dataSetSize;

            if (!visited[idx]) {
                if (method == 1)
                    searchChainHash(hashFunc, dataSet[idx]);
                else if (method == 2)
                    searchDoubleHash(hashFunc, dataSet[idx]);
                else if (method == 3)
                    searchCustomProbHash(hashFunc, dataSet[idx]);                
                inserted++;
            }
        }
    }

};

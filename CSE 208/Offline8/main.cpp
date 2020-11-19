#include <bits/stdc++.h>
#include "HashTable.h"

using namespace std;

#define STRING_SIZE 7
typedef unsigned long long int u64;


/*
#########################################
            Hash Functions
#########################################
*/

// Hash1 :: PolynomialRollHashFunction
u64 Hash1(string s) {
    u64 hash_value = 0;
    int PRC = 61;

    for (int i=0; i < s.size(); i++) {
        hash_value += int(s[i]) * pow(PRC, i);
    }
    return hash_value;
}

// Hash2 :: PowerHash Function
u64 Hash2(string s) {
    u64 hash_value = 0;
    for (int i=0; i < s.size(); i++) {
        hash_value += pow(int(s[i]), i);
    }
    return hash_value;
}

// Jenkins Hash Function
u64 Hash3(string s) {
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

// Fowler-Nol-Vo Hash Function
u64 Hash4(string s) {
    u64 hash_value = 0;
    const u64 FNV_PRIME = 16777619;

    for (int i=0; i < s.size(); i++) {
        hash_value = hash_value * FNV_PRIME;
        hash_value ^= s[i];
    }
    return hash_value;
}

/*
#########################################
            String Generator
#########################################
*/

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
}


/*
##################################################################################
##################################################################################
##################################################################################
*/


int main() {
    srand(time(NULL));
    
    cout << "::::Main Menu::::" << endl;
    cout << "1. Use Hash Table Manually" << endl;
    cout << "2. Calculate Accuracy For Hash Function Collisions" << endl;
    cout << "3. Generate Report" << endl;
    cout << "Enter choice: ";

    int option;
    cin >> option;

    if (option == 1) {

        cout << "Enter hash table size: ";
        int hashTableSize;
        cin >> hashTableSize;

        HashTable ht(hashTableSize);
        string key;
        int value;

        while (true) {

            cout << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> option;

            if (option == 1) {
                cout << "Enter key, value like this ('buetcse 17'): ";
                cin >> key >> value;

                if (ht.searchChainHash(Hash1, key) == NULL_VALUE) {
                    ht.insertChainHash(Hash1, key, value);
                    cout << "Key inserted" << endl;
                }
                else {
                    cout << "This key already exists." << endl;
                }
            }
            else if (option == 2) {
                cout << "Enter key to delete: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) == NULL_VALUE) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    ht.deleteChainHash(Hash1, key);
                    cout << "Key deleted" << endl;
                }
            }
            else if (option == 3) {
                cout << "Enter key to search: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) == NULL_VALUE) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    cout << "Value for this key: " << ht.searchChainHash(Hash1, key) << endl;
                }
            }
            else {
                break;
            }
        }
    }
    else if (option == 2) {

        const int DATASET_SIZE = 1000;

        int hash1Count = 0, hash2Count = 0;
        int hash3Count = 0, hash4Count = 0;

        string dataSet[DATASET_SIZE];
        string hash1Store[DATASET_SIZE], hash2Store[DATASET_SIZE];
        string hash3Store[DATASET_SIZE], hash4Store[DATASET_SIZE];

        createDataset(STRING_SIZE, dataSet, DATASET_SIZE);

        hash1Store[0] = to_string(Hash1( dataSet[0] ) % DATASET_SIZE );
        hash2Store[0] = to_string(Hash2( dataSet[0] ) % DATASET_SIZE );
        hash3Store[0] = to_string(Hash3( dataSet[0] ) % DATASET_SIZE );
        hash4Store[0] = to_string(Hash4( dataSet[0] ) % DATASET_SIZE );

        string hash1, hash2, hash3, hash4;

        for (int i = 1; i < DATASET_SIZE; i++) {
        
            hash1 = to_string(Hash1( dataSet[i] ) % DATASET_SIZE );
            hash2 = to_string(Hash2( dataSet[i] ) % DATASET_SIZE );
            hash3 = to_string(Hash3( dataSet[i] ) % DATASET_SIZE );
            hash4 = to_string(Hash4( dataSet[i] ) % DATASET_SIZE );
            
            if (stringExists(hash1, hash1Store, DATASET_SIZE))
                hash1Count++;
            
            if (stringExists(hash2, hash2Store, DATASET_SIZE))
                hash2Count++;

            if (stringExists(hash3, hash3Store, DATASET_SIZE))
                hash3Count++;
            
            if (stringExists(hash4, hash4Store, DATASET_SIZE))
                hash4Count++;    

            hash1Store[i] = hash1;
            hash2Store[i] = hash2;
            hash3Store[i] = hash3;
            hash4Store[i] = hash4;
        }

        cout << "Hash Function Accuracy: " << endl;
        cout << "Hash 1 Collision Rate: " << (100.00*hash1Count)/DATASET_SIZE << "%" << endl;
        cout << "Hash 2 Collision Rate: " << (100.00*hash2Count)/DATASET_SIZE << "%" << endl;
        cout << "Hash 3 Collision Rate: " << (100.00*hash3Count)/DATASET_SIZE << "%" << endl;
        cout << "Hash 4 Collision Rate: " << (100.00*hash4Count)/DATASET_SIZE << "%" << endl;
        cout << endl;
    }
    else if (option == 3) {

        int dataSetSize;

        cout << "Enter Dataset size: ";
        cin >> dataSetSize;
        
        string dataSet[dataSetSize];
        createDataset(STRING_SIZE, dataSet, dataSetSize);

        HashTable Hash1_Chaining_Method(dataSetSize);
        HashTable Hash1_Double_Hashing(dataSetSize);
        HashTable Hash1_Custom_Probing(dataSetSize);

        for (int i=0; i < dataSetSize; i++) {
            Hash1_Chaining_Method.insertChainHash(Hash1, dataSet[i], i+1);
            Hash1_Double_Hashing.insertDoubleHash(Hash1, dataSet[i], i+1);
            Hash1_Custom_Probing.insertCustomProbHash(Hash1, dataSet[i], i+1);
        }

        cout << endl;
        cout << "\t" << "::Hash1::" << endl;
        cout << "\t" << "Collision Count (out of 10,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash1_Chaining_Method.getCollisionCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash1_Double_Hashing.getCollisionCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash1_Custom_Probing.getCollisionCounter() << endl;
        
        Hash1_Chaining_Method.probeDataGeneration(Hash1, dataSet, dataSetSize, 1);
        Hash1_Double_Hashing.probeDataGeneration(Hash1, dataSet, dataSetSize, 2);
        Hash1_Custom_Probing.probeDataGeneration(Hash1, dataSet, dataSetSize, 3);

        cout << endl;
        cout << "\t" << "Probe Count (out of 1,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash1_Chaining_Method.getProbeCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash1_Double_Hashing.getProbeCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash1_Custom_Probing.getProbeCounter() << endl;
        cout << endl;

        HashTable Hash2_Chaining_Method(dataSetSize);
        HashTable Hash2_Double_Hashing(dataSetSize);
        HashTable Hash2_Custom_Probing(dataSetSize);

        for (int i=0; i < dataSetSize; i++) {
            Hash2_Chaining_Method.insertChainHash(Hash2, dataSet[i], i+1);
            Hash2_Double_Hashing.insertDoubleHash(Hash2, dataSet[i], i+1);
            Hash2_Custom_Probing.insertCustomProbHash(Hash2, dataSet[i], i+1);
        }

        cout << endl;
        cout << "\t" << "::Hash 2::" << endl;
        cout << "\t" << "Collision Count (out of 10,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash2_Chaining_Method.getCollisionCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash2_Double_Hashing.getCollisionCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash2_Custom_Probing.getCollisionCounter() << endl;
        
        Hash2_Chaining_Method.probeDataGeneration(Hash2, dataSet, dataSetSize, 1);
        Hash2_Double_Hashing.probeDataGeneration(Hash2, dataSet, dataSetSize, 2);
        Hash2_Custom_Probing.probeDataGeneration(Hash2, dataSet, dataSetSize, 3);
        
        cout << endl;
        cout << "\t" << "Probe Count (out of 1,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash2_Chaining_Method.getProbeCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash2_Double_Hashing.getProbeCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash2_Custom_Probing.getProbeCounter() << endl;
        cout << endl;

    }

    return 0;
}


//============================================================================
// Name        : HashTable.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
    string bidId;
    string title;
    string fund;
    double amount;
    Bid()
    {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable
{
private:
    // Define structures to hold bids
    struct Node
    {
        Bid bid;
        unsigned int key;
        Node *next;

        Node()
        {
            key = UINT_MAX;
            next = nullptr;
        }

        Node(Bid aBid) : Node()
        {
            bid = aBid;
        }

        Node(Bid aBid, unsigned int aKey) : Node(aBid)
        {
            key = aKey;
        }
    };

    vector<Node *> nodes;
    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable()
{
    nodes.resize(tableSize, nullptr);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size)
{
    this->tableSize = size;
    nodes.resize(tableSize, nullptr);
}

/**
 * Destructor
 */
HashTable::~HashTable()
{
    for (auto node : nodes)
    {
        while (node != nullptr)
        {
            Node *temp = node;
            node = node->next;
            delete temp;
        }
    }
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key)
{
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid)
{
    unsigned int key = hash(stoi(bid.bidId));
    Node *prev = nullptr;
    Node *node = nodes[key];

    while (node != nullptr && node->key != UINT_MAX && node->bid.bidId != bid.bidId)
    {
        prev = node;
        node = node->next;
    }

    if (node == nullptr)
    {
        node = new Node(bid, key);
        if (prev == nullptr)
        {
            nodes[key] = node;
        }
        else
        {
            prev->next = node;
        }
    }
    else
    {
        node->bid = bid;
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll()
{
    for (auto node : nodes)
    {
        while (node != nullptr)
        {
            if (node->key != UINT_MAX)
            {
                cout << node->key << ": " << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
            }
            node = node->next;
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId)
{
    unsigned int key = hash(stoi(bidId));
    Node *prev = nullptr;
    Node *node = nodes[key];

    while (node != nullptr && node->bid.bidId != bidId)
    {
        prev = node;
        node = node->next;
    }

    if (node == nullptr)
    {
        return;
    }

    if (prev == nullptr)
    {
        nodes[key] = node->next;
    }
    else
    {
        prev->next = node->next;
    }

    delete node;
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId)
{
    unsigned int key = hash(stoi(bidId));
    Node *node = nodes[key];

    while (node != nullptr && node->bid.bidId != bidId)
    {
        node = node->next;
    }

    if (node == nullptr)
    {
        return Bid();
    }
    else
    {
        return node->bid;
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable *hashTable)
{
    cout << "Loading CSV file " << csvPath << endl;

    csv::Parser file = csv::Parser(csvPath);

    vector<string> header = file.getHeader();
    for (auto const &c : header)
    {
        cout << c << " | ";
    }
    cout << "" << endl;

    try
    {
        for (unsigned int i = 0; i < file.rowCount(); i++)
        {
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            hashTable->Insert(bid);
        }
    }
    catch (csv::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch)
{
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[])
{
    string csvPath, bidKey;
    switch (argc)
    {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    clock_t ticks;

    HashTable *bidTable = new HashTable();

    Bid bid;

    int choice = 0;
    while (choice != 9)
    {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ticks = clock();
            loadBids(csvPath, bidTable);
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        case 2:
            bidTable->PrintAll();
            break;
        case 3:
            ticks = clock();
            bid = bidTable->Search(bidKey);
            ticks = clock() - ticks;

            if (!bid.bidId.empty())
            {
                displayBid(bid);
            }
            else
            {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    delete bidTable;

    return 0;
}
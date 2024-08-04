//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Angel Davila
// Version     : 1.0
// Copyright   : Copyright 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid()
    {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node
{
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node()
    {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) : Node()
    {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree
{

private:
    Node *root;

    void addNode(Node *node, Bid bid);
    void inOrder(Node *node);
    void postOrder(Node *node);
    void preOrder(Node *node);
    Node *removeNode(Node *node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
    // initialize housekeeping variables
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder()
{
    inOrder(root);
}

void BinarySearchTree::inOrder(Node *node)
{
    if (node != nullptr)
    {
        inOrder(node->left);
        displayBid(node->bid);
        inOrder(node->right);
    }
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder()
{
    postOrder(root);
}

void BinarySearchTree::postOrder(Node *node)
{
    if (node != nullptr)
    {
        postOrder(node->left);
        postOrder(node->right);
        displayBid(node->bid);
    }
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder()
{
    preOrder(root);
}

void BinarySearchTree::preOrder(Node *node)
{
    if (node != nullptr)
    {
        displayBid(node->bid);
        preOrder(node->left);
        preOrder(node->right);
    }
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid)
{
    // If the tree is empty, set the root to a new node with the bid
    if (root == nullptr)
    {
        root = new Node(bid);
    }
    else
    {
        // Otherwise, add the bid to the tree
        addNode(root, bid);
    }
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node *node, Bid bid)
{
    // If the bid's ID is less than the current node's bid ID, go left
    if (bid.bidId < node->bid.bidId)
    {
        if (node->left == nullptr)
        {
            node->left = new Node(bid);
        }
        else
        {
            addNode(node->left, bid);
        }
    }
    else
    {
        // If the bid's ID is greater than or equal to the current node's bid ID, go right
        if (node->right == nullptr)
        {
            node->right = new Node(bid);
        }
        else
        {
            addNode(node->right, bid);
        }
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId)
{
    root = removeNode(root, bidId);
}

/**
 * Remove a bid from some node (recursive)
 */
Node *BinarySearchTree::removeNode(Node *node, string bidId)
{
    if (node == nullptr)
    {
        return node;
    }

    // Traverse the tree to find the node to remove
    if (bidId < node->bid.bidId)
    {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId > node->bid.bidId)
    {
        node->right = removeNode(node->right, bidId);
    }
    else
    {
        // Node with only one child or no child
        if (node->left == nullptr)
        {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node *temp = node->right;
        while (temp && temp->left != nullptr)
        {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        node->bid = temp->bid;

        // Delete the inorder successor
        node->right = removeNode(node->right, temp->bid.bidId);
    }
    return node;
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId)
{
    Node *current = root;

    // Traverse the tree to find the bid
    while (current != nullptr)
    {
        if (bidId == current->bid.bidId)
        {
            return current->bid;
        }
        if (bidId < current->bid.bidId)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    Bid bid;
    return bid; // Return an empty bid if not found
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
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree *bst)
{
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const &c : header)
    {
        cout << c << " | ";
    }
    cout << "" << endl;

    try
    {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++)
        {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bst->Insert(bid);
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

    // process command line arguments
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

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree *bst;
    bst = new BinarySearchTree();
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

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

                      // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

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
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

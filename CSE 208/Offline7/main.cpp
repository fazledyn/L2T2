#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define INFINITY INT_MAX

class Node
{
public:
    int key, degree;
    Node *parent, *child, *sibling;

    Node (int _key)
    {
        key = _key;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
};

class BinomialHeap
{
    Node *head;

public:
    Node *findMinimum()
    {

        Node *y = nullptr;
        Node *x = head;
        int minimum = INFINITY;

        while (x != nullptr)
        {
            if (x->key < minimum)
            {
                minimum = x->key;
                y = x;
            }
            x = x->sibling;
        }
    }

    void BinomialLink(Node *y, Node *z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    void BinomialInsert(Node* x) {
        BinomialHeap newheap;
        newheap.head = x;
        this->head = BinomialHeapUnion(this, &newheap);
    }

    void ExtractMin() {

        Node *minNode = findMinimum();
        Node *child = minNode->child;

        // Parent Null kore
        while (child != nullptr) {
            child->parent = nullptr;
            child = child->sibling;
        }

        child = minNode->child;
        stack<Node*> allSibling;

        while (child != nullptr) {
            allSibling.push(child);
            child = child->sibling;
        }

        Node* currHead = allSibling.top();
        child = currHead;
        allSibling.pop();

        // resort them to the order
        while (!allSibling.empty()) {
            child->sibling = allSibling.top();
            allSibling.pop();
            child = child->sibling;
        }
        child->sibling = nullptr;
        // now final child, previoud first child

        
    }



};

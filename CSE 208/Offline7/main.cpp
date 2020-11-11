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
        BinomialHeap newHeap;
        newHeap.head = x;
        this->BinomialHeapUnion(newHeap);
    }


    void BinomialHeapMerge(BinomialHeap heap) {

        


    }


    void BinomialHeapUnion(BinomialHeap heap) {

        BinomialHeap newHeap;
        newHeap.head = this->BinomialHeapMerge(heap);

        if (newHeap.head == nullptr) {
            this->head = newHeap.head;
        }

        Node* prev = nullptr;
        Node* x = newHeap.head;
        Node* next = x->sibling;

        while (next != nullptr) {
            if ( (x->degree != next->degree) || ((next->sibling != nullptr) && (next->sibling->degree == x->degree)) ) {
                prev = x;
                x = next;
            }
            else {
                if (x->key <= next->key) {
                    x->sibling = next->sibling;
                    this->BinomialLink(next, x);
                }
                else {
                    if (prev == nullptr) {
                        this->head = next;
                    }
                    else {
                        prev->sibling = next;
                    }
                    this->BinomialLink(x, next);
                    x = next;
                }
            }
            next = x->sibling;
        }
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

        BinomialHeap newHeap;
        newHeap.head = currHead;

        this->BinomialHeapUnion(newHeap);
        
    }



};

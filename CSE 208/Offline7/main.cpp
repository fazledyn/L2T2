#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

#define INFINITY INT_MAX

class Node
{
public:
    int key, degree;
    Node *parent, *child, *sibling;

    Node(int _key)
    {
        key = _key;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }

    Node() {
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }

    void print() {
        cout << endl;
        cout << "Printing Node: " << endl;
        cout << "Key: " << key << endl;
        cout << "Degree: " << degree << endl;
        if (parent != nullptr)
            cout << "Parent: " << parent->key << "(" << parent << ")" << endl;
        if (child != nullptr)
            cout << "Child: " << child->key << "(" << child << ")" << endl;
        if (sibling != nullptr)
            cout << "Sibling: " << sibling->key << "(" << sibling << ")" << endl;
        cout << endl;
    }

};

class BinomialHeap
{
    Node *head;

public:

    BinomialHeap() {
        head = nullptr;
    }

    Node* getHead() {
        return this->head;
    }

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
        return y;
    }

    void BinomialLink(Node *y, Node *z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    void BinomialInsert(Node *x)
    {
        BinomialHeap newHeap;
        newHeap.head = x;
        this->BinomialUnion(newHeap);
    }

    void BinomialDecreaseKey(Node *node, int newKey)
    {
        if (newKey > node->key)
        {
            cout << "The new key is greater than the previous one!" << endl;
        }
        else
        {
            node->key = newKey;
            Node *temp = node;
            Node *parent = temp->parent;

            while ((parent != nullptr) && (temp->key < parent->key))
            {
                swap(temp->key, parent->key);
                // if temp and parent has satelite fields and exchange them too ??????????????
                // wtf does this mean
                temp = parent;
                parent = temp->parent;
            }
        }
    }

    void BinomialDelete(Node *x)
    {
        BinomialDecreaseKey(x, -INFINITY);
        BinomialExtractMin();
    }

    void BinomialHeapMerge(BinomialHeap heap)
    {
        Node *thisHead = this->head;
        Node *thatHead = heap.head;
        Node *newHead = nullptr;
        Node *storeHead = nullptr;

        if (thisHead == nullptr) {
            head = heap.head;
            return;
        }

        if (thisHead->degree <= thatHead->degree)
        {
            newHead = thisHead;
            thisHead = thisHead->sibling;
        }
        else
        {
            newHead = thatHead;
            thatHead = thatHead->sibling;
        }
        storeHead = newHead;

        while (thisHead != nullptr && thatHead != nullptr)
        {
            if (thisHead->degree <= thatHead->degree)
            {
                newHead->sibling = thisHead;
                thisHead = thisHead->sibling;
            }
            else
            {
                newHead->sibling = thatHead;
                thatHead = thatHead->sibling;
            }
            newHead = newHead->sibling;
        }

        if (thisHead != nullptr)
        {
            while (thisHead != nullptr)
            {
                newHead->sibling = thisHead;
                thisHead = thisHead->sibling;
                newHead = newHead->sibling;
            }
        }

        if (thatHead != nullptr)
        {
            while (thatHead != nullptr)
            {
                newHead->sibling = thatHead;
                thatHead = thatHead->sibling;
                newHead = newHead->sibling;
            }
        }

        this->head = storeHead;
    }


    void BinomialUnion(BinomialHeap heap) {

        BinomialHeapMerge(heap);

/*
        if (this->head == nullptr) {
            return;
        }
*/

        Node* prev = nullptr;
        Node* curr = this->head;
        Node* next = curr->sibling;

        while (next != nullptr) {

            if ( (curr->degree != next->degree) || ((next->sibling != nullptr) && (next->sibling->degree == curr->degree)) ) {
                prev = curr;
                curr = next;
            }
            else {

                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    BinomialLink(next, curr);
                }
                else {
                    if (prev == nullptr) {
                        head = next;
                    }
                    else {
                        prev->sibling = next;
                    }
                    BinomialLink(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
    }

    void BinomialExtractMin()
    {
        Node *minNode = findMinimum();
        Node *child = minNode->child;

        // Parent Null kore
        while (child != nullptr)
        {
            child->parent = nullptr;
            child = child->sibling;
        }

        child = minNode->child;
        stack<Node *> allSibling;

        while (child != nullptr)
        {
            allSibling.push(child);
            child = child->sibling;
        }

        Node *currHead = allSibling.top();
        child = currHead;
        allSibling.pop();

        // resort them to the order
        while (!allSibling.empty())
        {
            child->sibling = allSibling.top();
            allSibling.pop();
            child = child->sibling;
        }
        child->sibling = nullptr;
        // now final child, previoud first child

        BinomialHeap newHeap;
        newHeap.head = currHead;

        this->BinomialUnion(newHeap);
    }




};



int main() {

    BinomialHeap bh;
    Node* node;

    node = new Node(2);
    bh.BinomialInsert(node);

    node = new Node(5);
    bh.BinomialInsert(node);

    node = new Node(4);
    bh.BinomialInsert(node);

    bh.getHead()->print();
    bh.getHead()->sibling->print();
}

#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

#define INFINITY INT_MAX


int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 

int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 


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

    void setHead(Node* headNode) {
        this->head = headNode;
    }

    Node* findMinimum()
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
        BinomialDecreaseKey(x, -(INFINITY - 100));
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

        // if (this->head == nullptr) {
        //     return;
        // }

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

    int BinomialExtractMin()
    {
        Node *minNode = findMinimum();
        Node *child = minNode->child;
        int extractMinKey = minNode->key;

        // search kore link change korsi
        Node* iterNode = head;
        while (iterNode != nullptr) {
            if (iterNode->sibling == minNode) {
                iterNode->sibling = minNode->sibling;
                break;
            }
            else if ((head == minNode) && (iterNode->sibling != nullptr)) {
                this->head = iterNode->sibling;
                cout << __LINE__ << endl;
                return extractMinKey;
            }
            else if ((iterNode == minNode) && (iterNode->sibling == nullptr)) {
                head = nullptr;
                break;
            }
            iterNode = iterNode->sibling;
        }
        //bsdk cormen

        // Parent Null kore
        while (child != nullptr)
        {
            child->parent = nullptr;
            child = child->sibling;
        }

        child = minNode->child;
        stack<Node*> allSibling;

        while (child != nullptr)
        {
            allSibling.push(child);
            child = child->sibling;
        }

        Node* currHead = allSibling.top();
        Node* headStore = currHead;
        allSibling.pop();

        // resort them to the order
        while (!allSibling.empty())
        {
            currHead->sibling = allSibling.top();
            allSibling.pop();
            currHead = currHead->sibling;
        }

        currHead->sibling = nullptr;
        // now final child, previoud first child

        BinomialHeap h;
        h.setHead(headStore);
        BinomialUnion(h);

        return extractMinKey;
    }

    void BinomialHeapPrint() {
		Node* currPtr = head;
        cout << "Printing Binomial Heap..." << endl;

		while (currPtr != nullptr) {
            int degree = currPtr->degree;
			cout<<"Binomial Tree, B" << degree << endl;

			queue<Node*> q;
			q.push(currPtr);
            int level = 0, count = 0, prev_count = 0;

            cout << "Level " << level << " : ";
			while (!q.empty()) {
				Node* p = q.front();
				q.pop();

                if (count == nCr(degree, level) + prev_count) {
                    cout << endl;
                    prev_count = nCr(degree, level) + prev_count;
                    level++;
                    cout << "Level " << level << " : ";
                }

                cout << p->key << " ";
                count++;

				if (p->child != nullptr) {
					Node* tempPtr = p->child;
					while (tempPtr != nullptr) {
						q.push(tempPtr);
						tempPtr = tempPtr->sibling;
					}
                }
			}
			currPtr = currPtr->sibling;
			cout << endl;
		}
	}
};


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    BinomialHeap bh;
    Node* node;

    string input;
    while (getline(cin, input)) {
        char first_letter;
        {
            istringstream iss(input);
            iss >> first_letter;

            if (first_letter == 'P') {
                // nor argument
                bh.BinomialHeapPrint();
            }
            else if (first_letter == 'F') {
                node = bh.findMinimum();
                cout << "FindMin returned " << node->key << endl;
            }
            else if (first_letter == 'E') {
                int key = bh.BinomialExtractMin();
                cout << "ExtractMin returned " << key << endl;
            }
            else if (first_letter == 'U') {
                // var
                int number;
                vector <int> numbers;
                while (iss >> number) {
                    numbers.push_back(number);
                }

                BinomialHeap heap;
                for (int num:numbers) {
                    node = new Node;
                    node->key = num;
                    heap.BinomialInsert(node);            
                }
                bh.BinomialUnion(heap);
            }
            else if (first_letter == 'I') {
                int number;
                iss >> number;
                node = new Node;
                node->key = number;
                bh.BinomialInsert(node);
            }
        }
    }
}


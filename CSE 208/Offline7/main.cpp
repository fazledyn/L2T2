#include <iostream>
#include <climits>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

#define INFINITY INT_MAX
#define GARBAGE	-999999999

/*
    Helper Functions for calculating nCr for Pascal's Triangle
*/

int fact(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}

int nCr(int n, int r) {
    return fact(n) / (fact(r) * fact(n - r));
}

class Node {
   public:
    int key, degree;
    Node *parent, *child, *sibling;

    Node(int _key) {
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

class BinomialHeap {
    Node *head;

    void linkTree(Node *y, Node *z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    void DecreaseKey(Node *node, int newKey) {
        if (newKey > node->key) {
            cout << "The new key is greater than the previous one!" << endl;
        } else {
            node->key = newKey;
            Node *temp = node;
            Node *parent = temp->parent;

            while ((parent != nullptr) && (temp->key < parent->key)) {
                swap(temp->key, parent->key);
                temp = parent;
                parent = temp->parent;
            }
        }
    }

    void heapMerge(BinomialHeap heap) {
        
        Node *thisHead = this->head;
        Node *thatHead = heap.head;
        Node *newHead = nullptr;
        Node *storeHead = nullptr;

        /*
            ! If we merge a non-empty heap to a NULL heap, then simply replace the heads and return.
            ! Otherwise memory violation error comes.
        */
        if (thisHead == nullptr) {
            head = heap.head;
            return;
        }

        if (thisHead->degree <= thatHead->degree) {
            newHead = thisHead;
            thisHead = thisHead->sibling;
        } else {
            newHead = thatHead;
            thatHead = thatHead->sibling;
        }
        storeHead = newHead;

        /*
            ? For the following two Heaps (this and that) we add each and every child according to degree.
            ?? How's that like Mergesort? IDK
        */
        while (thisHead != nullptr && thatHead != nullptr) {
            if (thisHead->degree <= thatHead->degree) {
                newHead->sibling = thisHead;
                thisHead = thisHead->sibling;
            } else {
                newHead->sibling = thatHead;
                thatHead = thatHead->sibling;
            }
            newHead = newHead->sibling;
        }

        if (thisHead != nullptr) {
            while (thisHead != nullptr) {
                newHead->sibling = thisHead;
                thisHead = thisHead->sibling;
                newHead = newHead->sibling;
            }
        }

        if (thatHead != nullptr) {
            while (thatHead != nullptr) {
                newHead->sibling = thatHead;
                thatHead = thatHead->sibling;
                newHead = newHead->sibling;
            }
        }
        this->head = storeHead;
    }

   public:
    BinomialHeap() {
        head = nullptr;
    }

    Node *getHead() {
        return this->head;
    }

    void setHead(Node *headNode) {
        this->head = headNode;
    }

    Node *findMinimum() {
        Node *y = nullptr;
        Node *x = head;
        int minimum = INFINITY;

        while (x != nullptr) {
            if (x->key < minimum) {
                minimum = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    void insert(Node *x) {
        BinomialHeap newHeap;
        newHeap.head = x;
        this->Union(newHeap);
    }

    void deleteNode(Node *x) {
        DecreaseKey(x, -(INFINITY - 100));
        extractMin();
    }

    int extractMin() {
        Node *minNode = findMinimum();

	if (minNode == nullptr) return GARBAGE;

        Node *child = minNode->child;
        int extractMinKey = minNode->key;
        Node *iterNode = head;
	
	cout << __LINE__ << endl;

	if (minNode == head) {
		if (minNode->child != nullptr && minNode->sibling != nullptr){
			head = minNode->sibling;
		}
		else if (minNode->child != nullptr && minNode->sibling == nullptr) {
			head = nullptr;
		}
		else if (minNode->child == nullptr && minNode->sibling != nullptr) {
			head = minNode->sibling;
			return minNode->key;
		}
		else if (minNode->child == nullptr && minNode->sibling == nullptr) {
			head = nullptr;
			return minNode->key;
		}
	}

	cout << __LINE__ << endl;
	
	if (minNode != head) {
	        while (iterNode != nullptr) {
	           	if (iterNode->sibling == minNode) {
	                	iterNode->sibling = minNode->sibling;
			}
	            	iterNode = iterNode->sibling;
	        }
	}
        //bhosdike cormen

        // Parent Null kore
        while (child != nullptr) {
            child->parent = nullptr;
            child = child->sibling;
        }

        child = minNode->child;
        stack<Node *> allSibling;

        while (child != nullptr) {
            allSibling.push(child);
            child = child->sibling;
        }

        Node *currHead = allSibling.top();
        Node *headStore = currHead;
        allSibling.pop();

        // resort them to the order
        while (!allSibling.empty()) {
            currHead->sibling = allSibling.top();
            allSibling.pop();
            currHead = currHead->sibling;
        }

        currHead->sibling = nullptr;
        // now final child, previoud first child

        BinomialHeap h;
        h.setHead(headStore);
        Union(h);

        return extractMinKey;
    }

    void Union(BinomialHeap heap) {
        heapMerge(heap);

        Node *prev = nullptr;
        Node *curr = this->head;
        Node *next = curr->sibling;

        while (next != nullptr) {
            if ((curr->degree != next->degree) || ((next->sibling != nullptr) && (next->sibling->degree == curr->degree))) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    linkTree(next, curr);
                } else {
                    if (prev == nullptr) {
                        head = next;
                    } else {
                        prev->sibling = next;
                    }
                    linkTree(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
    }

    void heapPrint() {
        Node *currPtr = head;
        cout << "Printing Binomial Heap..." << endl;

        while (currPtr != nullptr) {
            int degree = currPtr->degree;
            cout << "Binomial Tree, B" << degree << endl;

            queue<Node *> q;
            q.push(currPtr);
            int level = 0, count = 0, prev_count = 0;

            cout << "Level " << level << " : ";
            while (!q.empty()) {
                Node *p = q.front();
                q.pop();

                /*
                    PASCAL'S TRIANGLE CO-EFFECIENT FORMULA
                    For printing new line and the level numbers.
                */

                if (count == nCr(degree, level) + prev_count) {
                    cout << endl;
                    prev_count = nCr(degree, level) + prev_count;
                    level++;
                    cout << "Level " << level << " : ";
                }

                cout << p->key << " ";
                count++;

                if (p->child != nullptr) {
                    Node *tempPtr = p->child;
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
    Node *node;

    string input;
    while (getline(cin, input)) {
        char first_letter;
        {
            istringstream iss(input);
            iss >> first_letter;

            if (first_letter == 'P') {
                bh.heapPrint();
            }
            else if (first_letter == 'F') {
                node = bh.findMinimum();
		if (node == nullptr)
			cout << "The heap is empty !" << endl;
		else
                	cout << "FindMin returned " << node->key << endl;
            }
            else if (first_letter == 'E') {
                if (bh.findMinimum()) {
                    int key = bh.extractMin();
                    cout << "ExtractMin returned " << key << endl;
                }
            }
            else if (first_letter == 'U') {
                int number;
                vector<int> numbers;
                while (iss >> number) {
                    numbers.push_back(number);
                }

                BinomialHeap heap;
                for (int num : numbers) {
                    node = new Node;
                    node->key = num;
                    heap.insert(node);
                }
                bh.Union(heap);

            }
            else if (first_letter == 'I') {
                int number;
                iss >> number;
                node = new Node;
                node->key = number;
                bh.insert(node);
            }
        }
    }
}


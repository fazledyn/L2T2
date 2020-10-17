#include <iostream>
using namespace std;

#define NIL_KEY -10000
#define BLACK 1
#define RED 2

class Node {
    public:
    int color, key;
    Node *left, *right, *parent;
};

class RBT {

    Node *root, *nil;

    void LeftRotate(Node* x) {
        Node *y = x->right;

        x->right = y->left;
        y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else 
            x->parent->right = y;
        
        y->left = x;
        x->parent = y;
    }
    
    void RightRotate(Node* x) {
        Node *y = x->left;

        x->left = y->right;
        y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nil)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else 
            x->parent->left = y;
        
        y->right = x;
        x->parent = y;
    }

    void InsertFixup(Node* z) {
        while (z->parent->color == RED) {

            if (z->parent == z->parent->parent->left) {
                Node *y = z->parent->parent->right;

                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    RightRotate(z->parent->parent);
                }
            }
            else {
                Node *y = z->parent->parent->left;

                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    Node* DeleteNode(Node* z) {
        Node *y;
        if ((z->left == nil) || (z->right == nil)) {
            y = z;
        }
        else {
            y = Successor(z);
        }

        Node *x;
        if (y->left != nil)
            x = y->left;
        else
            x = y->right;

        x->parent = y->parent;

        if (y->parent == nil) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }

        if ( y != z) 
            z->key = y->key;
        
        if (y->color == BLACK)
            DeleteFixup(x);

        return y;
    }

    void DeleteFixup(Node *x) {
        while ( (x->color == BLACK) && (x != root) ) {
            if (x == x->parent->left){
                Node *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                
                if ( (w->left->color == BLACK) && (w->right->color == BLACK) ) {
                    w->color = RED;
                    x = x->parent;
                }
                else {

                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root;
                }
            }
            else {
                Node *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                
                if ( (w->right->color == BLACK) && (w->left->color == BLACK) ) {
                    w->color = RED;
                    x = x->parent;
                }
                else {

                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node* Minimum(Node* x) {
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }

    Node* Successor(Node* x) {
        if (x->right != nil) {
            return Minimum(x->right);
        }
        Node *y = x->parent;
        while ((y != nil) && (x == y->right)) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node* SearchForDelete(Node* node, int data) {
        if (node->key == data){
            return node;
        } 
        else if (node->key > data) {
            if (node->left != nil)
                return SearchForDelete(node->left, data);
        }
        else {
            if (node->right != nil)
                return SearchForDelete(node->right, data);
        }
        return nullptr;
    }

    public:
    RBT() {
        nil = new Node;
        root = new Node;

        nil->color = BLACK;
        nil->key = NIL_KEY;
        root = nil;
    }

    Node* getRoot(){
        return root;
    }

    void Print(Node *x) {

        if (x != nil) {
            cout << x->key << ":";
            if (x->color == BLACK)  cout << "b";
            else                    cout << "r";

            if ((x->left != nil) || (x->right != nil)) {    
                cout << "(";
                Print(x->left);
                cout << ")" << "(";
                Print(x->right);
                cout << ")";
            }
        }
    }

    void Insert(Node *z) {
        Node *y = nil;
        Node *x = root;

        while (x != nil) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nil) 
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else 
            y->right = z;
        
        z->left = nil;
        z->right = nil;
        z->color = RED;
        InsertFixup(z);
    }

    bool Search(Node* node, int data) {
        bool found = false;
        //cout << "key: " << node->key << endl;
        if (node == nil)
            return found;

        if (node->key == data) 
            found = true;
        else if (node->key > data) {
            if (node->left != nil)
                found = Search(node->left, data);
        }
        else {
            if (node->right != nil)
                found = Search(node->right, data);
        }
        return found;
    }

    void Delete(Node* node, int data) {
        if (Search(node, data)) {    
            Node *target = SearchForDelete(node, data);
            DeleteNode(target);
        }
    }
};


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    RBT rbt;
    char choice;
    int value;
    Node* x;

    while (cin >> choice >> value) {

        if (choice == 'I') {
            x = new Node;
            x->key = value;
            x->color = BLACK;
            rbt.Insert(x);
            rbt.Print(rbt.getRoot());
        }
        if (choice == 'D') {
            rbt.Delete(rbt.getRoot(), value);
            rbt.Print(rbt.getRoot());
        }
        if (choice == 'F') {
            if (rbt.Search(rbt.getRoot(), value))
                cout << "True";
            else
                cout << "False";
        }
        cout << endl;
    }
    return 0;
}

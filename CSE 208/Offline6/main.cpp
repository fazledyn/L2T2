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
    public:
    Node *root, *nil;

    RBT() {
        nil = new Node;
        root = new Node;

        nil->color = BLACK;
        nil->key = NIL_KEY;
        root = nil;
    }

    void Print(Node *x) {
        // 2:b(1:b)(5:r(3:b()(4:r))(7:b))
        if (x != nil) {
            if (x == root) {
                cout << x->key << ":";
                if (x->color == RED) cout << "r";
                else cout << "b";    
            }
            else {
                cout << "(";
                if (x != nil) { 
                    cout << x->key << ":";
                    if (x->color == RED) cout << "r";
                    else cout << "b";
                }
                cout << ")";
            }
            Print(x->left);
            Print(x->right);
        }
    }

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

    Node* Delete(Node* z) {
        Node *y;
        if ((z->left == nil) || (z->right == nil)) {
            y = z;
        }
        else {
            y = TreeSuccessor(z);
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

    Node* TreeSuccessor(Node *node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    bool Search(Node* node, int data) {
        bool found = false;
        //cout << "key: " << node->key << endl;

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

};



int main() {
    RBT rbt;
    Node* x;

    cout << "started\n";

    x = new Node;
    x->key = 1;
    x->color = BLACK;
    rbt.Insert(x);
    
    x = new Node;
    x->key = 3;
    x->color = BLACK;
    rbt.Insert(x);

    x = new Node;
    x->key = 2;
    x->color = BLACK;
    rbt.Insert(x);
    
    x = new Node;
    x->key = 5;
    x->color = BLACK;
    rbt.Insert(x);

    x = new Node;
    x->key = 7;
    x->color = BLACK;
    rbt.Insert(x);
    
    x = new Node;
    x->key = 4;
    x->color = BLACK;
    rbt.Insert(x);

    // 2:b(1:b)(5:r(3:b()(4:r))(7:b))
    // insert, search works
    // gotta implement delete

    cout << "ended\n";
    if (rbt.Search(rbt.root, 10))
        cout << "found\n";
    else
        cout << "not found\n";

    if (rbt.Search(rbt.root, 5))
        cout << "found\n";
    else 
        cout << "not found\n";

    rbt.Print(rbt.root);

}










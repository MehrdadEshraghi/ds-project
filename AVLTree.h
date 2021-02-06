#include<iostream>
#include <algorithm>
#include "Soldier.h"
#include "Vector.h"

#define pow2(n) (1 << (n))

using namespace std;



class Node {
    friend class AVLTree;
    int strength;
    Node* parent;
    Soldier* soldier;
	Node *left;
	Node *right;
//public:
//    ~Node() {
//        delete soldier;
//    }
};

struct RESULT{
    Node*node;
    int level;
};

class AVLTree {
    Node* root;
    Node* deepest;
    Vector<Soldier*> soldiers;
public:
    AVLTree() {
		root = NULL;
	}

	Soldier* pickSoldierToFight(int _strength) {
	    updateSoldiers();
	    Soldier* result;
	    int low = INT_MAX;
        for(int i = 0; i < soldiers.size(); i++) {
            if(abs(soldiers[i]->getStrength() - _strength) < low) {
                low = abs(soldiers[i]->getStrength() - _strength);
                result = soldiers[i];
            }
        }
        Soldier* l = new Soldier(result->getStrength(), result->getCastleNum(), result->getDistance());
        this->remove(l->getStrength());
        return l;
	}

    void updateSoldiers() {
        _updateSoldiers(root);
    }

    void _updateSoldiers(Node* tree) {
        if (tree == NULL)
            return;
        _updateSoldiers(tree->left);
        soldiers.push_back(tree->soldier);
        _updateSoldiers(tree->right);
    }



    int height(Node *temp) {
        int h = 0;
        if (temp != NULL) {
            int l_height = height(temp->left);
            int r_height = height(temp->right);
            int maxHeight = max(l_height, r_height);
            h = maxHeight + 1;
        }
        return h;
    }

    int diff(Node *temp) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    Node* doubleRightRotate(Node *parent) {
        Node *temp;
        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    Node* doubleLeftRotation(Node *parent) {
        Node *temp;
        temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    Node* leftRightRotation(Node *parent) {
        Node *temp;
        temp = parent->left;
        parent->left = doubleRightRotate(temp);
        return doubleLeftRotation(parent);
    }

    Node* rightLeftRotation(Node *parent) {
        Node *temp;
        temp = parent->right;
        parent->right = doubleLeftRotation(temp);
        return doubleRightRotate(parent);
    }

    Node* balance(Node *temp) {
        int bal_factor = diff(temp);
        if (bal_factor > 1) {
            if (diff(temp->left) > 0)
                temp = doubleLeftRotation(temp);
            else
                temp = leftRightRotation(temp);
        }
        else if (bal_factor < -1) {
            if (diff(temp->right) > 0)
                temp = rightLeftRotation(temp);
            else
                temp = doubleRightRotate(temp);
        }
        return temp;
    }

    Node* _insert(Node *root, int strength, Soldier* _soldier, Node* _parent) {
        if (root == NULL) {
            root = new Node;
            root->soldier = _soldier;
            root->strength = strength;
            root->left = NULL;
            root->right = NULL;
            root->parent = _parent;
            return root;
        }
        else if (strength < root->strength) {
            root->left = _insert(root->left, strength, _soldier, root);
            root = balance(root);
        }
        else if (strength >= root->strength) {
            root->right = _insert(root->right, strength, _soldier, root);
            root = balance(root);
        }
        return root;
    }

    void insert(Soldier* _soldier) {
        this->root = _insert(this->root, _soldier->getStrength(), _soldier, NULL);
    }

    void _display(Node *ptr, int level) {
        int i;
        if (ptr != NULL) {
            _display(ptr->right, level + 1);
            printf("\n");
            if (ptr == root)
                cout << "Root -> ";
            for (i = 0; i < level && ptr != root; i++)
                cout << "        ";
            cout << ptr->strength;
            _display(ptr->left, level + 1);
        }
    }

    void display() {
        _display(this->root, 1);
    }


    void _inorder(Node *tree) {
        if (tree == NULL)
            return;
        _inorder(tree->left);
        cout << tree->strength << "  ";
        _inorder(tree->right);
    }

    void inorder() {
        _inorder(this->root);
    }

    void _preorder(Node *tree) {
        if (tree == NULL)
            return;
        cout << tree->strength << "  ";
        _preorder(tree->left);
        _preorder(tree->right);

    }

    void preorder() {
        _preorder(this->root);
    }

    Node* findMin(Node* t) {
        if (t == NULL) return NULL;
        else if (t->left == NULL) return t;
        else return findMin(t->left);
    }

    Node*  findMax(Node* t) {
        if (t == NULL) return NULL;
        else if (t->right == NULL) return t;
        else return findMax(t->right);
    }

    void _postorder(Node *tree) {
        if (tree == NULL)
            return;
        _postorder(tree->left);
        _postorder(tree->right);
        cout << tree->strength << "  ";
    }

    void postorder() {
        _postorder(this->root);
    }

    Soldier* pullSoldier() {
        if(root == NULL) {
            return NULL;
        }
        this->deepest = getDeepest(root).node;
        this->remove(deepest->soldier->getStrength());
//        if(deepest == root) {
            int a = this->deepest->soldier->getCastleNum();
            int b = this->deepest->soldier->getDistance();
            int c = this->deepest->soldier->getStrength();
//            root = NULL;
            return new Soldier(c, a, b);
//        }
//        if(deepest == deepest->parent->right)
//            deepest->parent->right = NULL;
//        else
//            deepest->parent->left = NULL;
//        return deepest->soldier;


//        if(isLeavesEmpty()) return NULL;
//        Node* s = this->leaves[leaves.size() - 1];
//        cout << s->soldier->getStrength() << endl;
//        if(s == root) {
//            int a = this->root->soldier->getCastleNum();
//            int b = this->root->soldier->getDistance();
//            int c = this->root->soldier->getStrength();
//            root = NULL;
//            return new Soldier(c, a, b);
//        }
//        if(s->parent) {
//            if(s == s->parent->right)
//                s->parent->right = NULL;
//            else
//                s->parent->left = NULL;
//        }
//        this->leaves.pop_back();
//        return s->soldier;
    }

    Node* _remove(Node* t, int x) {
        Node* temp;
        if (t == NULL) return NULL;
        else if (x < t->strength) t->left = _remove(t->left, x);
        else if (x >t->strength) t->right = _remove(t->right, x);
        else if (t->left && t->right) {
            temp = findMin(t->right);
            t->strength = temp->strength;
            t->right = _remove(t->right, t->strength);
        }
        else {
            temp = t;
            if (t->left == NULL) t = t->right;
            else if (t->right == NULL) t = t->left;
            delete temp;
        }
        if (t == NULL) return t;
        t = balance(t);
    }

    void remove(int strength) {
        this->root = _remove(this->root, strength);
    }

    bool isEmpty() {
        if(!this->root) return true;
        return false;
    }

    void find(Node *root, int level, int &maxLevel, Node* &res) {
        if (root != NULL) {
            find(root->left, ++level, maxLevel, res);
            if (level > maxLevel) {
                res = root;
                maxLevel = level;
            }
            find(root->right, level, maxLevel, res);
        }
    }

    Node* deepestNode(Node *root) {
        Node* res = NULL;
        int maxLevel = -1;
        find(root, 0, maxLevel, res);
        return res;
    }

    RESULT getDeepest( Node *root ){
        if( root == NULL ){
            RESULT result = {NULL, 0};
            return result;
        }
        RESULT lResult = getDeepest( root->left );
        RESULT rResult = getDeepest( root->right );
        RESULT result = lResult.level < rResult.level ? rResult : lResult;
        ++ result.level;
        if( result.node == NULL )
            result.node = root;
        return result;
    }
};


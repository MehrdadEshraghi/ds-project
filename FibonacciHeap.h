#pragma once
#include <cmath>

struct FibHeapNode
{
	int key;
	FibHeapNode* left;
	FibHeapNode* right;
	FibHeapNode* parent;
	FibHeapNode* child;
	int degree;
	bool mark;
};


class FibHeap {
public:
	FibHeapNode* m_minNode;
	int m_numOfNodes;

	FibHeap() {
		m_minNode = nullptr;
		m_numOfNodes = 0;
	}

	~FibHeap() {
		_clear(m_minNode);
	}

    FibHeapNode* insert(int newKey) {
        FibHeapNode* newNode = _create_node(newKey);
        _insert_node(newNode);
        return newNode;
    }

    void merge(FibHeap &another) {
        m_minNode = _merge(m_minNode, another.m_minNode);
        m_numOfNodes += another.m_numOfNodes;
        another.m_minNode = nullptr;
        another.m_numOfNodes = 0;
    }

    int  extract_min() {
        FibHeapNode* minNode = _extract_min_node();
        int ret = minNode->key;
        delete minNode;
        return ret;
    }

    void decrease_key(FibHeapNode* x, int newKey) {
        _decrease_key(x, newKey);
    }

    void delete_node(FibHeapNode* x) {
        _decrease_key(x, m_minimumKey);
        extract_min();
    }

private:
	static const int m_minimumKey;
    FibHeapNode* _create_node(int newKey) {
        FibHeapNode* newNode = new FibHeapNode;
        newNode->key = newKey;
        newNode->left = newNode;
        newNode->right = newNode;
        newNode->parent = nullptr;
        newNode->child = nullptr;
        newNode->degree = 0;
        newNode->mark = false;
        return newNode;
    }


    void _insert_node(FibHeapNode* newNode) {
        m_minNode = _merge( m_minNode, newNode);
        m_numOfNodes++;
    }

    void _remove_from_circular_list(FibHeapNode* x) {
        if (x->right == x)
            return;
        FibHeapNode* leftSib = x->left;
        FibHeapNode* rightSib = x->right;
        leftSib->right = rightSib;
        rightSib->left = leftSib;
    }

    FibHeapNode* _merge(FibHeapNode* a, FibHeapNode* b) {
        if(a == nullptr)
            return b;
        if(b == nullptr)
            return a;
        if( a->key > b->key )
        {
            FibHeapNode* temp = a;
            a = b;
            b = temp;
        }
        FibHeapNode* aRight = a->right;
        FibHeapNode* bLeft	= b->left;
        a->right = b;
        b->left = a;
        aRight->left = bLeft;
        bLeft->right = aRight;
        return a;
    }

    FibHeapNode* _extract_min_node() {
        FibHeapNode* min = m_minNode;
        if ( min != nullptr) {
            _unparent_all(min->child);
            _merge(min, min->child);
            _remove_from_circular_list(min);
            if ( min == min->right)
                m_minNode = nullptr;
            else {
                m_minNode = min->right;
                _consolidate();
            }
            m_numOfNodes--;
        }
        return min;
    }

    void _unparent_all(FibHeapNode* x) {
        if(x == nullptr)
            return;
        FibHeapNode* y = x;
        do {
            y->parent = nullptr;
            y = y->right;
        }while(y != x);
    }


    void _consolidate() {
        int Dn = (int)(log2(m_numOfNodes) / log2(1.618));
        FibHeapNode** A = new FibHeapNode*[Dn+1];
        for (int i = 0; i < Dn+1; i++)
            A[i] = nullptr;
        FibHeapNode* x = m_minNode;
        bool breakFlag = false;
        while(true) {
            int d = x->degree;
            while( A[d] != nullptr) {
                FibHeapNode* y = A[d];
                if (y == x) {
                    breakFlag = true;
                    break;
                }
                if ( x->key > y->key ) {
                    FibHeapNode* temp = x;
                    x = y;
                    y = temp;
                }
                _make_child(y, x);
                A[d++] = nullptr;
            }
            if (breakFlag)
                break;
            A[x->degree] = x;
            x = x->right;
        }
        m_minNode = x;
        FibHeapNode* iter = x;
        do {
            if ( iter->key < m_minNode->key )
                m_minNode = iter;
            iter = iter->right;
        } while( iter != x );
        delete []A;
    }

    void _make_child(FibHeapNode *child, FibHeapNode *parent) {
        _remove_from_circular_list(child);
        child->left = child->right = child;
        child->parent = parent;
        parent->child = _merge(parent->child, child);
        parent->degree++;
        child->mark = false;
    }

    void _decrease_key(FibHeapNode* x, int newKey) {
        x->key = newKey;
        FibHeapNode* y = x->parent;
        if ( y != nullptr && x->key < y->key ) {
            _cut(x, y);
            _cascading_cut(y);
        }
        if (x->key < m_minNode->key)
            m_minNode = x;
    }

    void _cut(FibHeapNode* x, FibHeapNode* y) {
        _remove_from_circular_list(x);
        if (x->right == x)
            y->child = nullptr;
        else
            y->child = x->right; // update y's child
        y->degree--;
        _merge(m_minNode, x);
        x->parent = nullptr;
        x->mark = false;
    }

    void _cascading_cut(FibHeapNode* y) {
        FibHeapNode* z = y->parent;
        if ( z != nullptr) {
            if( y->mark == false)
                y->mark = true;
            else {
                _cut(y,z);
                _cascading_cut(z);
            }
        }
    }

    void _clear(FibHeapNode* x) {
        if ( x != nullptr )
        {
            FibHeapNode* t1 = x;
            do{
                FibHeapNode* t2 = t1;
                t1 = t1->right;
                _clear(t2->child);
                delete t2;
            } while(t1 != x);
        }
    }
};

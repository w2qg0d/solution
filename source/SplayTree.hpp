//
//  SplayTree.hpp
//  Data Structure
//
//  Created by w2qg0d on 2023/2/7.
//

#ifndef SplayTree_h
#define SplayTree_h

template <typename ElemType>
struct SplayNode
{
    ElemType data;
    SplayNode* parent;
    SplayNode* lchild;
    SplayNode* rchild;
    SplayNode(ElemType e)
        : data(e)
        , parent(nullptr)
        , lchild(nullptr)
        , rchild(nullptr) {}
};

template <typename ElemType>
class SplayTree
{
    SplayNode<ElemType>* root;
public:
    SplayTree(void);
    ~SplayTree(void);
    void insert(ElemType);
    void remove(ElemType);
    void clear(void);
    void print(void);
private:
    void left_rotate(SplayNode<ElemType>*);
    void right_rotate(SplayNode<ElemType>*);
    void splay(SplayNode<ElemType>*);
    void clear(SplayNode<ElemType>*&);
    void print(SplayNode<ElemType>*&);
};

template <typename ElemType>
void SplayTree<ElemType>::left_rotate(SplayNode<ElemType>* old_root)
{
    SplayNode<ElemType>* new_root;
    new_root = old_root->rchild;
    old_root->rchild = new_root->lchild;
    if (old_root->rchild)
        old_root->rchild->parent = old_root;
    new_root->parent = old_root->parent;
    if (!new_root->parent)
        root = new_root;
    else if (old_root == new_root->parent->lchild)
        new_root->parent->lchild = new_root;
    else
        new_root->parent->rchild = new_root;
    new_root->lchild = old_root;
    old_root->parent = new_root;
}

template <typename ElemType>
void SplayTree<ElemType>::right_rotate(SplayNode<ElemType>* old_root)
{
    SplayNode<ElemType>* new_root;
    new_root = old_root->lchild;
    old_root->lchild = new_root->rchild;
    if (old_root->lchild)
        old_root->lchild->parent = old_root;
    new_root->parent = old_root->parent;
    if (!new_root->parent)
        root = new_root;
    else if (old_root == new_root->parent->lchild)
        new_root->parent->lchild = new_root;
    else
        new_root->parent->rchild = new_root;
    new_root->rchild = old_root;
    old_root->parent = new_root;
}

template <typename ElemType>
void SplayTree<ElemType>::splay(SplayNode<ElemType>* current)
{
    SplayNode<ElemType>* parent, * grandparent;
    while (current->parent)
    {
        parent = current->parent;
        grandparent = parent->parent;
        if (!grandparent)
        {
            if (current == parent->lchild)
                right_rotate(parent);
            else
                left_rotate(parent);
        }
        else if (parent == grandparent->lchild && current == parent->lchild)
        {
            right_rotate(grandparent);
            right_rotate(parent);
        }
        else if (parent == grandparent->lchild && current == parent->rchild)
        {
            left_rotate(parent);
            right_rotate(grandparent);
        }
        else if (parent == grandparent->rchild && current == parent->rchild)
        {
            left_rotate(grandparent);
            left_rotate(parent);
        }
        else
        {
            right_rotate(parent);
            left_rotate(grandparent);
        }
    }
}

template <typename ElemType>
void SplayTree<ElemType>::insert(ElemType e)
{
    SplayNode<ElemType>* current = root;
    SplayNode<ElemType>* parent = nullptr;
    while (current)
    {
        parent = current;
        if (e < current->data)
            current = current->lchild;
        else if (e > current->data)
            current = current->rchild;
        else
            return;
    }
    current = new SplayNode<ElemType>(e);
    current->parent = parent;
    if (!parent)
        root = current;
    else if (e < parent->data)
        parent->lchild = current;
    else
        parent->rchild = current;
    splay(current);
}

template <typename ElemType>
void SplayTree<ElemType>::remove(ElemType e)
{
    SplayNode<ElemType>* current = root;
    SplayNode<ElemType>* tmp, * left_tree, * right_tree;
    while (current)
        if (e < current->data)
            current = current->lchild;
        else if (e > current->data)
            current = current->rchild;
        else
            break;
    if (!current)
        return;
    splay(current);
    left_tree = current->lchild;
    right_tree = current->rchild;
    delete current;
    if (left_tree)
        left_tree->parent = nullptr;
    if (right_tree)
        right_tree->parent = nullptr;
    if (left_tree && right_tree)
    {
        for (tmp = right_tree; tmp->lchild; tmp = tmp->lchild);
        splay(tmp);
        root = tmp;
        tmp->lchild = left_tree;
        left_tree->parent = tmp;
    }
    else if (left_tree)
        root = left_tree;
    else
        root = right_tree;
}

template <typename ElemType>
SplayTree<ElemType>::SplayTree(void)
{
    root = nullptr;
}

template <typename ElemType>
SplayTree<ElemType>::~SplayTree(void)
{
    clear(root);
}


template <typename ElemType>
void SplayTree<ElemType>::clear(void)
{
    clear(root);
}

template <typename ElemType>
void SplayTree<ElemType>::clear(SplayNode<ElemType>*& T)
{
    if (T)
    {
        clear(T->lchild);
        clear(T->rchild);
        delete T;
        T = nullptr;
    }
}

template <typename ElemType>
void SplayTree<ElemType>::print(void)
{
    print(root);
    std::cout << std::endl;
}

template <typename ElemType>
void SplayTree<ElemType>::print(SplayNode<ElemType>*& T)
{
    if (T)
    {
        print(T->lchild);
        std::cout << T->data << " ";
        print(T->rchild);
    }
}

#endif /* SplayTree_h */

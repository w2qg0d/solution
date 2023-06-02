//
//  AVLTree.hpp
//  Data Structure
//
//  Created by w2qg0d on 2023/2/12.
//

#ifndef AVLTree_h
#define AVLTree_h

template <typename ElemType>
struct AVLNode
{
    ElemType data;
    int bf;
    AVLNode* parent;
    AVLNode* lchild;
    AVLNode* rchild;
    AVLNode(ElemType e)
        : data(e)
        , bf(0)
        , parent(nullptr)
        , lchild(nullptr)
        , rchild(nullptr) {}
};

template <typename ElemType>
class AVLTree
{
    AVLNode<ElemType>* root;
public:
    AVLTree(void);
    ~AVLTree(void);
    void insert(ElemType);
    void remove(ElemType);
    void clear(void);
    void print(void);
private:
    void left_rotate(AVLNode<ElemType>*);
    void right_rotate(AVLNode<ElemType>*);
    void clear(AVLNode<ElemType>*&);
    void print(AVLNode<ElemType>*&);
};

template <typename ElemType>
void AVLTree<ElemType>::left_rotate(AVLNode<ElemType>* old_root)
{
    AVLNode<ElemType>* new_root;
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
void AVLTree<ElemType>::right_rotate(AVLNode<ElemType>* old_root)
{
    AVLNode<ElemType>* new_root;
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
void AVLTree<ElemType>::insert(ElemType e)
{
    AVLNode<ElemType>* current = root;
    AVLNode<ElemType>* parent = nullptr;
    // =========================== Search
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
    // =========================== Insert
    current = new AVLNode<ElemType>(e);
    current->parent = parent;
    if (!parent)
        root = current;
    else if (e < parent->data)
        parent->lchild = current;
    else
        parent->rchild = current;
    // =========================== Rebalance
    while (parent)
    {
        if (current == parent->lchild)
            parent->bf++;
        else
            parent->bf--;
        if (parent->bf == 0)
            break;
        if (parent->bf == 1 || parent->bf == -1)
        {
            current = parent;
            parent = current->parent;
            continue;
        }
        if (parent->bf == 2 && current->bf == 1)
        {
            right_rotate(parent);
            current->bf = parent->bf = 0;
            break;
        }
        if (parent->bf == 2 && current->bf == -1)
        {
            left_rotate(current);
            right_rotate(parent);
            if (current->parent->bf == 1)
            {
                current->bf = current->parent->bf = 0;
                parent->bf = -1;
            }
            else if (current->parent->bf == -1)
            {
                parent->bf = parent->parent->bf = 0;
                current->bf = 1;
            }
            else
                current->bf = current->parent->bf = parent->bf = 0;
            break;
        }
        if (parent->bf == -2 && current->bf == -1)
        {
            left_rotate(parent);
            current->bf = parent->bf = 0;
            break;
        }
        if (parent->bf == -2 && current->bf == 1)
        {
            right_rotate(current);
            left_rotate(parent);
            if (current->parent->bf == -1)
            {
                current->bf = current->parent->bf = 0;
                parent->bf = 1;
            }
            else if (current->parent->bf == 1)
            {
                parent->bf = parent->parent->bf = 0;
                current->bf = -1;
            }
            else
                current->bf = current->parent->bf = parent->bf = 0;
            break;
        }
    }
}

template <typename ElemType>
void AVLTree<ElemType>::remove(ElemType e)
{
    AVLNode<ElemType>* current = root;
    AVLNode<ElemType>* parent, * sibling, * target, * tmp;
    // =========================== Search
    while (current)
        if (e < current->data)
            current = current->lchild;
        else if (e > current->data)
            current = current->rchild;
        else
            if (current->rchild)
            {
                for (tmp = current->rchild; tmp->lchild; tmp = tmp->lchild);
                e = current->data = tmp->data;
                current = tmp;
            }
            else if (current->lchild)
            {
                e = current->data = current->lchild->data;
                current = current->lchild;
            }
            else
                break;
    if (!current)
        return;
    target = current;
    // =========================== Rebalance
    while (current != root)
    {
        parent = current->parent;
        if (current == parent->lchild)
        {
            parent->bf--;
            sibling = parent->rchild;
        }
        else
        {
            parent->bf++;
            sibling = parent->lchild;
        }
        if (parent->bf == 0)
        {
            current = parent;
            continue;
        }
        if (parent->bf == 1 || parent->bf == -1)
            break;
        if (parent->bf == 2 && sibling->bf == 0)
        {
            right_rotate(parent);
            parent->bf = 1;
            sibling->bf = -1;
            break;
        }
        if (parent->bf == 2 && sibling->bf == 1)
        {
            right_rotate(parent);
            parent->bf = sibling->bf = 0;
            current = sibling;
            continue;
        }
        if (parent->bf == 2 && sibling->bf == -1)
        {
            left_rotate(sibling);
            right_rotate(parent);
            if (parent->parent->bf >= 0)
                sibling->bf = 0;
            else
                sibling->bf = 1;
            if (parent->parent->bf <= 0)
                parent->bf = 0;
            else
                parent->bf = -1;
            parent->parent->bf = 0;
            current = parent->parent;
            continue;
        }
        if (parent->bf == -2 && sibling->bf == 0)
        {
            left_rotate(parent);
            parent->bf = -1;
            sibling->bf = 1;
            break;
        }
        if (parent->bf == -2 && sibling->bf == -1)
        {
            left_rotate(parent);
            parent->bf = sibling->bf = 0;
            current = sibling;
            continue;
        }
        if (parent->bf == -2 && sibling->bf == 1)
        {
            right_rotate(sibling);
            left_rotate(parent);
            if (parent->parent->bf <= 0)
                sibling->bf = 0;
            else
                sibling->bf = -1;
            if (parent->parent->bf >= 0)
                parent->bf = 0;
            else
                parent->bf = 1;
            parent->parent->bf = 0;
            current = parent->parent;
            continue;
        }
    }
    // =========================== Delete
    if (target == root)
        root = nullptr;
    else if (target == target->parent->lchild)
        target->parent->lchild = nullptr;
    else
        target->parent->rchild = nullptr;
    delete target;
}
template <typename ElemType>
AVLTree<ElemType>::AVLTree()
{
    root = nullptr;
}

template <typename ElemType>
AVLTree<ElemType>::~AVLTree()
{
    clear(root);
}

template <typename ElemType>
void AVLTree<ElemType>::clear(void)
{
    clear(root);
}

template <typename ElemType>
void AVLTree<ElemType>::clear(AVLNode<ElemType>*& T)
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
void AVLTree<ElemType>::print(void)
{
    print(root);
    std::cout << std::endl;
}

template <typename ElemType>
void AVLTree<ElemType>::print(AVLNode<ElemType>*& T)
{
    if (T)
    {
        print(T->lchild);
        std::cout << T->data << " ";
        print(T->rchild);
    }
}

#endif /* AVLTree_h */

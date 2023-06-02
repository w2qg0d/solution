//
//  RedBlackTree.hpp
//  Data Structure
//
//  Created by 汪文谦 on 2023/2/3.
//

#ifndef RedBlackTree_h
#define RedBlackTree_h

enum ColorType
{
    red = false,
    black = true
};

template <typename ElemType>
struct RedBlackNode
{
    ElemType data;
    ColorType color;
    RedBlackNode* parent;
    RedBlackNode* lchild;
    RedBlackNode* rchild;
    RedBlackNode(ElemType e)
        : data(e)
        , parent(nullptr)
        , lchild(nullptr)
        , rchild(nullptr) {}
};

template <typename ElemType>
class RedBlackTree
{
    RedBlackNode<ElemType>* root;
public:
    RedBlackTree(void);
    ~RedBlackTree(void);
    void insert(ElemType);
    void remove(ElemType);
    void clear(void);
    void print(void);
private:
    void left_rotate(RedBlackNode<ElemType>*);
    void right_rotate(RedBlackNode<ElemType>*);
    void clear(RedBlackNode<ElemType>*&);
    void print(RedBlackNode<ElemType>*&);
    bool CheckBalance(void);
    bool CheckBalance(RedBlackNode<ElemType>*, int, int);
};

template <typename ElemType>
void RedBlackTree<ElemType>::left_rotate(RedBlackNode<ElemType>* old_root)
{
    RedBlackNode<ElemType>* new_root;
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
void RedBlackTree<ElemType>::right_rotate(RedBlackNode<ElemType>* old_root)
{
    RedBlackNode<ElemType>* new_root;
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
void RedBlackTree<ElemType>::insert(ElemType e)
{
    RedBlackNode<ElemType>* current = root;
    RedBlackNode<ElemType>* parent = nullptr;
    RedBlackNode<ElemType>* grandparent, * uncle;
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
    current = new RedBlackNode<ElemType>(e);
    current->parent = parent;
    if (!parent)
        root = current;
    else if (e < parent->data)
        parent->lchild = current;
    else
        parent->rchild = current;
    // =========================== Rebalance
    while (parent && parent->color == red)
    {
        grandparent = parent->parent;
        if (parent == grandparent->lchild)
        {
            uncle = grandparent->rchild;
            if (uncle && uncle->color == red)
            { // Case 1
                parent->color = uncle->color = black;
                grandparent->color = red;
                current = grandparent;
                parent = current->parent;
                continue;
            }
            if (current == parent->lchild)
            { // Case 2
                right_rotate(grandparent);
                parent->color = black;
                grandparent->color = red;
                break;
            }
            if (current == parent->rchild)
            { // Case 3
                left_rotate(parent);
                right_rotate(grandparent);
                current->color = black;
                grandparent->color = red;
                break;
            }
        }
        else
        {
            uncle = grandparent->lchild;
            if (uncle && uncle->color == red)
            { // Case 1
                parent->color = uncle->color = black;
                grandparent->color = red;
                current = grandparent;
                parent = current->parent;
                continue;
            }
            if (current == parent->rchild)
            { // Case 2
                left_rotate(grandparent);
                parent->color = black;
                grandparent->color = red;
                break;
            }
            if (current == parent->lchild)
            { // Case 3
                right_rotate(parent);
                left_rotate(grandparent);
                current->color = black;
                grandparent->color = red;
                break;
            }
        }
    }
    root->color = black;
}

template <typename ElemType>
void RedBlackTree<ElemType>::remove(ElemType e)
{
    RedBlackNode<ElemType>* current = root;
    RedBlackNode<ElemType>* parent, * sibling, * target, * tmp;
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
    while (current != root && current->color == black)
    {
        parent = current->parent;
        if (current == parent->lchild)
        {
            sibling = parent->rchild;
            if (sibling->color == red)
            { // Case 1
                left_rotate(parent);
                sibling->color = black;
                parent->color = red;
                sibling = parent->rchild;
            }
            if (sibling->rchild && sibling->rchild->color == red)
            { // Case 2
                left_rotate(parent);
                sibling->color = parent->color;
                sibling->lchild->color = sibling->rchild->color = black;
                break;
            }
            if (sibling->lchild && sibling->lchild->color == red)
            { // Case 3
                right_rotate(sibling);
                left_rotate(parent);
                parent->parent->color = parent->color;
                parent->color = black;
                break;
            }
            if (parent->color == red)
            { // Case 4
                sibling->color = red;
                parent->color = black;
                break;
            }
            if (parent->color == black)
            { // Case 5
                sibling->color = red;
                current = parent;
                continue;
            }
        }
        else
        {
            sibling = parent->lchild;
            if (sibling->color == red)
            { // Case 1
                right_rotate(parent);
                sibling->color = black;
                parent->color = red;
                sibling = parent->lchild;
            }
            if (sibling->lchild && sibling->lchild->color == red)
            { // Case 2
                right_rotate(parent);
                sibling->color = parent->color;
                sibling->lchild->color = sibling->rchild->color = black;
                break;
            }
            if (sibling->rchild && sibling->rchild->color == red)
            { // Case 3
                left_rotate(sibling);
                right_rotate(parent);
                parent->parent->color = parent->color;
                parent->color = black;
                break;
            }
            if (parent->color == red)
            { // Case 4
                sibling->color = red;
                parent->color = black;
                break;
            }
            if (parent->color == black)
            { // Case 5
                sibling->color = red;
                current = parent;
                continue;
            }
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
RedBlackTree<ElemType>::RedBlackTree(void)
{
    root = nullptr;
}

template <typename ElemType>
RedBlackTree<ElemType>::~RedBlackTree(void)
{
    clear(root);
}

template <typename ElemType>
void RedBlackTree<ElemType>::clear(void)
{
    clear(root);
}

template <typename ElemType>
void RedBlackTree<ElemType>::clear(RedBlackNode<ElemType>*& T)
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
void RedBlackTree<ElemType>::print(void)
{
    print(root);
    if (CheckBalance())
    {
        std::cout << " 平衡";
    }
    std::cout << std::endl;
}

template <typename ElemType>
void RedBlackTree<ElemType>::print(RedBlackNode<ElemType>*& T)
{
    if (T)
    {
        print(T->lchild);
        std::cout << T->data << " ";
        print(T->rchild);
    }
}

template <typename ElemType>
bool RedBlackTree<ElemType>::CheckBalance(void)
{
    if (!root)
        return true;
    // 根结点是黑色的
    if (root->color != black)
    {
        printf("根结点不是黑色的\n");
        return false;
    }
    // 每一条路径黑色结点的个数必须是相同的
    int BlcakNum = 0;
    RedBlackNode<ElemType>* left = root;
    while (left)
    {
        // 统计某一条路径的所有黑色结点个数
        if (left->color == black)
            BlcakNum++;
        left = left->lchild;
    }
    // 检查连续的红色结点，检查每一条路径的黑色结点个数是否相等
    return CheckBalance(root, BlcakNum ,0);
}

template <typename ElemType>
bool RedBlackTree<ElemType>::CheckBalance(RedBlackNode<ElemType>* T, int BlackNum, int count)
{
    if (!T)
    {
        if (BlackNum != count)
        {
            printf("黑色结点个数不均等\n");
            return false;
        }
        // 遍历完整棵树，如果以上列举的非法情况都不存在就返回true
        return true;
    }
    // 检查是否出现连续的红色结点
    if (T->color == red && T->parent->color == red)
    {
        printf("出现了连续的红色结点\n");
        return false;
    }
    // 走前序遍历的过程中记录每一条路径黑色结点的个数
    if (T->color == black)
        count++;
    // 递归左右子树
    return CheckBalance(T->lchild, BlackNum, count) && CheckBalance(T->rchild, BlackNum, count);
}

#endif /* RedBlackTree_h */

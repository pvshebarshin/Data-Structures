#ifndef DATA_STRUCTURES_AVL_BST_H
#define DATA_STRUCTURES_AVL_BST_H

#include <stdexcept>
#include <iostream>

template<typename T>
class AVL_BST
{
private:
    class Node
    {
    public:
        Node(T data) noexcept;

        T data;
        int height;
        Node* left_ptr;
        Node* right_ptr;
        int getHeight() const noexcept;
    };

    Node* root;

    Node* singleRightRotate(Node* &node) noexcept;
    Node* singleLeftRotate(Node* &node) noexcept;
    Node* doubleLeftRotate(Node* &node) noexcept;
    Node* doubleRightRotate(Node* &data) noexcept;

    void remove(Node* node) noexcept;
    Node* add(T& data, Node* node) noexcept;
    bool contains(T& data, Node* node) const noexcept;

public:
    AVL_BST() noexcept;
    AVL_BST(T data) noexcept;
    ~AVL_BST();

    void add(T data) noexcept;

    bool contains(T data) const noexcept;
    bool isEmpty() const noexcept;
    T max() const;



    void inorder(Node* t) {
        if (t == NULL)
            return;
        inorder(t->left_ptr);
        std::cout << t->data << " ";
        inorder(t->right_ptr);
    }
    void display()
    {
        inorder(root);
        std::cout << std::endl;
    }
};

template<typename T>
AVL_BST<T>::Node::Node(T data) noexcept
{
    this->data = data;
    left_ptr = right_ptr = nullptr;
    height = 0;
}

template<typename T>
int AVL_BST<T>::Node::getHeight() const noexcept
{
    return (this == NULL || this == nullptr ? -1 : this->height);
}

template<typename T>
AVL_BST<T>::AVL_BST() noexcept
{
    root = nullptr;
}

template<typename T>
AVL_BST<T>::AVL_BST(T data) noexcept
{
    root = new Node(data);
}

template<typename T>
void AVL_BST<T>::add(T data) noexcept
{
    root = add(data, root);
}

template<typename T>
typename AVL_BST<T>::Node* AVL_BST<T>::add(T& data, AVL_BST::Node* node) noexcept
{
    if(node == nullptr){
        node = new Node(data);
    }else if(data < node->data){
        node->left_ptr = add(data, node->left_ptr);
        if(node->left_ptr->getHeight() - node->right_ptr->getHeight() == 2)
        {
            if(data < node->left_ptr->data)
                node = singleRightRotate(node);
            else
                node = doubleRightRotate(node);
        }
    }else if(data > node->data){
        node->right_ptr = add(data, node->right_ptr);
        if(node->right_ptr->getHeight() - node->left_ptr->getHeight() == 2)
        {
            if(data > node->right_ptr->data)
                node = singleLeftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }
    node->height = (node->left_ptr->getHeight() > node->right_ptr->getHeight()
            ? node->left_ptr->getHeight() : node->right_ptr->getHeight()) + 1;
}

template<typename T>
typename AVL_BST<T>::Node *AVL_BST<T>::singleRightRotate(AVL_BST::Node* &node) noexcept
{
    Node* temp = node->left_ptr;
    node->left_ptr = temp->right_ptr;
    temp->right_ptr = node;
    node->height = (node->left_ptr->getHeight() > node->right_ptr->getHeight()
            ? node->left_ptr->getHeight() : node->right_ptr->getHeight()) + 1;
    temp->height = (temp->left_ptr->getHeight() > node->getHeight()
            ? temp->left_ptr->getHeight() : node->getHeight()) + 1;
    return temp;
}

template<typename T>
typename AVL_BST<T>::Node *AVL_BST<T>::singleLeftRotate(AVL_BST::Node* &node) noexcept
{
    Node* temp = node->right_ptr;
    node->right_ptr = temp->left_ptr;
    temp->left_ptr = node;
    node->height = (node->left_ptr->getHeight() > node->right_ptr->getHeight()
            ? node->left_ptr->getHeight() : node->right_ptr->getHeight()) + 1;
    temp->height = (temp->right_ptr->getHeight() > node->getHeight()
            ? temp->right_ptr->getHeight() : node->getHeight()) + 1;
    return temp;
}

template<typename T>
typename AVL_BST<T>::Node *AVL_BST<T>::doubleLeftRotate(AVL_BST::Node* &node) noexcept
{
    node->right_ptr = singleRightRotate(node->right_ptr);
    return singleLeftRotate(node);
}

template<typename T>
typename AVL_BST<T>::Node *AVL_BST<T>::doubleRightRotate(AVL_BST::Node* &data) noexcept
{
    data->left_ptr = singleLeftRotate(data->left_ptr);
    return singleRightRotate(data);
}

template<typename T>
AVL_BST<T>::~AVL_BST()
{
    remove(root);
}

template<typename T>
void AVL_BST<T>::remove(AVL_BST::Node *node) noexcept
{
    if (node != nullptr)
    {
        Node* right = node->right_ptr;
        Node* left = node->left_ptr;
        remove(right);
        remove(left);
        delete node;
    }
}

template<typename T>
bool AVL_BST<T>::contains(T data) const noexcept
{
    if(root == nullptr){
        return false;
    } else if(root->data == data){
        return true;
    } else if(data < root->data && root->left_ptr != nullptr){
        return contains(data, root->left_ptr);
    } else if(data > root->data && root->right_ptr != nullptr){
        return contains(data, root->right_ptr);
    } else {
        return false;
    }
}

template<typename T>
bool AVL_BST<T>::contains(T& data, AVL_BST::Node* node) const noexcept
{
    if(node == nullptr){
        return false;
    } else if(node->data == data){
        return true;
    } else if(data < node->data && node->left_ptr != nullptr){
        return contains(data, node->left_ptr);
    } else if(data > node->data && node->right_ptr != nullptr){
        return contains(data, node->right_ptr);
    } else {
        return false;
    }
}

template<typename T>
T AVL_BST<T>::max() const
{
    if(root == nullptr){
        throw new std::logic_error("Tree is is_empty");
    } else if(root->left_ptr != nullptr){
        Node* node = root->left_ptr;
        while (node->left_ptr != nullptr)
            node = node->left_ptr;
        return node->data;
    }
    return root->data;
}

template<typename T>
bool AVL_BST<T>::isEmpty() const noexcept
{
    return root == nullptr;
}

#endif

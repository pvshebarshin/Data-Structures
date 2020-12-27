#ifndef DATA_STRUCTURES_AVL_BST_H
#define DATA_STRUCTURES_AVL_BST_H

template<typename T>
class AVL
{
private:
    class Node
    {
    public:
        Node(T data);

        T data;
        int height;
        Node* left_ptr;
        Node* right_ptr;
    };

    Node* root;

    Node* singleRightRotate(Node* &node) noexcept;
    Node* singleLeftRotate(Node* &node) noexcept;
    Node* doubleLeftRotate(Node* &node) noexcept;
    Node* doubleRightRotate(Node* &data) noexcept;

    void remove(Node* node) noexcept;
    void add(T& data, Node* node) noexcept;
    bool contains(T& data, Node* node) const noexcept;

public:
    AVL();
    AVL(T data) noexcept;
    ~AVL();

    void add(T data);

    bool contains(T data) const noexcept;
};

template<typename T>
AVL<T>::Node::Node(T data)
{
    this->data = data;
    left_ptr = right_ptr = nullptr;
    height = 0;
}

template<typename T>
AVL<T>::AVL()
{
    root = nullptr;
}

template<typename T>
AVL<T>::AVL(T data) noexcept
{
    root = new Node(data);
}

template<typename T>
void AVL<T>::add(T data)
{
    if(root == nullptr) {
        root = new Node(data);
    } else if(data < root->data){
        if(root->left_ptr == nullptr)
            root->left_ptr = new Node(data);
        else
            add(data, root->left_ptr);
    } else if(data > root->data){
        if(root->right_ptr == nullptr)
            root->right_ptr = new Node(data);
        else
            add(data, root->right_ptr);
    }
}

template<typename T>
void AVL<T>::add(T& data, AVL::Node* node) noexcept
{
    if(node == nullptr){
        node = new Node(data);
    }else if(data < node->data){
        add(data, node->left_ptr);
        if(node->left_ptr->height - node->right_ptr->height == 2)
        {
            if(data < node->left_ptr->data)
                node = singleRightRotate(node);
            else
                node = doubleRightRotate(node);
        }
    }else if(data > node->data){
        add(data, node->right_ptr);
        if(node->right_ptr->height - node->left_ptr->height == 2)
        {
            if(data > node->right_ptr->data)
                node = singleLeftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }
    node->height = (node->left_ptr->height > node->right_ptr->height
            ? node->left_ptr->height : node->right_ptr->height) + 1;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::singleRightRotate(AVL::Node* &node) noexcept
{
    Node* temp = node->left_ptr;
    node->left_ptr = temp->right_ptr;
    temp->right_ptr = node;
    node->height = (node->left_ptr->height > node->right_ptr->height
            ? node->left_ptr->height : node->right_ptr->height) + 1;
    temp->height = (temp->left_ptr->height > node->height
            ? temp->left_ptr->height : node->height) + 1;
    return temp;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::singleLeftRotate(AVL::Node* &node) noexcept
{
    Node* temp = node->right_ptr;
    node->right_ptr = temp->left_ptr;
    temp->left_ptr = node;
    node->height = (node->left_ptr->height > node->right_ptr->height
            ? node->left_ptr->height : node->right_ptr->height) + 1;
    temp->height = (temp->right_ptr->height > node->height
            ? temp->right_ptr->height : node->height) + 1;
    return temp;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::doubleLeftRotate(AVL::Node* &node) noexcept
{
    node->right_ptr = singleRightRotate(node->right_ptr);
    return singleLeftRotate(node);
}

template<typename T>
typename AVL<T>::Node *AVL<T>::doubleRightRotate(AVL::Node* &data) noexcept
{
    data->left_ptr = singleLeftRotate(data->left_ptr);
    return singleRightRotate(data);
}

template<typename T>
AVL<T>::~AVL()
{
    remove(root);
}

template<typename T>
void AVL<T>::remove(AVL::Node *node) noexcept
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
bool AVL<T>::contains(T data) const noexcept
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
bool AVL<T>::contains(T& data, AVL::Node* node) const noexcept
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

#endif

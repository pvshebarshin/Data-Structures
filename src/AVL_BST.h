#ifndef DATA_STRUCTURES_AVL_BST_H
#define DATA_STRUCTURES_AVL_BST_H

#include <stdexcept>

template<typename T>
class AVL_BST
{
public:
    AVL_BST() noexcept;
    AVL_BST(T data) noexcept;
    ~AVL_BST();
    // Get the tree's height.
    int getHeight() const noexcept;
    // Insert the value into the tree.
    void add(T data);
    // Print the tree.
    void print();
    // Remove the value from the tree.
    void remove(T data);

    bool is_empty() const noexcept;

    bool contains(T data) const noexcept;

    T min() const;
    T max() const;

private:
    class Node
    {
    public:
        Node(T data) noexcept;
        // Calculate the balance point.
        int getBalance() const noexcept;
        // Remove the node's parent.
        void removeParent() noexcept;
        // Set the node's height.
        void update_height() noexcept;

        T data;
        int height;
        Node* left_child;
        Node* right_child;
        Node* parent;
    };

    Node *root;

    void balance_node(Node* node);
    // Find the node containing the data.
    Node* find_node(T data) const noexcept;
    // Print the subtree.
    void printSubtree(Node *subtree, int depth, int offset, bool first);
    // Rotate the subtree left.
    void left_rotation(Node* node) noexcept;
    // Rotate the subtree left.
    void right_rotation(Node* node) noexcept;
    // Set the root.
    void set_root(Node* node) noexcept;
    // Figure out the default spacing for element.
    int spacing(int offset);

    void remove(Node* node) noexcept;
};

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
int AVL_BST<T>::getHeight() const noexcept
{
    return root->height;
}

template<typename T>
void AVL_BST<T>::add(T data)
{
    if (root == nullptr) {
        root = new Node(data);
    } else {
        Node* added_node = nullptr;
        Node* temp = root;
        while (temp != nullptr && added_node == nullptr)
            if (data < temp->data)
                if (temp->left_child == nullptr)
                    added_node = temp->left_child = new Node(data);
                else
                    temp = temp->left_child;
            else if (data > temp->data)
                if (temp->right_child == nullptr)
                    added_node = temp->right_child = new Node(data);
                else
                    temp = temp->right_child;
            else
                throw new std::logic_error("Element already exists");

        temp = added_node;
        while(temp != nullptr)
        {
            temp->update_height();
            balance_node(temp);
            temp = temp->parent;
        }
    }
}

template<typename T>
void AVL_BST<T>::balance_node(AVL_BST::Node* node)
{
    int bal = node->getBalance();
    if (bal > 1) {
        if (node->left_child->getBalance() < 0)
            left_rotation(node->left_child);
        right_rotation(node);
    } else if (bal < -1) {
        if (node->right_child->getBalance() > 0)
            right_rotation(node->right_child);
        left_rotation(node);
    }
}

template<typename T>
void AVL_BST<T>::left_rotation(AVL_BST::Node* node) noexcept
{
    enum {left, right} side;
    Node *p = node->parent;
    if (p != nullptr && p->left_child == node)
        side = left;
    else
        side = right;

    Node *temp = node->right_child;
    node->right_child = temp->left_child;
    temp->left_child = node;

    if (p == nullptr)
        set_root(temp);
    else if (side == left)
        p->left_child = temp;
    else
        p->right_child = temp;
}

template<typename T>
void AVL_BST<T>::right_rotation(AVL_BST::Node* node) noexcept
{
    enum {left, right} side;
    Node *p = node->parent;
    if (p != nullptr && p->left_child == node)
        side = left;
    else
        side = right;

    Node *temp = node->left_child;
    node->left_child = temp->right_child;
    temp->right_child = node;

    if (p == nullptr)
        set_root(temp);
    else if (side == left)
        p->left_child = temp;
    else
        p->right_child = temp;
}

template<typename T>
void AVL_BST<T>::set_root(AVL_BST::Node* node) noexcept
{
    root = node;
    if (root != nullptr)
        root->removeParent();
}

template<typename T>
bool AVL_BST<T>::is_empty() const noexcept
{
    return root == nullptr;
}

template<typename T>
bool AVL_BST<T>::contains(T data) const noexcept
{
    return find_node(data) != nullptr;
}

template<typename T>
typename AVL_BST<T>::Node* AVL_BST<T>::find_node(T data) const noexcept
{
    Node* node = root;
    while (node != nullptr) {
        if (data == node->data)
            break;
        else if (data < node->data)
            node = node->left_child;
        else
            node = node->right_child;
    }
    return node;
}

template<typename T>
AVL_BST<T>::~AVL_BST()
{
    remove(root);
}

template<typename T>
void AVL_BST<T>::remove(AVL_BST::Node* node) noexcept
{
    if (node != nullptr)
    {
        Node* right = node->right_child;
        Node* left = node->left_child;
        remove(right);
        remove(left);
        delete node;
    }
}

template<typename T>
T AVL_BST<T>::min() const
{
    if(root == nullptr) {
        throw new std::logic_error("Tree is is_empty");
    } else if(root->left_child != nullptr) {
        Node* node = root->left_child;
        while (node->left_child != nullptr)
            node = node->left_child;
        return node->data;
    }
    return root->data;
}

template<typename T>
T AVL_BST<T>::max() const
{
    if(root == nullptr) {
        throw new std::logic_error("Tree is is_empty");
    } else if(root->right_child != nullptr) {
        Node* node = root->right_child;
        while (node->right_child != nullptr)
            node = node->right_child;
        return node->data;
    }
    return root->data;
}

template<typename T>
void AVL_BST<T>::remove(T data)
{
    Node *toBeRemoved = find_node(data);
    if (toBeRemoved == nullptr)
        throw new std::logic_error("There are no such data tree");

    enum {left, right} side;
    Node* pointer = toBeRemoved->parent;
    if (pointer != nullptr && pointer->left_child == toBeRemoved)
        side = left;
    else
        side = right;

    if (toBeRemoved->left_child == nullptr)
        if (toBeRemoved->right_child == nullptr) {

            if (pointer == nullptr) {
                set_root(nullptr);
                delete toBeRemoved;

            } else {
                if (side == left)
                    pointer->left_child = nullptr;
                else
                    pointer->right_child = nullptr;
                delete toBeRemoved;
                pointer->update_height();
                balance_node(pointer);
            }
        } else {
            if (pointer == nullptr) {
                set_root(toBeRemoved->right_child);
                delete toBeRemoved;
            } else {
                if (side == left)
                    pointer->left_child = toBeRemoved->right_child;
                else
                    pointer->right_child = toBeRemoved->right_child;
                delete toBeRemoved;
                pointer->update_height();
                balance_node(pointer);
            }
        }
    else if (toBeRemoved->right_child == nullptr) {
        if (pointer == nullptr) {
            set_root(toBeRemoved->left_child);
            delete toBeRemoved;
        } else {
            if(side == left)
                pointer->left_child = toBeRemoved->left_child;
            else
                pointer->right_child = toBeRemoved->left_child;
            delete toBeRemoved;
            pointer->update_height();
            balance_node(pointer);
        }
    } else {
        Node* replacement;
        Node* replacement_parent;
        Node* temp_node;
        int bal = toBeRemoved->getBalance();
        if (bal > 0) {
            if (toBeRemoved->left_child->right_child == nullptr) {
                replacement = toBeRemoved->left_child;
                replacement->right_child = toBeRemoved->right_child;
                temp_node = replacement;
            } else {
                replacement = toBeRemoved->left_child->right_child;
                while (replacement->right_child != nullptr)
                    replacement = replacement->right_child;
                replacement_parent = replacement->parent;
                replacement_parent->right_child = replacement->left_child;
                temp_node = replacement_parent;
                replacement->left_child = toBeRemoved->left_child;
                replacement->right_child = toBeRemoved->right_child;
            }
        } else if (toBeRemoved->right_child->left_child == nullptr) {
            replacement = toBeRemoved->right_child;
            replacement->left_child = toBeRemoved->left_child;
            temp_node = replacement;
        } else {
            replacement = toBeRemoved->right_child->left_child;
            while (replacement->left_child != nullptr)
                replacement = replacement->left_child;
            replacement_parent = replacement->parent;
            replacement_parent->left_child = replacement->right_child;
            temp_node = replacement_parent;
            replacement->left_child = toBeRemoved->left_child;
            replacement->right_child = toBeRemoved->right_child;
        }
        if (pointer == nullptr)
            set_root(replacement);
        else if (side == left)
            pointer->left_child = replacement;
        else
            pointer->right_child = replacement;
        delete toBeRemoved;
        balance_node(temp_node);
    }
}

template<typename T>
AVL_BST<T>::Node::Node(T data) noexcept
{
    this->data = data;
    height = 0;
    parent = left_child = right_child = nullptr;
}

template<typename T>
void AVL_BST<T>::Node::update_height() noexcept
{
    if (left_child == nullptr)
        if (right_child == nullptr)
            height = 0;
        else
            height = right_child->height+1;
    else if (right_child == nullptr)
        height = left_child->height + 1;
    else if (left_child->height > right_child->height)
        height = left_child->height + 1;
    else
        height = right_child->height + 1;
}

template<typename T>
int AVL_BST<T>::Node::getBalance() const noexcept
{
    int result;
    if (left_child == nullptr)
        if (right_child == nullptr)
            result = 0;
        else
            result = -right_child->height - 1;
    else if (right_child == nullptr)
        result = left_child->height + 1;
    else
        result = left_child->height - right_child->height;
    return result;
}

template<typename T>
void AVL_BST<T>::Node::removeParent() noexcept
{
    parent = nullptr;
}

#endif

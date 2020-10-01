#ifndef LIST_H
#define LIST_H

template<typename T>
class List
{
public:
    List(T data) noexcept;
    List() noexcept;
    List(const List<T>& list) noexcept;
    ~List() noexcept;

    T front() const;
    T back() const;

    T& operator[] (int index);
    const T& operator[] (int index) const;
    bool operator==(const List<T>& list) const noexcept;
    bool operator!=(const List<T>& list) const noexcept;

    void push_back(T data) noexcept;
    void push_front(T data) noexcept;
    T pop_front();
    T pop_back();
    T pop(int index);

    int getSize() const noexcept;
    bool empty() const noexcept;

private:
    class Node
    {
    public:
        Node(T data, Node* pNext = nullptr) noexcept;
        T data;
        Node* pNext;
    };
    int size;
    Node* head;
};

template<typename T>
List<T>::List() noexcept
{
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::List(T data) noexcept
{
    size = 1;
    head = new Node(data);
}

template<typename T>
int List<T>::getSize() const noexcept
{
    return size;
}

template<typename T>
bool List<T>::empty() const noexcept
{
    return head == nullptr;
}

template<typename T>
List<T>::~List() noexcept
{
    for(int i = 0; i < size; ++i)
    {
        Node* temp = head;
        head = head->pNext;
        delete temp;
    }
}

template<typename T>
T List<T>::front() const
{
    if(size == 0)
        throw new std::logic_error("list is empty");
    return head->data;
}

template<typename T>
T List<T>::back() const
{
    if(size == 0)
        throw new std::logic_error("list is empty");
    Node* temp = head;
    for(int i = 0; i < size - 1; ++i)
        temp = temp->pNext;
    return temp->data;
}

template<typename T>
T& List<T>::operator[](const int index)
{
    if(index >= size || index < 0 || size == 0)
        throw new std::out_of_range("incorrect size");
    Node* temp = head;
    for(int i = 0; i < index; ++i)
        temp = temp->pNext;
    return temp->data;
}

template<typename T>
List<T>::List(const List<T> &list) noexcept
{
    if(list.getSize() == 0){
        size = 0;
        head = nullptr;
    } else {
        size = 1;
        head = new Node(list[0]);
        for(int i = 1; i < list.size; ++i)
            push_back(list[i]);
    }
}

template<typename T>
void List<T>::push_back(T data) noexcept
{
    ++size;
    Node* temp = head;
    while(temp->pNext != nullptr)
        temp = temp->pNext;
    temp->pNext = new Node(data);
}

template<typename T>
const T &List<T>::operator[](int index) const
{
    if(index >= size || index < 0 || size == 0)
        throw new std::out_of_range("incorrect size");
    Node* temp = head;
    for(int i = 0; i < index; ++i)
        temp = temp->pNext;
    return temp->data;
}

template<typename T>
bool List<T>::operator==(const List<T> &list) const noexcept
{
    if(size != list.getSize())
        return false;
    for(int i = 0; i < size; ++i)
        if((*this)[i] != list[i])
            return false;
    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T> &list) const noexcept
{
    return !(*this == list);
}

template<typename T>
void List<T>::push_front(T data) noexcept
{
    ++size;
    Node* newHead = new Node(data);
    newHead->pNext = head;
    head = newHead;
}

template<typename T>
T List<T>::pop_front()
{
    if(size == 0)
        throw new std::logic_error("list is empty");
    --size;
    T temp = head->data;
    Node* node = head;
    if(node->pNext != nullptr)
        head = head->pNext;
    delete node;
    return temp;
}

template<typename T>
T List<T>::pop_back()
{
    if(size == 0)
        throw new std::logic_error("list is empty");
    --size;
    Node* temp_node = head;
    for(int i = 0; i < size; ++i)
        temp_node = temp_node->pNext;
    T temp = temp_node->data;
    delete temp_node;
    return temp;
}

template<typename T>
T List<T>::pop(int index)
{
    if(size == 0)
        throw new std::logic_error("list is empty");
    if(index < 0 || index >= size)
        throw new std::out_of_range("incorrect size");
    --size;
    Node* node = head;
    for(int i = 1; i < index - 1; ++i)
        node = node->pNext;
    T temp = node->pNext->data;
    Node* tempNode = node->pNext;
    node->pNext = node->pNext->pNext;
    delete tempNode;
    return temp;
}

template<typename T>
List<T>::Node::Node(T data, List::Node *pNext) noexcept
{
    this->data = data;
    this->pNext = pNext;
}

#endif

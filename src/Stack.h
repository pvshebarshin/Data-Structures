#ifndef STACK_H
#define STACK_H
#include <stdexcept>
template<typename T>
class Stack
{
public:
    explicit Stack(int size = 1024);
    ~Stack() noexcept;

    void push(T item);
    T pop();
    T top() const;

    bool is_full() const noexcept;
    bool is_empty() const noexcept;

    void clear() noexcept;

    int size() const noexcept;

    void compound(Stack<T>& _stack);

private:
    int MAX_SIZE;
    int head;
    T* stack;
};

template<typename T>
Stack<T>::Stack(int size)
{
    if(size <= 0)
        throw std::logic_error("incorrect data");
    MAX_SIZE = size;
    stack = new T[size];
    head = -1;
}

template<typename T>
Stack<T>::~Stack() noexcept
{
    delete[] stack;
}

template<typename T>
bool Stack<T>::is_full() const noexcept
{
    return MAX_SIZE == head + 1;
}

template<typename T>
bool Stack<T>::is_empty() const noexcept
{
    return head == -1;
}

template<typename T>
void Stack<T>::push(T item)
{
    if(!is_full()) {
        ++head;
        stack[head] = item;
    } else {
        throw std::logic_error("stack is full");
    }
}

template<typename T>
void Stack<T>::clear() noexcept
{
    delete[] stack;
    head = -1;
    stack = new T[MAX_SIZE];
}

template<typename T>
T Stack<T>::pop()
{
    if(is_empty())
        throw std::logic_error("stack is empty");
    return stack[head--];
}

template<typename T>
T Stack<T>::top() const
{
    if(!is_empty())
        return stack[head];
    throw std::logic_error("stack is empty");
}

template<typename T>
int Stack<T>::size() const noexcept
{
    return head + 1;
}

template<typename T>
void Stack<T>::compound(Stack<T>& _stack)
{
    if(head + 1 + _stack.size() > MAX_SIZE)
        throw std::logic_error("no place for item");
    int temp = _stack.size();
    for(int i = 0; i < temp; ++i)
        push(_stack.pop());
}

#endif

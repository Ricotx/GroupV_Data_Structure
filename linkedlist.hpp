#pragma once
#include "model.hpp"

using namespace std;

template<typename T>
class ListNode {
public:
    T data;
    ListNode<T>* next;
    ListNode<T>* prev;
    
    ListNode(const T& item) : data(item), next(nullptr), prev(nullptr) {}
    
    ~ListNode() {
        // Data will be cleaned up by its own destructor
    }
};

template<typename T>
class CustomLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;
    
public:
    CustomLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~CustomLinkedList() {
        clear();
    }
    
    // Copy constructor (needed for data loading)
    CustomLinkedList(const CustomLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // Assignment operator (needed for data loading)
    CustomLinkedList& operator=(const CustomLinkedList& other) {
        if (this != &other) {
            clear();
            ListNode<T>* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // Essential for data loading
    void push_back(const T& item) {
        ListNode<T>* newNode = new ListNode<T>(item);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    
    // Essential for data access
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Essential for data management
    int getSize() const {
        return size;
    }
    
    bool empty() const {
        return size == 0;
    }
    
    void clear() {
        while (head != nullptr) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
};

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Libraries / Classes
#include <iostream>
#include <string>
#include <sstream>

template <typename T>

class LinkedList {

private:

    struct Node {

        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}

    };

    Node* head;
    Node* tail;
    int count;

public:

    // Constructor
    LinkedList() {

        head = nullptr;
        tail = nullptr;
        count = 0;

    }

    // Copy Constructor
    LinkedList(const LinkedList& other) {

        head = nullptr;
        tail = nullptr;
        count = 0;
        Node* current = other.head;

        while (current != nullptr) {

            push_back(current->data);
            current = current->next;

        }

    }

    // Destructor
    ~LinkedList() {

        clear();

    }

    void clear() {

        while (head != nullptr) {

            Node* temp = head;
            head = head->next;
            delete temp;

        }

        tail = nullptr;
        count = 0;

    }

    bool empty() const {

        return count == 0;

    }

    int size() const {

        return count;

    }

    void push_back(const T& value) {

        // Create a new node
        Node* pushBackNode = new Node(value);

        // If the list is empty, set the head to the new node
        if (head == nullptr) {

            head = pushBackNode;
            tail = pushBackNode;

        }
        // Otherwise, set the tail's next to the new node
        else {

            tail->next = pushBackNode;

            // Set the tail to the new node
            tail = pushBackNode;

        }

        // Increment the count
        count++;

    }

    void push_front(const T& value) {

        // Create a new node
        Node* pushFrontNode = new Node(value);

        // If the list is empty, set the tail to the new node
        if (head == nullptr) {

            head = pushFrontNode;
            tail = pushFrontNode;

        }
        else {

            // Set the new node's next to the head
            pushFrontNode->next = head;

            // Set the head to the new node
            head = pushFrontNode;

        }

        // Increment the count
        count++;

    }

    void insert(int index, const T& value) {

        // If the index is out of range, throw an exception
        if (index < 0 || index > count) {

            throw std::out_of_range("Index out of range");

        }

        // Create a new node
        Node* insertNode = new Node(value);

        // If the index is 0, set the new node's next to the head
        if (index == 0) {

            insertNode->next = head;

            // Set the head to the new node
            head = insertNode;

        }
        // Otherwise, iterate through the list to the index - 1 node
        else {

            Node* currentNode = head;

            for (int i = 0; i < index - 1; ++i) {

                currentNode = currentNode->next;

            }

            // Set the new node's next to the index node's next
            insertNode->next = currentNode->next;

            // Set the index node's next to the new node
            currentNode->next = insertNode;

        }

        // If the index is the last node, set the tail to the new node
        if (index == count) {

            tail->next = insertNode;
            tail = insertNode;

        }

        // Increment the count
        count++;

    }

    void pop_back() {

        // if the list is empty, throw an exception
        if (head == nullptr) {

            throw std::out_of_range("Empty list");

        }

        // If the head is the tail, delete the head
        if (head == tail) {

            delete head;
            head = nullptr;
            tail = nullptr;

        }
        // Otherwise, iterate through the list to the node before the tail
        else {

            Node* currentNode = head;

            while (currentNode->next != tail) {

                currentNode = currentNode->next;

            }

            // Delete the tail
            delete tail;

            // Set the tail to the node before the tail
            tail = currentNode;

            // Set the tail's next to nullptr
            tail->next = nullptr;

        }

        // Decrement the count
        count--;

    }

    void pop_front() {

        // if the list is empty, throw an exception
        if (head == nullptr) {

            throw std::out_of_range("Empty list");

        }

        // Set the head to the next node
        Node* oldHead = head;
        head = head->next;

        // Delete the old head
        delete oldHead;

        // Decrement the count
        count--;

    }

    void erase(int index) {

        if (index < 0 || index >= count) {

            throw std::out_of_range("Index out of range");

        }

        if (index == 0) {

            Node* temp = head;
            head = head->next;
            delete temp;

        }

        else {

            Node* temp = head;
            
            for (int i = 0; i < index - 1; i++) {

                temp = temp->next;

            }

            Node* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;

            if (index == count - 1) {

                tail = temp;

            }

        }

        count--;

    }

    T front() const {

        if (empty()) {

            throw std::out_of_range("LinkedList is empty");

        }

        return head->data;

    }

    T back() const {

        if (empty()) {

            throw std::out_of_range("LinkedList is empty");

        }

        return tail->data;

    }

    std::string toString() const {

        std::string result = "";
        Node* temp = head;
        bool first = true;

        while (temp != nullptr) {

            std::stringstream ss;
            ss << temp->data;

            if (!first) {

                result.append(" ");

            }
            else {

                first = false;

            }

            result.append(ss.str());
            temp = temp->next;

        }

        return result;

    }

    void print() const {

        std::cout << toString() << std::endl;

    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {

        if (this != &other) {

            clear();
            Node* temp = other.head;

            while (temp != nullptr) {

                push_back(temp->data);
                temp = temp->next;

            }

        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {

        os << list.toString();
        return os;

    }

    // This is an iterator function that allows an action to be performed upon each element.
    void traverse(std::function<void(const T&)> action) const {

        Node* current = head;

        while (current) {

            action(current->data);
            current = current->next;

        }

    }

    // This function is situationally useful for this project, and is used to remove an element based on a string attribute.
    bool deleteCharacter(const std::string& name) {

        // Establish traversal nodes.
        Node<T> current = head;
        Node<T> previous = nullptr;

        while (current) {

            if (current->data.name == name) {

                if (previous) {

                    previous->next = current->next;

                }
                else {

                    head = current->next;

                }

                delete current;
                return true;

            }

            previous = current;
            current = current->next;

        }

        return false;

    }

};

#endif // LINKEDLIST_H
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

class Node {
public:
    std::string sender;
    std::string content;
    long long timestamp;
    Node* next;

    // Constructor
    Node(const std::string& sender, const std::string& content, long long timestamp);
};

class LinkedList {
private:
    Node* head;

        // Helper function to merge two sorted linked lists
    Node* merge(Node* left, Node* right);

    // Helper function to perform merge sort on the linked list
    Node* mergeSort(Node* start);
public:
    // Constructor
    LinkedList();

    Node* getHead(){ return head;}
    // Destructor to free memory
    ~LinkedList();

    // Function to insert a node at the end of the list
    void insert(const std::string& sender, const std::string& content, long long timestamp);

    // Function to print the list
    void display();

    // Function (and helpers) to sort the list by timestamp
    void sortByTimestamp();

    // Writes sorted list to file
    void writeToFile(std::string& path);
};

#endif // LINKEDLIST_H

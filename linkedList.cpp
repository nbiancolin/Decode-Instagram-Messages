#include "linkedList.h"
#include <iostream>
#include <fstream>

// Node class implementation
Node::Node(const std::string& sender, const std::string& content, long long timestamp)
    : sender(sender), content(content), timestamp(timestamp), next(nullptr) {}

// LinkedList class implementation
LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* nextNode;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Helper function to merge two sorted linked lists
Node* LinkedList::merge(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node* result = nullptr;

    if (left->timestamp <= right->timestamp) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Helper function to perform merge sort on the linked list
Node* LinkedList::mergeSort(Node* start) {
    if (start == nullptr || start->next == nullptr) {
        return start;
    }

    Node* slow = start;
    Node* fast = start->next;

    // Move fast pointer two steps, and slow pointer one step
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* right = slow->next;
    slow->next = nullptr;  // Split the list into two halves

    Node* leftSorted = mergeSort(start);
    Node* rightSorted = mergeSort(right);

    // Merge the sorted halves
    return merge(leftSorted, rightSorted);
}

// Function to sort the list by timestamp using merge sort
void LinkedList::sortByTimestamp() {
    head = mergeSort(head);
}


void LinkedList::insert(const std::string& sender, const std::string& content, long long timestamp) {
    Node* newNode = new Node(sender, content, timestamp);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::display() {
    Node* current = head;

    while (current != nullptr) {
        std::cout << "Sender: " << current->sender << ", Content: " << current->content
                  << ", Timestamp: " << current->timestamp << std::endl;
        current = current->next;
    }
}



void LinkedList::writeToFile(std::string& path) {
    std::ofstream outFile(path);

    if (!outFile.is_open()) {
        std::cerr << "Error opening the file for writing." << std::endl;
        return;
    }

    outFile << "Nick's Instagram Message Converter thingy\n" << std::endl;

    Node* current = head;
    std::string prevSender = "";
    
    while (current != nullptr) {
        // Print name
        if (current->sender != prevSender) {
            outFile << current->sender << "\n(" << current->timestamp << ") ";
        } else {
            outFile << "(" << current->timestamp << ") ";
        }

        outFile << current->content << "\n";
        prevSender = current->sender;
        current = current->next;
    }

    outFile << "\nEnd of messages" << std::endl;
    outFile.close();
}

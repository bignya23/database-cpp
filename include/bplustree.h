#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <cmath>

template <typename K, typename V>
class BPlusTree {
private:
    // Make node size dynamic based on system page size (typically 4KB)
    static const size_t PAGE_SIZE = 4096;  // 4KB
    static const size_t OVERHEAD = sizeof(bool) + 2 * sizeof(void*);  // isLeaf + pointers
    static const size_t KEY_VALUE_SIZE = sizeof(K) + sizeof(V) + sizeof(void*);
    static const int MAX_KEYS = (PAGE_SIZE - OVERHEAD) / KEY_VALUE_SIZE;
    static const int MIN_KEYS = MAX_KEYS / 2;

    struct Node {
        bool isLeaf;
        std::vector<K> keys;
        std::vector<Node*> children;
        Node* next;  // For leaf nodes to form a linked list
        std::vector<V> values;  // Only used in leaf nodes

        Node(bool leaf = false) : isLeaf(leaf), next(nullptr) {
            // Pre-allocate space to avoid frequent reallocations
            keys.reserve(MAX_KEYS);
            if (leaf) {
                values.reserve(MAX_KEYS);
            }
            else {
                children.reserve(MAX_KEYS + 1);
            }
        }

        ~Node() {
            if (!isLeaf) {
                for (Node* child : children) {
                    delete child;
                }
            }
        }
    };

    Node* root;
    size_t size_;  // Track total number of entries

    // Helper function to find position
    int findPosition(const std::vector<K>& keys, const K& key) {
        return std::lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    }

    // Split leaf node
    Node* splitLeafNode(Node* node, K& upKey) {
        Node* newNode = new Node(true);
        int mid = (node->keys.size() + 1) / 2;

        for (int i = mid; i < node->keys.size(); i++) {
            newNode->keys.push_back(node->keys[i]);
            newNode->values.push_back(node->values[i]);
        }

        node->keys.resize(mid);
        node->values.resize(mid);

        newNode->next = node->next;
        node->next = newNode;

        upKey = newNode->keys[0];
        return newNode;
    }

    // Split internal node
    Node* splitInternalNode(Node* node, K& upKey) {
        Node* newNode = new Node(false);
        int mid = node->keys.size() / 2;

        upKey = node->keys[mid];

        for (int i = mid + 1; i < node->keys.size(); i++) {
            newNode->keys.push_back(node->keys[i]);
        }

        for (int i = mid + 1; i <= node->keys.size(); i++) {
            newNode->children.push_back(node->children[i]);
        }

        node->keys.resize(mid);
        node->children.resize(mid + 1);

        return newNode;
    }

    // Insert into leaf
    void insertIntoLeaf(Node* node, const K& key, const V& value) {
        int pos = findPosition(node->keys, key);

        node->keys.insert(node->keys.begin() + pos, key);
        node->values.insert(node->values.begin() + pos, value);
    }

    // Recursive insertion
    Node* insertRecursive(Node* node, const K& key, const V& value, K& upKey) {
        if (node->isLeaf) {
            insertIntoLeaf(node, key, value);
            size_++;

            if (node->keys.size() > MAX_KEYS) {
                return splitLeafNode(node, upKey);
            }
            return nullptr;
        }

        int pos = findPosition(node->keys, key);
        K newUpKey;
        Node* newNode = insertRecursive(node->children[pos], key, value, newUpKey);

        if (newNode == nullptr) {
            return nullptr;
        }

        node->keys.insert(node->keys.begin() + pos, newUpKey);
        node->children.insert(node->children.begin() + pos + 1, newNode);

        if (node->keys.size() > MAX_KEYS) {
            return splitInternalNode(node, upKey);
        }
        return nullptr;
    }

public:
    BPlusTree() : root(new Node(true)), size_(0) {}

    ~BPlusTree() {
        delete root;
    }

    void insert(const K& key, const V& value) {
        K upKey;
        Node* newNode = insertRecursive(root, key, value, upKey);

        if (newNode != nullptr) {
            Node* newRoot = new Node(false);
            newRoot->keys.push_back(upKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newNode);
            root = newRoot;
        }
    }

    // Get total number of entries
    size_t size() const {
        return size_;
    }

    // Print key-value pairs
    void print() {
        std::cout << "Total entries: " << size_ << std::endl;
        std::cout << "Key - Value pairs:" << std::endl;
        std::cout << "=================" << std::endl;

        // Find leftmost leaf
        Node* current = root;
        while (!current->isLeaf) {
            current = current->children[0];
        }

        // Print all leaf nodes
        size_t count = 0;
        while (current != nullptr) {
            for (size_t i = 0; i < current->keys.size(); ++i) {
                std::cout << current->keys[i] << "  -  ";
                for (auto& it : current->values[i]) {
                    std::cout << it << ", ";
                }
                std::cout << std::endl;
                count++;

                // Print progress every 1000 entries
                if (count % 1000 == 0) {
                    std::cout << "... " << count << " entries printed ..." << std::endl;
                }
            }
            current = current->next;
        }
        std::cout << "\nTotal " << count << " entries printed" << std::endl;
    }

    // Print specific range of entries
    void printRange(size_t start, size_t end) {
        if (start >= size_ || end <= start) {
            std::cout << "Invalid range" << std::endl;
            return;
        }

        end = std::min(end, size_);

        Node* current = root;
        while (!current->isLeaf) {
            current = current->children[0];
        }

        size_t count = 0;
        while (current != nullptr && count < end) {
            for (size_t i = 0; i < current->keys.size() && count < end; ++i) {
                if (count >= start) {
                    std::cout << current->keys[i] << " - " << current->values[i] << std::endl;
                }
                count++;
            }
            current = current->next;
        }
    }
};
#pragma once

#include <new>
#include <iostream>

enum Color { RED, BLACK };
class keyAlreadyExists : public std::exception
{
public:
    const char* what() const throw()
    {
        return "Key already exists";
    }
};

template <typename KeyType, typename ValueType>
class Map
{   
struct Node
{
    KeyType key;
    ValueType value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(KeyType k, ValueType v) : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
private:
    Node* root;
    unsigned long int size;

    void rotateLeft(Node* node){
        Node* right = node->right;
        node->right = right->left;
        if(right->left != nullptr){
            right->left->parent = node;
        }
        right->parent = node->parent;
        if(node->parent == nullptr){
            root = right;
        }
        else if(node == node->parent->left){
            node->parent->left = right;
        }
        else{
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    }

    void rotateRight(Node* node){
        Node* left = node->left;
        node->left = left->right;
        if(left->right != nullptr){
            left->right->parent = node;
        }
        left->parent = node->parent;
        if(node->parent == nullptr){
            root = left;
        }
        else if(node == node->parent->right){
            node->parent->right = left;
        }
        else{
            node->parent->left = left;
        }
        left->right = node;
        node->parent = left;
    }
    
    void insertFix(Node* node){
        Node* parent = nullptr;
        Node* grandParent = nullptr;
        while(node != root && node->color == RED && node->parent->color == RED){
            parent = node->parent;
            grandParent = parent->parent;
            if(parent == grandParent->left){
                Node* uncle = grandParent->right;
                if(uncle != nullptr && uncle->color == RED){
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandParent;
                }else{
                    if(node == parent->right){
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandParent);
                    std::swap(parent->color, grandParent->color);
                    node = parent;
                }
            }else{
                Node* uncle = grandParent->left;
                if(uncle != nullptr && uncle->color == RED){
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandParent;
                }else{
                    if(node == parent->left){
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandParent);
                    std::swap(parent->color, grandParent->color);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
        
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void copyTree(Node* node) {
        if (node != nullptr) {
            add(node->key, node->value);
            copyTree(node->left);
            copyTree(node->right);
        }
    }

public:
    Map(){
        root = nullptr;
        size = 0;
    }

    Map(const Map& other){
        root = nullptr;
        size = 0;
        copyTree(other.root);
    }

    ~Map() {
        deleteTree(root);
    }

    Map& operator=(const Map& other) {
        if (this != &other) {
            deleteTree(root);
            root = nullptr;
            size = 0;
            copyTree(other.root);
        }
        return *this;
    }

    void add(KeyType key, ValueType value){
        if(size == 0){
            root = new Node(key, value);
            root->color = BLACK;
            size++;
        }
        else
        {   
            if(findNode(key) != nullptr){
                throw keyAlreadyExists();
            }

            Node* newNode = new Node(key, value);
            Node* parent = nullptr;
            Node* current = root;
            while(current != nullptr){
                parent = current;
                if(key < current->key){
                    current = current->left;
                }else{
                    current = current->right;
                }
            }
            newNode->parent = parent;
            if(parent == nullptr){
                root = newNode;
            }else if(newNode->key < parent->key){
                parent->left = newNode;
            }else{
                parent->right = newNode;
            }
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->color = RED;
            insertFix(newNode);
            size++;
        }
    }

    Node* findNode(KeyType key){
        Node* current = root;
        while(current != nullptr && current->key != key){
            if(key < current->key){
                current = current->left;
            }else{
                current = current->right;
            }
        }
        return current;
    }

    ValueType* find(KeyType key){
        Node* node = findNode(key);
        if(node == nullptr){
            return nullptr;
        }
        return &node->value;
    }

    void transplant(Node* first, Node* second){
        if(first->parent == nullptr){
            root = second;
        }else if(first == first->parent->left){
            first->parent->left = second;
        }else{
            first->parent->right = second;
        }
        if(second != nullptr){
            second->parent = first->parent;
        }
    }

    Node* minimum(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    Node* maximum(Node* node){
        while(node->right != nullptr){
            node = node->right;
        }
        return node;
    }
    
    Node* remove(KeyType key){
        Node* node = findNode(key);
        if(node == nullptr){
            return nullptr;
        }
        Node* temp = node;
        Color originalColor = temp->color;
        Node* nodeToFix = nullptr;
        if(node->left == nullptr){
            nodeToFix = node->right;
            transplant(node, node->right);
        }
        else if(node->right == nullptr){
            nodeToFix = node->left;
            transplant(node, node->left);
        }
        else{
            temp = minimum(node->right);
            originalColor = temp->color;
            nodeToFix = temp->right;
            if(temp->parent == node){
                if(nodeToFix != nullptr){
                    nodeToFix->parent = temp;
                }
            }else{
                transplant(temp, temp->right);
                temp->right = node->right;
                temp->right->parent = temp;
            }
            transplant(node, temp);
            temp->left = node->left;
            temp->left->parent = temp;
            temp->color = node->color;
        }   
        if(originalColor == BLACK){
            removeFix(nodeToFix);
        }
        size--;
        delete node;
        return temp;
    }

    void removeFix(Node* node){
        while(node != root && node != nullptr && node->color == BLACK){
            if(node == node->parent->left){
                Node* sibling = node->parent->right;
                if(sibling != nullptr && sibling->color == RED){
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }
                if((sibling->left == nullptr || sibling->left->color == BLACK) && 
                (sibling->right == nullptr || sibling->right->color == BLACK)){
                    if (sibling != nullptr) sibling->color = RED;
                    node = node->parent;
                }else{
                    if(sibling->right == nullptr || sibling->right->color == BLACK){
                        if(sibling->left != nullptr) sibling->left->color = BLACK;
                        if (sibling != nullptr) sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    if (sibling != nullptr) sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if(sibling->right != nullptr) sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            }else{
                Node* sibling = node->parent->left;
                if(sibling != nullptr && sibling->color == RED){
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }
                if((sibling->right == nullptr || sibling->right->color == BLACK) && 
                (sibling->left == nullptr || sibling->left->color == BLACK)){
                    if (sibling != nullptr) sibling->color = RED;
                    node = node->parent;
                }else{
                    if(sibling->left == nullptr || sibling->left->color == BLACK){
                        if(sibling->right != nullptr) sibling->right->color = BLACK;
                        if (sibling != nullptr) sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    if (sibling != nullptr) sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if(sibling->left != nullptr) sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr) {
            node->color = BLACK;
        }
    }

    unsigned long int getSize(){
        return size;
    }

    Node* getRoot(){
        return root;
    }    

    void inOrderTraversal(Node* node, std::ostream& os){
        if(node != nullptr){
            inOrderTraversal(node->left, os);
            os << node->key << " " << node->value << std::endl;
            inOrderTraversal(node->right, os);
        }
    }
};

template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream& os, Map<KeyType, ValueType>& map){
    map.inOrderTraversal(map.getRoot(), os);
    return os;
}
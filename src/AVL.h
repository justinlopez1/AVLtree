//
// Created by funny on 9/28/2023.
//
#include <string>
#include <utility>
#include <queue>
#include <vector>  // NOT using namespace std lolll
#include <iostream>
#pragma once

#ifndef AVLTREE_AVL_H
#define AVLTREE_AVL_H


class AVLTree {   //node is a private member of avl class  --
    struct Node {
        Node* left;
        Node* right;
        std::string id;
        std::string name;
        int height;
        Node(std::string _id, std::string _name): left(nullptr), right(nullptr), id(std::move(_id)), name(std::move(_name)), height(1) {}
    };
public:              //functions that are used in main, as simple as these functinos can get
    AVLTree();
    void insert(const std::string& id, const std::string& name);
    void remove(const std::string& idToRemove);
    void remove_inorder_N(int n);
    void search_id(const std::string& id);
    void search_name(const std::string& name);
    std::vector<std::string> print_inorder();
    void print_postorder();
    void print_preorder();
    int get_level_count();
private:
    void print_inorder_helper(Node* node, std::vector<std::string> &inorderIDs);   //all helper functions and recursive functinos used for the tree
    void print_postorder_helper(Node* node, std::vector<std::string> &postorderIDs);
    void print_preorder_helper(Node* node, std::vector<std::string> &preorderIDs);
    void search_name_helper(Node* node, const std::string& name, bool &done);
    Node* insert_helper(Node* node, const std::string& id, const std::string& name);
    Node* remove_helper(Node* node, const std::string& id, bool &done);
    static int max(int a, int b);
    static int get_height(Node* node);
    static int get_balance(Node* node);
    static Node* left_rotation(Node* node);
    static Node* right_rotation(Node* node);
    static Node* min_value(Node* subtreeRoot);
    Node* remove_inorder_N_helper(Node* node, int &n, const int &removedN, bool &done);

    Node* root;
};
                                             //im not putting comments in all of these its probably fine its pretty readable anyway
AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::insert(const std::string &id, const std::string &name) {
    if (root == nullptr) {
        root = new Node(id, name);
        std::cout << "successful" << std::endl;
    }
    else
        root = insert_helper(root, id, name);
}

void AVLTree::remove(const std::string &idToRemove) {
    bool done = false;
    root = remove_helper(root, idToRemove, done);
    if (!done) std::cout << "unsuccessful" << std::endl;
}

void AVLTree::search_id(const std::string &id) { //
    if (root == nullptr) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    Node* temp = root;
    while (true) {
        if (temp->id == id) {
            std::cout << temp->name << std::endl;
            return;
        }
        else if (stoi(id) < stoi(temp->id)) {
            if (temp->left != nullptr) {
                temp = temp->left;
            }
            else {
                std::cout << "unsuccessful" << std::endl;
                return;
            }
        }
        else {
            if (temp->right != nullptr) {
                temp = temp->right;
            }
            else {
                std::cout << "unsuccessful" << std::endl;
                return;
            }
        }
    }
}

void AVLTree::search_name(const std::string &name) {
    bool done = false;
    search_name_helper(root, name, done);
    if (!done) std::cout << "unsuccessful" << std::endl;
}

std::vector<std::string> AVLTree::print_inorder() {
    std::vector<std::string> inorderIDs;
    print_inorder_helper(root, inorderIDs);
    for (unsigned int i = 0; i < inorderIDs.size(); i++) {
        std::cout << inorderIDs[i];
        if (i != inorderIDs.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
    return inorderIDs;
}

void AVLTree::print_inorder_helper(AVLTree::Node *node, std::vector<std::string> &inorderIDs) {
    if (node == nullptr)
        return;

    print_inorder_helper(node->left, inorderIDs);

    inorderIDs.push_back(node->name);

    print_inorder_helper(node->right, inorderIDs);
}

void AVLTree::print_postorder() {
    std::vector<std::string> postorderIDs;
    print_postorder_helper(root, postorderIDs);
    for (unsigned int i = 0; i < postorderIDs.size(); i++) {
        std::cout << postorderIDs[i];
        if (i != postorderIDs.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void AVLTree::print_postorder_helper(AVLTree::Node *node, std::vector<std::string> &postorderIDs) {
    if (node == nullptr)
        return;

    print_postorder_helper(node->left, postorderIDs);

    print_postorder_helper(node->right, postorderIDs);

    postorderIDs.push_back(node->name);
}

void AVLTree::print_preorder() {
    std::vector<std::string> preorderIDs;
    print_preorder_helper(root, preorderIDs);
    for (unsigned int i = 0; i < preorderIDs.size(); i++) {
        std::cout << preorderIDs[i];
        if (i != preorderIDs.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void AVLTree::print_preorder_helper(AVLTree::Node *node, std::vector<std::string> &preorderIDs) {
    if (node == nullptr)
        return;

    preorderIDs.push_back(node->name);

    print_preorder_helper(node->left, preorderIDs);

    print_preorder_helper(node->right, preorderIDs);
}

void AVLTree::search_name_helper(AVLTree::Node *node, const std::string& name, bool &done) {

    if (node == nullptr)
        return;

    search_name_helper(node->left, name, done);

    if (node->name == name) {
        std::cout << node->id << std::endl;
        done = true;
    }

    search_name_helper(node->right, name, done);
}

int AVLTree::max(int a, int b) {
    return (a > b)? a : b;
}

int AVLTree::get_balance(Node* node) {
    if (node == nullptr)
        return 0;

    int x = get_height(node->left);
    int y = get_height(node->right);

    return x - y;
}

AVLTree::Node *AVLTree::insert_helper(AVLTree::Node *node, const std::string &id, const std::string &name) {
    if (node == nullptr) {
        std::cout << "successful" << std::endl;
        return new Node(id, name);
    }
    else if (stoi(id) > stoi(node->id))
        node->right = insert_helper(node->right, id, name);
    else if (stoi(id) < stoi(node->id))
        node->left = insert_helper(node->left, id, name);
    else
        std::cout << "unsuccessful" << std::endl;

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);

    if (balance < -1 and stoi(id) > stoi(node->right->id)) {
        return left_rotation(node);
    }
    else if (balance < -1 and stoi(id) < stoi(node->right->id)) {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }
    else if (balance > 1 and stoi(id) < stoi(node->left->id)) {
        return right_rotation(node);
    }
    else if (balance > 1 and stoi(id) > stoi(node->left->id)) {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    return node;

}

AVLTree::Node *AVLTree::left_rotation(AVLTree::Node *node) {
    Node* temp = node->right;
    Node* branch = temp->left;

    temp->left = node;
    node->right = branch;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    temp->height = 1 + max(get_height(temp->left), get_height(temp->right));

    return temp;
}

AVLTree::Node *AVLTree::right_rotation(AVLTree::Node *node) {
    Node* temp = node->left;
    Node* branch = temp->right;

    temp->right = node;
    node->left = branch;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    temp->height = 1 + max(get_height(temp->left), get_height(temp->right));

    return temp;
}

int AVLTree::get_height(AVLTree::Node *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

AVLTree::Node *AVLTree::remove_helper(AVLTree::Node *node, const std::string &id, bool &done) {
    if (node == nullptr)
        return node;
    else if (stoi(id) > stoi(node->id))
        node->right = remove_helper(node->right, id, done);
    else if (stoi(id) < stoi(node->id))
        node->left = remove_helper(node->left, id, done);
    else {
        if (node->right == nullptr or node->left == nullptr) {
            Node* temp = (node->left != nullptr)? node->left : node->right;
            if (temp == nullptr) {
               delete node;
               node = nullptr;
                std::cout << "successful" << std::endl;
                done = true;
            }
            else {
                *node = *temp;
                delete temp;
                std::cout << "successful" << std::endl;
                done = true;
            }
        }
        else {
            Node* temp = min_value(node->right);
            node->id = temp->id;
            node->name = temp->name;
            node->right = remove_helper(node->right, temp->id, done);
        }
    }

    if (node != nullptr)
        node->height = 1 + max(get_height(node->left), get_height(node->right));

    return node;
}

AVLTree::Node *AVLTree::min_value(AVLTree::Node *subtreeRoot) {
    while (subtreeRoot->left != nullptr) {
        subtreeRoot = subtreeRoot->left;
    }
    return subtreeRoot;
}

int AVLTree::get_level_count() {
    if (root == nullptr)
        return 0;
    return root->height;
}

void AVLTree::remove_inorder_N(int n) {
    int temp = 0;
    bool done = false;
    remove_inorder_N_helper(root, temp, n, done);
    if (!done) std::cout << "unsuccessful" << std::endl;
}

AVLTree::Node *AVLTree::remove_inorder_N_helper(AVLTree::Node *node, int &n, const int &removedN, bool &done){
    if (done)
        return nullptr;
    if (node == nullptr)
        return nullptr;

    remove_inorder_N_helper(node->left, n, removedN, done);
    if (n == removedN) {
        remove(node->id);
        done = true;
    }
    n++;
    remove_inorder_N_helper(node->right, n, removedN, done);
    return nullptr;
}

#endif //AVLTREE_AVL_H

bool is_valid_id(const std::string &s) {
    if (s.size() != 8)
        return false;

    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}        //some helper functions to clean up main and validate possible ids and numbesr and such

bool is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_valid_name(const std::string &s) {
    if (s[0] != '"')
        return false;
    if (s[s.size()-1] != '"')
        return false;
    std::string temp = s.substr(1, s.size()-2);
    std::string::const_iterator it = temp.begin();
    while (it != temp.end() && (std::isalpha(*it) or std::isspace(*it) or *it == ' ')) ++it;
    return !temp.empty() && it == temp.end();
}

std::string remove_quotes(const std::string &s) {
    return s.substr(1, s.size()-2);
}

#include<iostream>
#include<queue>

using namespace std;

struct Node {
    int data;
    Node* pLeft;
    Node* pRight;
    int height;
    Node(int value) {
        data = value;
        pLeft = nullptr;
        pRight = nullptr;
        height = 1;
    }
};

int height (Node* root) {
    return root == nullptr ? 0 : root->height;
}

int balancefactor(Node* root) {
    return root == nullptr ? 0 : height(root->pLeft) - height(root->pRight);
}

Node* rightRotate(Node* root) {
    Node* newRoot = root->pLeft;
    root->pLeft = newRoot->pRight;
    newRoot->pRight = root;
    root->height = max(height(root->pLeft), height(root->pRight));
    newRoot->height = 1 + max(height(newRoot->pLeft), height(newRoot->pRight));
    return newRoot;
}

Node* leftRotate(Node* root){
    Node* newRoot = root->pRight;
    root->pRight = newRoot->pLeft;
    newRoot->pLeft = root;
    root->height = 1 + max(height(root->pLeft), height(root->pRight));
    newRoot->height = 1 + max(height(newRoot->pLeft), height(newRoot->pRight));
    return newRoot;
}

Node* BalanceAVLTree(Node* root){
    int balance = balancefactor(root);
    if(balance > 1 && balancefactor(root->pLeft) >= 0) {
        return rightRotate(root);
    } 
    if(balance > 1 && balancefactor(root->pLeft) < 0) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }
    if(balance< -1 && balancefactor(root->pRight) <= 0) {
        return leftRotate(root);
    }
    if(balance < -1 && balancefactor(root->pRight) > 0) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }
    root->height = 1 + max(height(root->pLeft), height(root->pRight));
    return root;
}

Node *insert(Node* root, int value) {
    if(root == nullptr) {
        root = new Node{value};
        return root;
    }

    if(root->data > value) {
        root->pLeft = insert(root->pLeft, value);
    } else if(root->data < value) {
        root->pRight = insert(root->pRight, value);
    } else {
        return root;
    }
    root->height = 1 + max(height(root->pLeft), height(root->pRight));
    return BalanceAVLTree(root);
}

void Inorder(Node* root){
    if(root != nullptr) { 
        Inorder(root->pLeft);
        cout << root->data << " ";
        Inorder(root->pRight); 
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 25);
    root = insert(root, 5);
    Inorder(root);
}
#include<iostream>
#include<queue>
#include<stack>

using namespace std;

struct Node{
    int value;
    Node* pLeft;
    Node* pRight;
    int height;
    Node(int data){
        this->value = data;
        pLeft = pRight = nullptr;
        height = 1;
    }
};

int height(Node* pRoot) {
    return pRoot == nullptr ? 0 : pRoot->height;
}

int balanceFactor(Node* pRoot) {
    return pRoot == nullptr ? 0 : height(pRoot->pLeft) - height(pRoot->pRight);
}

Node* rightRotate(Node* pRoot) {
    Node* newRoot = pRoot->pLeft;
    pRoot->pLeft = newRoot->pRight;
    newRoot->pRight = pRoot;
    pRoot->height = 1 + max(height(pRoot->pRight), height(pRoot->pLeft));
    newRoot->height = 1 + max(height(newRoot->pRight), height(newRoot->pLeft));
    return newRoot;
}

Node* leftRotate(Node* pRoot) {
    Node* newRoot = pRoot-> pRight;
    pRoot->pRight = newRoot->pLeft;
    newRoot->pLeft = pRoot;
    pRoot->height = 1 + max(height(pRoot->pRight), height(pRoot->pLeft));
    newRoot->height = 1 + max(height(newRoot->pRight), height(newRoot->pLeft));
    return newRoot;
}

Node* BalanceAVLTree(Node* root){
    
    if(root == nullptr) return root;

    int bl = balanceFactor(root);
    root->height = 1 + max(height(root->pLeft), height(root->pRight));
    if(bl > 1 && balanceFactor(root->pLeft) >= 0) {
        return rightRotate(root);
    }
    if(bl > 1 && balanceFactor(root->pLeft) < 0) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }
    if(bl < -1 && balanceFactor(root->pRight) <= 0) {
        return leftRotate(root);
    }
    if(bl < -1 && balanceFactor(root->pRight) > 0) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }
    root->height = 1 +  max(height(root->pRight), height(root->pLeft));
    return root;
}

Node* insert(Node* root, int value) {
    if(root == nullptr) return new Node(value);
    if(root->value > value){
        root->pLeft = insert(root->pLeft, value);
    } else if(root->value < value) {
        root->pRight = insert(root->pRight, value);
    } else {
        return root;
    }
    return BalanceAVLTree(root);
}


int main() {

}
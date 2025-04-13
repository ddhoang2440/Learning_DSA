#include <iostream>
#include<queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) {
        this->data = value; // Sửa lỗi gán
        left = right = nullptr;
    }
};

Node* insert(Node* root, int value);
bool search(Node* root, int key);
Node* findMin(Node* root);
Node* removeNode(Node* root, int value);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void LevelOrder(Node* root);

int main() {
    Node* root = nullptr;
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 0);
    root = insert(root, 2);
    root = insert(root, 5);

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout << "\nXóa nút 2:\n";
    root = removeNode(root, 2);
    inorder(root);
    cout << endl;

    return 0;
}

// Hàm chèn nút vào BST
Node* insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);

    if (root->data > value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Hàm tìm kiếm giá trị trong BST
bool search(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (root->data > key)
        return search(root->left, key);
    return search(root->right, key);
}

// Hàm tìm giá trị nhỏ nhất trong BST
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Hàm xóa một nút trong BST
Node* removeNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (root->data > value) {
        root->left = removeNode(root->left, value);
    } else if (root->data < value) {
        root->right = removeNode(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

// Duyệt theo thứ tự trái - gốc - phải (Inorder)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Duyệt theo thứ tự gốc - trái - phải (Preorder)
void preorder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Duyệt theo thứ tự trái - phải - gốc (Postorder)
void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

int CountNode(Node* root){
    if(root == nullptr) return 0;

    int left = CountNode(root->left);
    int right = CountNode(root->right); 

    return 1 + left + right;
}

int Height(Node* root) {
    if(root == nullptr) return 0;

    int left = Height(root->left);
    int right = Height(root->right);

    return 1 + max(left, right);
}

void LevelofOrder(Node* root) {
    if(root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->data;
        if(root->left) q.push(root->left);
        if(root->right) q.push(root->right);
    }
}

Node* CreateTree(int a[], int n){
    if(n == 0) return nullptr;
    Node* root = new Node{a[0]};
    for(int i = 0; i < n; i++) {
        Node* temp = root;
        while(true){
            if(a[i] < temp->data) {
                if(temp->left == nullptr){
                    temp->left = new Node{a[i]};
                    break;
                } else temp = temp->left;
            } else{
                if(temp->right == nullptr) {
                    temp->right = new Node{a[i]};
                    break;
                } else temp = temp->right;
            }
        }
    }
    return root;
}

int Level(Node* root, Node* p, int level = 0) {
    if(root == nullptr) return -1;

    if(root == p) return level;

    int left = Level(root->left, p, level + 1);
    if(left != -1) return level;

    return Level(root-> right, p, level + 1);
}

int CountLeaf(Node* root){
    if(root == nullptr) return 0;
    if(root->left == nullptr && root->right == nullptr) return 1;
    return CountLeaf(root->left) + CountLeaf(root->right);
}

int CountLess(Node* root, int x){
    if(root == nullptr) return 0;

    return (root->data < x ? 1 : 0) + CountLess(root->left, x) + CountLess(root->right, x);
}

int CountGreater(Node* root, int x) {
    if(root == nullptr) return 0;

    return (root->data > x ? 1 : 0) + CountGreater(root->left, x) + CountGreater(root->right, x);
}

bool IsBST(Node* root, Node* minNode = nullptr, Node* maxNode = nullptr){
    if(root == nullptr) return 1;
    if((minNode != nullptr && minNode->data >= root->data) || (maxNode != nullptr && maxNode->data <= root->data)) return -1;

    return IsBST(root->left, minNode, root) && IsBST(root->right, root, maxNode);
}

bool IsFullBST(Node* root) {
    if (!root) return true;
    if ((!root->left && root->right) || (root->left && !root->right))
        return false;
    return IsFullBST(root->left) && IsFullBST(root->right);
}
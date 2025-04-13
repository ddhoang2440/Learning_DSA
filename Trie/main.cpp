#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_NUMS = 26;

struct TrieNode{
    bool isEndWord;
    TrieNode* children[ALPHABET_NUMS];
    TrieNode() { // Constructor
        isEndWord = 0;
        for(int i = 0 ; i < ALPHABET_NUMS; i++) {
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode * root, string s){
    TrieNode *node = root;

    for (int i = 0; i < s.length(); i++){
        int idx = s[i] - 'a';
        if(!node->children[idx]){
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }
    node->isEndWord = true;
}

void deleteSubtree(TrieNode* &pNode) {
    if (pNode == nullptr)
        return;
    
    for (int i = 0; i < ALPHABET_NUMS; ++i)
        if (pNode->children[i] != nullptr)
            deleteSubtree(pNode->children[i]);
        
    delete pNode;
    pNode = nullptr;
}

void removeWord(TrieNode* pRoot, string s) {
    if (s.empty())
        return;

    TrieNode* pCur = pRoot;
    TrieNode* pLast = nullptr;
    char lastChar = 'a';

    
    for (auto c : s) {
        if (pCur->children[c - 'a'] == nullptr)
            return;
        
        int childCount = 0;
        for (int i = 0; i < ALPHABET_NUMS; ++i) 
            if (pCur->children[i] != nullptr)
                childCount++;
        
        if (childCount > 1) {
            pLast = pCur;
            lastChar = c;
        }

        pCur = pCur->children[c - 'a'];
    }

    if (!pCur->isEndWord)
        return;
    
    int childCount = 0;
    for (int i = 0; i < ALPHABET_NUMS; ++i) 
        if (pCur->children[i] != nullptr)
            childCount++;

    if (childCount > 0) {
        pCur->isEndWord = false;
        return;
    }

    if (pLast != nullptr)
        deleteSubtree(pLast->children[lastChar - 'a']);
    else 
        deleteSubtree(pRoot->children[s[0] - 'a']);
}

TrieNode *searchWord(TrieNode *&pRoot, string word)
{
    TrieNode* node = pRoot;
    for (char c : word) {
        if (!node->children[c - 'a']) 
            return nullptr;
        node = node->children[c - 'a'];
    }
    return node->isEndWord ? node : nullptr;
}

/*------------Hàm thu thập các từ có chung tiền tố và in ra màn hình------------------*/
void CollectKeysWithPrefix(TrieNode* p, string prefix) {
    if(p == nullptr) return;

    if(p->isEndWord) {
        cout << prefix << endl;
    }

    for(int i = 0; i < ALPHABET_NUMS; i++) {
        if (p->children[i]) {
            prefix.push_back(char(i + 'a'));  // Thêm ký tự vào prefix
            CollectKeysWithPrefix(p->children[i], prefix);
            prefix.pop_back();  // Xóa ký tự khi quay lui
        }
    }
}
/*-------------------Hàm tìm kiếm node cuối cùng của tiền tố ----------------------*/
TrieNode *Get(TrieNode *p, string key) {
    for (char c : key) {
        if (!p || !p->children[c - 'a']) return nullptr;
        p = p->children[c - 'a'];
    }
    return p;
}

/*-----------------Hàm chính để tìm các key có chung tiền tố--------------------*/
void keysWithPrefix(TrieNode *pRoot, string prefix) {
    TrieNode* p = Get(pRoot, prefix);
    if (!p) return;
    CollectKeysWithPrefix(p, prefix);
}

void buildTrieFromFile(TrieNode* pRoot, const string& fileName) {
    ifstream fin(fileName);
    if (!fin.is_open())
        return;
    
    string temp;
    while (getline(fin, temp)) {
        if (!temp.empty())
            insert(pRoot, temp);
    }
    fin.close();
}

vector<string> generateCandidates(string word) {
    vector<string> candidates;

    // Xóa một ký tự (deletion)
    for (int i = 0; i < word.length(); i++) {
        string newWord = word.substr(0, i) + word.substr(i + 1);
        candidates.push_back(newWord);
    }

    // Thêm một ký tự (insertion)
    for (int i = 0; i <= word.length(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string newWord = word.substr(0, i) + c + word.substr(i);
            candidates.push_back(newWord);
        }
    }

    // Thay thế một ký tự (substitution)
    for (int i = 0; i < word.length(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (c != word[i]) { // Tránh thay thế chính nó
                string newWord = word;
                newWord[i] = c;
                candidates.push_back(newWord);
            }
        }
    }

    return candidates;
}

void spellCheck(TrieNode* root, string word) {
    if (searchWord(root, word)) {
        cout << "CORRECT" << endl;
        return;
    }

    vector<string> candidates = generateCandidates(word);
    vector<string> suggestions;

    for (string candidate : candidates) {
        if (searchWord(root, candidate)) {
            suggestions.push_back(candidate);
        }
    }

    // In kết quả
    cout << suggestions.size() << endl;
    for (string suggestion : suggestions) {
        cout << suggestion << endl;
    }
}

int main() {
    TrieNode* pRoot = new TrieNode();
    
    buildTrieFromFile(pRoot, "Dic.txt");

    string inputWord;
    cout << "Nhập từ cần check: ";
    cin >> inputWord;
    spellCheck(pRoot, inputWord);
}
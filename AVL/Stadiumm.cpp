#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<sstream>
#include<stack>
#include<queue>

using namespace std;

struct RecordAttendance {
unsigned int attend; //attendance
string home; //home team
string away; //away team
unsigned int year;
};

struct Stadium {
string name;
unsigned int cap; //capacity
string city;
string clubs;
vector<int> renos; //renovations
RecordAttendance record; // default = "0 ( - , 0)"
string address;
};

struct NODE{
    Stadium stadium;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

// Read File
vector<int> processReno(string input){
    stringstream ss(input);
    string p;
    vector<int> renos;
    while(getline(ss, p, ',')) {
        renos.push_back(stoi(p));
    }
    return renos;
}

void processRecord(string input, RecordAttendance &p) {
    if (input.empty()) {
        p.attend = 0;
        p.home = " ";
        p.away = " ";
        p.year = 0;
        return;
    }
    string s;
    stringstream ss(input);
    getline(ss, s, '(');
    p.attend = stoi(s);
    getline(ss, p.home, '-');
    getline(ss, p.away, ',');
    getline(ss, s, ')');
    p.year = stoi(s);
    return;
}

vector<Stadium> readfile(string filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cout << "Can't open file " << filename << endl;
        return {};
    }
    vector<Stadium> stadiums;
    string line;
    getline(file, line);
    Stadium s;
    while(getline(file, line)) {
        stringstream ss(line);
        string p;
        getline(ss, s.name, ';');
        getline(ss, p, ';');
        s.cap = stoi(p);
        getline(ss, s.city, ';');
        getline(ss, s.clubs, ';');
        getline(ss, p, ';');
        s.renos = processReno(p);
        getline(ss, p, ';');
        processRecord(p, s.record);
        getline(ss, s.address, ';');
        stadiums.push_back(s);
    }
    return stadiums;
}

// Build AVL
int height(NODE* pRoot){
    return pRoot == nullptr ? 0 : pRoot->height;
}

int balancefactor(NODE* pRoot) {
    return pRoot == nullptr ? 0 : height(pRoot->pLeft) - height(pRoot->pRight);
}

NODE* rightRotate(NODE* pRoot){
    NODE* newRoot = pRoot->pLeft;
    pRoot->pLeft = newRoot->pRight;
    newRoot->pRight = pRoot;
    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    newRoot->height = 1 + max(height(newRoot->pLeft), height(newRoot->pRight));
    return newRoot;
}

NODE* leftRotate(NODE* pRoot){
    NODE* newRoot = pRoot->pRight;
    pRoot->pRight = newRoot->pLeft;
    newRoot->pLeft = pRoot;
    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    newRoot->height = 1 + max(height(newRoot->pLeft), height(newRoot->pRight));
    return newRoot;
}

NODE* balanceAVLTree(NODE* pRoot){
    if(pRoot == nullptr) return pRoot;
    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    int b = balancefactor(pRoot);
    if(b > 1 && balancefactor(pRoot->pLeft) >= 0){
        return rightRotate(pRoot);
    }
    if(b > 1 && balancefactor(pRoot->pLeft) < 0) {
        pRoot->pLeft = leftRotate(pRoot->pLeft);
        return rightRotate(pRoot);
    }
    if(b < -1 && balancefactor(pRoot->pRight) <= 0){
        return leftRotate(pRoot);
    }
    if(b < -1 && balancefactor(pRoot->pRight) > 0) {
        pRoot->pRight = rightRotate(pRoot->pRight);
        return leftRotate(pRoot);
    }
    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    return pRoot;
}

// Insert list of stadiums
int cmp(Stadium a, Stadium b){
    if(a.cap != b.cap) return a.cap < b.cap ? - 1 : 1;
    if(a.record.attend != b.record.attend) return a.record.attend > b.record.attend ? -1 : 1;
    return a.name < b.name ? -1 : 1;
    return 0;
}

NODE* insert(NODE*& pRoot, Stadium p) {
    if(cmp(p, pRoot->stadium) < 0){
        pRoot->pLeft = insert(pRoot->pLeft, p);
    } else if(cmp(p, pRoot->stadium) > 0) {
        pRoot->pRight = insert(pRoot->pRight, p);
    } else {
        return pRoot;
    }
    return balanceAVLTree(pRoot);
}

NODE* question1_1(vector<Stadium> stadiums){
    NODE* p = new NODE{stadiums[0], nullptr, nullptr, 1};
    for(int i = 1 ; i < stadiums.size(); i++) {
        p = insert(p, stadiums[i]);
    }
    return p;
}

// Delete all stadium by city
NODE *findMin(NODE* root) {
    while(root->pLeft != nullptr) {
        root = root->pLeft;
    }
    return root;
}

void question1_2(NODE*& pRoot, string city) {
    if(pRoot == nullptr) return;

    question1_2(pRoot->pLeft, city);
    question1_2(pRoot->pRight, city);

    if(pRoot->stadium.city == city) {
        if(pRoot->pLeft == nullptr && pRoot->pRight == nullptr) {
            delete pRoot;
            pRoot = nullptr;
        }
        else if(pRoot->pLeft == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->pRight;
            delete temp;
        } else if(pRoot->pRight == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->pLeft;
            delete temp;
        } else {
            NODE* temp = findMin(pRoot->pRight);
            pRoot->stadium = temp->stadium;
            question1_2(pRoot->pRight, temp->stadium.city);
        }
    }
    pRoot = balanceAVLTree(pRoot);
}

// Create Adj Matrix with some condition
int find(vector<string> names, string name)  {
    for(int i = 0; i < names.size(); i++) {
        if(names[i] == name) return i;        
    }
    return -1;
}

int SameRenovations(vector<int> a, vector<int> b) {
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b.size(); j++) {
            if(a[i] == b[j]) return 1;
        }
    }
    return 0;
}

vector<vector<int>> question2_1(vector<Stadium> stadiums, vector<string>& names) {
    /*Bước 1: Thu thập các names*/
    for(Stadium s : stadiums) {
        if(find(names, s.name) == -1){
            names.push_back(s.name);
        }
    }
    
    int n = stadiums.size();
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for(int i = 0; i < stadiums.size(); i++) {
        for(int j = i + 1; j < stadiums.size(); j++) {
            if(SameRenovations(stadiums[i].renos, stadiums[j].renos)){
                int u = find(names, stadiums[i].name); 
                int v = find(names, stadiums[j].name);
                if(u != -1 && v != -1) {
                    matrix[u][v] = matrix[v][u] = 1;
                }
            }
        }
    }
    return matrix;
}

/*Implement vector<string> question2_2(vector<string> names, vector<vector<int>> graph); to return the stadium(s)
 with the most connections (i.e., highest degree in the renovation graph). Return all stadiums tied for the top.*/

vector<string> question2_2(vector<string> names, vector<vector<int>> graph) {
    vector<string> res;
    int v = graph.size();
    int max = -1;
    vector<int> degree(v, 0);
    for(int i = 0 ; i < v; i++) {
        for(int j = 0; j < v; j++) {
            degree[i] += graph[i][j];
        }
        if(max < degree[i]) {
            max = degree[i];
        }
    }
    
    for(int i = 0; i < v; i++) {
        if(degree[i] == max){
            res.push_back(names[i]);
        }
    }
    return res;
}

//Description:
// Return true if the given stadium has any connection (degree > 0), otherwise return false.
bool question2_3(vector<string> names, vector<vector<int>> graph, string stadium_name){
    int v = graph.size();
    int m = find(names, stadium_name);
    if(m != -1) {
        for(int i = 0; i < v; i++) {
            if(graph[i][m] > 0) return true;
        }
    }
    return false;
}


//Return the total number of connected components in the graph. Use BFS or DFS for implementation.
int question2_4(vector<vector<int>> graph){
    int v = graph.size();
    vector<bool> isVisited(v, false);
    queue<int> q;
    int count = 0;
    for(int i = 0; i < v; i++) {
        if(isVisited[i] == false) {
            isVisited[i] = true;
            count++;
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int j = 0 ; j < v; j++) {
                    if(!isVisited[j] && graph[u][j] > 0){
                        isVisited[j] = true;
                        q.push(j);
                    }
                }
            }
        }
    }
    return count;
}

//Description:
// Return the list of isolated stadiums (i.e., stadiums with degree 0, no connections to others).
vector<string> question2_5(vector<string> names , vector<vector<int>> graph){
    int v = graph.size();
    vector<string> isolated;
    for(int i = 0; i < v; i++){
        bool flag = false;
        for(int j = 0; j < v; j++) {
            if(graph[i][j] > 0) {
                flag = true;
                break;
            }
        }
        if(!flag) {
            isolated.push_back(names[i]);
        }
    }
    return isolated;
}

//Return true if the graph is fully connected (i.e., all stadiums are in the same component), otherwise return false.
bool question2_6(vector<vector<int>> graph) {
    int v = graph.size();
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            if(i != j && graph[i][j] == 0) return false;
        }
    }
    return true;
}

// Description:
// Group and return the connected components in the graph. Each group contains stadium names that are connected.
vector<vector<string>> question2_8(vector<string> names, vector<vector<int>> graph) {
    int sz = names.size();
    vector<vector<string>>connectedGroup;
    int v = graph.size();
    vector<bool> isVisited(v, false);
    for(int i = 0; i < v; i++) {
        if(!isVisited[i]){
            vector<string> group;
            queue<int> q;
            isVisited[i] = true;
            q.push(i);
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                group.push_back(names[u]);
                for(int j = 0; j < v; j++) {
                    if(!isVisited[j] && graph[i][j] > 0) {
                        isVisited[j] = true;
                        q.push(j);
                        group.push_back(names[j]);
                    }
                }
            }
        connectedGroup.push_back(group);
        }
    }
    return connectedGroup;
}

//Description:
// Return the number of edges in the graph (count of connections, undirected, so avoid double counting).
int question2_9(vector<vector<int>> graph){
    int v = graph.size();
    int count = 0;
    // Just count 1/2 of square
    for(int i = 0 ; i < v; i++) {
        for(int j = i + 1; j < v; j++) {
            count += graph[i][j];
        }
    }
    return count;
}

//Description:
// Return all stadiums that are connected to at least 2 other stadiums (degree ≥ 2).
vector<string> question2_10(vector<string> names, vector<vector<int>> graph) {
    vector<string> res;
    int v = graph.size();
    for(int i = 0; i < v; i++) {
        int degree = 0;
        for(int j = 0; j < v; j++) {
            if(graph[i][j] > 0) {
                degree++;
            }
            if(degree >= 2) {
                res.push_back(names[i]);
                break;
            }
        }
    }
    return res;
}

// Description:
// Return the number of isolated groups that contain exactly two stadiums
// (i.e., connected components with exactly two nodes and one edge between them).
int question2_11(vector<vector<int>> graph) {
    int v = graph.size();
    vector<bool> isVisited(v, false);
    int count = 0;
    for(int i = 0; i < v; i++) {
        if(!isVisited[i]) {
            isVisited[i] = true;
            queue<int> q;
            vector<int> component;
            q.push(i);
            while(!q.empty()) {
                int u = q.front();
                component.push_back(u); //Save the order
                for(int j = 0; j < v; j++) {
                    if(!isVisited[j] && graph[u][j]){
                        isVisited[j] = true;
                        q.push(j);
                    }
                }
            }
            if(component.size() == 2) {
                int m = component[0];
                int n = component[1];
                if (graph[m][n] > 0) count++;
            }
        }
    }
    return count;
}

//Description:
//Return all stadiums that form a complete subgraph (clique of size ≥ 3), where each stadium in the group is connected to every other.
vector<string> question2_12(vector<string> names, vector<vector<int>> graph) {
    int v = graph.size();
    vector<string> res;

    for(int i = 0; i < v; i++) {
        for(int j = i + 1; j < v; j++) {
            for(int k = j + 1; k < v; k++) {
                if(graph[i][j] && graph[i][k] && graph[j][k] 
                    && graph[j][i] && graph[k][i] && graph[i][k]){
                        if(find(res, names[i]) == -1) res.push_back(names[i]);
                        if(find(res, names[j]) == -1) res.push_back(names[j]);
                        if(find(res, names[k]) == -1) res.push_back(names[k]);
                    }
            }
        }
    }
    return res;
}
/**------Updrade version-------**/
vector<vector<string>> question2_12_cliques(vector<string> names, vector<vector<int>> graph) {
    vector<vector<string>> result;
    int v = graph.size();
    for(int i = 0; i < v; i++) {
        for(int j = i + 1; j < v; j++) {
            for(int k = j + 1; k < v; j++) {
                if(graph[i][k] && graph[j][k]) {
                    vector<string> group = {names[i], names[j], names[k]};
                    result.push_back(group);
                    for(int l = 0; l < v; l++) {
                        if(l != i && l != j && l != k && graph[l][i] && graph[l][j] && graph[l][k]){
                            group.push_back(names[l]);
                        }
                    }
                    result.back() = group;
                }
            }
        }
    }
    return result;
}


// Description:
// Return true if there is a path (direct or indirect) between stadiumA and stadiumB.
bool question2_13(vector<string> names, vector<vector<int>> graph, string stadiumA, string stadiumB) {
    int u = find(names, stadiumA);
    int k = find(names, stadiumB);
    if(u == -1 || k == -1) return false;

    int v = graph.size();
    queue<int> q;
    vector<bool> isVisited(v, false);
    isVisited[u] = true;
    q.push(u);
    while (!q.empty()) {
        int m = q.front();
        q.pop();
        for(int i = 0; i < v; i++) {
            if(!isVisited[i] && graph[m][i] > 0){
                isVisited[i] = true;
                q.push(i);
            }
        } 
    }
    return isVisited[k];
}

// Description:
// Return all bridges in the graph (edges that, if removed, increase the number of components), formatted as pairs of stadium names
bool HasPath(vector<vector<int>> graph, int u, int k) {
    int v = graph.size();
    queue<int> q;
    vector<bool> isVisited(v, false);
    isVisited[u] = true;
    q.push(u);
    while (!q.empty()) {
        int m = q.front();
        q.pop();
        for(int i = 0; i < v; i++) {
            if(!isVisited[i] && graph[m][i] > 0){
                isVisited[i] = true;
                q.push(i);
            }
        } 
    }
    return isVisited[k];
}

vector<vector<string>> question2_14(vector<string> names, vector<vector<int>> graph) {
    int v = graph.size();
    vector<vector<string>> res;
    for(int i = 0; i < v; i++) {
        for(int j = i + 1; j < v; j++) {
            if(graph[i][j] == 0) continue;
            
            graph[i][j] = 0;
            graph[j][i] = 0;
            if(HasPath(graph, i, j)) {
                vector<string> p = {names[i], names[j]};
                res.push_back(p);
            }
            graph[i][j] = 1;
            graph[j][i] = 1;
        }
    }
    return res;
}



// Description:
// Check whether the graph is connected, i.e., all stadiums are part of one big component.
bool question2_15(vector<vector<int>> graph) {
    int v = graph.size();
    vector<bool> isVisisted(v, false);
    queue<int> q;
    isVisisted[0] = true;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < v; i++) {
            if(!isVisisted[i] && graph[u][i] > 0) {
                isVisisted[i] = true;
                q.push(i);
            }
        }
    }
    for(bool c : isVisisted) {
        if(!isVisisted[c]) return false;
    }
    return true;
}

// Description:
// Return all leaf stadiums (stadiums with degree = 1), returned as pairs: (leaf, its neighbor).
vector<vector<string>> question2_16(vector<string> names, vector<vector<int>> graph){
    int v = graph.size();
    vector<vector<string>> res;
    for(int i = 0; i < v; i++) {
        int d = 0, n = -1;
        for(int j = 0; j < v; j++) {
            if(graph[i][j]) {
                d++;
                n = j;
            }
        }
        if(d == 1) {
            res.push_back({names[i], names[n]});
        }
    }
    return res;
}

// Description:
// Trả về bậc lớn nhất trong đồ thị, tức là số lượng kết nối nhiều nhất của một sân vận động.
int question2_17(vector<vector<int>> graph) {
    int v = graph.size();
    int maxDegree = -1;
    for(int i = 0; i < v; i++) {
        int tempDegree = 0;
        for(int j = 0; j < v; j++) {
            if(graph[i][j] > 0) {
                tempDegree++;
            }
        }
        if(tempDegree > maxDegree) maxDegree = tempDegree;
    }
    return maxDegree;
}

// Description:
// Return stadiums that are not bridges, i.e., removing them will not break their component into more pieces.
int countComponents(vector<vector<int>> graph, int skip = -1) {
    int v = graph.size();
    vector<bool> isVisited(v, false);
    int count = 0;
    for(int i = 0; i < v; i++) {
        if(i == skip || isVisited[i]) continue;
        
        queue<int> q;
        count++;
        isVisited[i] = true;
        q.push(i);
        for(int j = 0; j < v; j++) {
            if(!isVisited[j] && graph[i][j] && j != skip) {
                isVisited[j] = true;
                q.push(j);
            }
        }
    }
    return count;
}

vector<string> question2_18(vector<string> names, vector<vector<int>> graph) {
    int v = graph.size();
    vector<string> res;
    int baseComponents = countComponents(graph);
    for(int i = 0; i < v; i++) {
        int newComponents = countComponents(graph, i);
        if(newComponents == baseComponents) {
            res.push_back(names[i]);
        } 
    }
    return res;
}

// Description:
// Return all central stadiums: stadiums that lie on at least one shortest path between two other stadiums (using BFS).
// vector<string> question2_19(vector<string> names, vector<vector<int>> graph)
vector<int> bfsshortespath(int src, vector<vector<int>> graph) {
    int v = graph.size();
    vector<int> dist(v, -1);
    queue<int> q;
    q.push(v);
    dist[src] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0; i < v; i++) {
            if(graph[u][i] && dist[i] == -1){
                dist[i] = dist[u] + 1;
                q.push(i);
            }
        }
    }
    return dist;
}

vector<string> question2_19(vector<string> names, vector<vector<int>> graph){
    int v = graph.size();
    vector<bool> isCentral(v, false);

    for(int i = 0; i < v; i++) {
        vector<int> DistFromI = bfsshortespath(i, graph);
        for(int j = 0; j < v; j++) {
            if(i == j || DistFromI[j] == -1) continue;
            int shortest = DistFromI[j];
            vector<int> DistFromJ = bfsshortespath(j, graph);
            for(int k = 0; k < v; k++) {
                if(k != i && k != j && DistFromI[k] != -1
                 && DistFromJ[k] != -1 && DistFromI[k] + DistFromJ[k] == shortest) {
                    isCentral[k] = true;
                 }
            }
        }
    }
    vector<string> res;
    for(int i = 0; i < v; i++) {
        if(isCentral[i]) {
            res.push_back(names[i]);
        }
    }
    return res;
}

int main() {
    vector<Stadium> stadiums = readfile("stadium.csv");
    vector<string> names;
    vector<vector<int>> res = question2_1(stadiums, names);
    // for(string s : names) {
    //     cout << s << endl;
    // }

    int v = res.size();
    vector<string> temp = question2_12(names, res);
    for(string c : temp) {
        cout << c << endl;
    }
}
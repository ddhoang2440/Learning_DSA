#include<iostream>
#include<vector>
#include<sstream>
#include<cstring>
#include<string>
#include<queue>
#include<fstream>

using namespace std;
/*Question 1*/
vector<vector<int>> readAdjMatrix(string filename){
    ifstream file(filename);

    int n;
    file >> n;
    vector<vector<int>> matrix(n, vector<int> (n));
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n; j++) {
            file >> matrix[i][j];         
        }
    }
    file.close();
    return matrix;
}

vector<vector<int>> adjMatrixtoList(const vector<vector<int>>& matrix) {
    int n = matrix.size();

    vector<vector<int>> adjList(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

void PrintListAdj(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for(int i = 0 ; i < n; i++){
        for(int j : matrix[i]) {
        cout << j << " ";
        }
        cout << endl;
    }
}

/*Question2*/
vector<vector<int>> readAdjList(string filename){
    ifstream file(filename);
    if (!file) {
        cout << "Can't open file " << filename << endl;
        return {}; 
    }

    int n;
    file >> n;
    file.ignore(); // Bỏ qua ký tự xuống dòng sau số đỉnh

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    string line;
    for (int i = 0; i < n; i++) {
        if (getline(file, line)) {  // Kiểm tra xem có đọc được dòng không
            stringstream ss(line);
            int neighbour;
            while (ss >> neighbour) {
                matrix[i][neighbour] = 1;
            }
        }
    }
    return matrix;
}

void PrintAdjMatrix(const vector<vector<int>> &matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

bool isDirected(const vector<vector<int>>& matrix){
    int n = matrix.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] != matrix[j][i]){
                return true;
            }
        }
    }
    return false;
}

int countEdges(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            if(matrix[i][j] == 1) {
                count++;
            }
        }
    }

    return isDirected(matrix)? count : count / 2;
}

vector<int> VertexDegrees(const vector<vector<int>>& matrix){
    int n = matrix.size();
    vector<int> degrees(n, 0);
    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 1){
                degrees[i]++;
            }
        }
    }
    return degrees;
}

bool isCompleteGraph(const vector<vector<int>> &matrix){
    int n = matrix.size();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j && matrix[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

int connectedComponents(const vector<vector<int>> &adjlist) {
    int n = adjlist.size(), count = 0;
    vector<bool> visited(n, false);
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(visited[i] == false) {
            q.push(i);
            visited[i] = true;
            count++;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(int v : adjlist[u]) {
                    if(visited[v] == false){
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    return count;
}


vector<int> shortestPathBFS(const vector<vector<int>>& adj, int start) {
    int V = adj.size();

    vector<int> distance(V, -1);
    queue<int>q;
    distance[start] = 0;
    q.push(start);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v = 0; v < V; v++) {
            if(adj[u][v] != 0 && distance[v] == -1){
                distance[v] = 1 + distance[u];
            }
        }
    }

    return distance;
}



int main() {
    vector<vector<int>> res = readAdjMatrix("Graph1.txt");

    vector<int> path = shortestPathBFS(res, 0);

    for(int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
}
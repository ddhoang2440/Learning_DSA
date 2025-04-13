#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<fstream>
using namespace std;
/*{source,destination,[name of airliner,number of business seats,number of economy seats,hours,minutes]}
{"Myanmar,South Sudan": ["Comac ARJ-900/C909-200 90", "11 business, 84 economy", "9 hours, 25 minutes"]}
{"Faeroe Islands,Ethiopia": ["Comac C919", "92 business, 98 economy", "9 hours, 16 minutes"]}
{"Italy,Greece": ["Bombardier C-110 100", "8 business, 117 economy", "1 hour, 36 minutes"]}
{"Netherlands,Tunisia": ["Antonov 24", "21 business, 31 economy", "3 hours, 4 minutes"]}
*/
struct Attendance{
    string source;
    string destination;
    string airliner;
    int business;
    int economy;
    int hours;
    int minutes;
};

struct Node{
    Attendance data;
    Node* pLeft;
    Node* pRight;
};


vector<string> Split(string input, char delim) {
    vector<string> res;
    string temp = "";

    for(char c : input) {
        if(c == delim) {
            res.push_back(temp);
            temp.clear();
        } else {
            temp += c;
        }
    }
    res.push_back(temp);
    return res;
}
//{"Myanmar,South Sudan": ["Comac ARJ-900/C909-200 90", "11 business, 84 economy", "9 hours, 25 minutes"]}

int Convert(string input){
    string temp = "";
    for(char c : input){
        if(isdigit(c)){
            temp += c;
        }
    }
    return stoi(temp);
}

Attendance ParseLine(string input) {
    Attendance res;
    if(input.empty()) return res;
    int delim1 = 0, delim2 = input.find(':'), delim3 = input.find('['), delim4 = input.find(']'), delim5 = 0;
    for(int i = 0; i < input.size(); i++) {
        if(input[i] == ',') {
            delim1 = i;
            break;
        }
    }
    res.source = input.substr(2, delim1 - 2);
    res.destination = input.substr(delim1 + 1, delim2 - 2 - (delim1 + 1) + 1);

    for(int i = delim3; i < delim4; i++) {
        if(input[i] == ','){
            delim5 = i;
            break;
        }
    }

    string temp = input.substr(delim3, delim4 - delim3 + 1);
    vector<string> splitline = Split(temp, ',');
    if(splitline.size() == 4) {
        res.airliner = splitline[0].substr(2, delim5 - 2 - (delim3 + 2) + 1);
        res.business = Convert(splitline[1]);
        res.economy = Convert(splitline[2]);
        res.minutes = Convert(splitline[3]);
        res.hours = 0;

    } else if(splitline.size() == 5) {
        res.airliner = splitline[0].substr(2, delim5 - 2 - (delim3 + 2) + 1);
        res.business = Convert(splitline[1]);
        res.economy = Convert(splitline[2]);
        res.hours = Convert(splitline[3]);
        res.minutes = Convert(splitline[4]);
    }
    return res;
}

vector<Attendance> ReadFile(string filename) {
    vector<Attendance> res;
    fstream file(filename, ios::in);
    if(!file.is_open()){
        cout << "Can't open File";
        return res;
    }
    string skipline;
    getline(file, skipline);
    string line;
    while(getline(file, line)) {
        Attendance temp = ParseLine(line);
        if(temp.source != "") {
            res.push_back(temp);
        }
    }
    file.close();
    return res;
} 

void PrintList(Node* root){
    if(root == nullptr) return;
    PrintList(root->pLeft);
    cout << root->data.source << " " << root->data.destination << " "
    << root->data.airliner << " " << root->data.business << " "
    << root->data.economy << " " << root->data.hours << " "<< root->data.minutes << endl;
    PrintList(root->pRight);
}

void printLevel(Node* root, int level) {
    if(root == nullptr) return;
    if(level == 0) {
        cout << root->data.source << " " << root->data.destination << " "
        << root->data.airliner << " " << root->data.business << " "
        << root->data.economy << " " << root->data.hours << " "<< root->data.minutes << endl;
        return;
    }

    printLevel(root->pLeft, level - 1);
    printLevel(root->pRight, level - 1);

}


Node* Insert(Node *&pRoot, Attendance p) {
    if(pRoot == nullptr) {
        pRoot = new Node{p, nullptr, nullptr};
        return pRoot;
    }

    if(pRoot->data.source > p.source){
        pRoot->pLeft = Insert(pRoot->pLeft, p);
    } else if(pRoot->data.source < p.source) {
        pRoot->pRight =Insert(pRoot->pRight, p);
    } else {
        if((pRoot->data.hours * 60 + pRoot->data.minutes) > (p.hours * 60 + p.minutes)) {
            pRoot->pLeft = Insert(pRoot->pLeft, p);
        } else if((pRoot->data.hours * 60 + pRoot->data.minutes) < (p.hours * 60 + p.minutes)) {
            pRoot->pRight =Insert(pRoot->pRight, p);
        }
        else {
            if(pRoot->data.destination > p.destination){
                pRoot->pLeft = Insert(pRoot->pLeft, p);
            } else if(pRoot->data.destination < p.destination) {
                pRoot->pRight =Insert(pRoot->pRight, p);
            }
        }
    }
    return pRoot;
}

//VD: level_list = ”0.1.4” → In ra các node ở mức 0, mức 1, mức 4
void print_levellist(Node* root, string level_list) {
    vector<string> ListofLevels = Split(level_list, '.');

    for(int i = 0 ; i < ListofLevels.size(); i++) {
        int level = stoi(ListofLevels[i]);
        printLevel(root, level);
    }
}
Node* Findmin(Node* root){
    if(root == nullptr) return nullptr;
    while(root->pLeft != nullptr) {
        root = root->pLeft;
    }
    return root;
}
Node* Remove(Node* root, char ch) {
    if(root == nullptr) return nullptr;

    if(root->data.source[0] < ch) {
        if(root->pLeft == nullptr) {
            Node* temp = root->pRight;
            delete root;
            return temp;
        } else if(root->pRight == nullptr) {
            Node* temp = root->pLeft;
            delete root;
            return temp;
        } else {
            Node* temp = Findmin(root->pRight);
            root->data = temp->data;
            root->pRight = Remove(root->pRight, ch);
        }
        root->pLeft = Remove(root->pLeft, ch);
        root->pRight = Remove(root->pRight, ch);
    }
    return root; 
}

int main() {
    vector<Attendance> res = ReadFile("attendance_data_compact.json");

    Node* root = new Node{res[0], nullptr, nullptr};
    
    for(int i = 0 ; i < res.size(); i++) {
        Insert(root, res[i]);
    }
    print_levellist(root, "0.1.4");
    cout << endl << endl;
    Remove(root, 't');

    print_levellist(root, "0.1.4");

}
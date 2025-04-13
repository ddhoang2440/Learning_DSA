#include<iostream>
#include<cmath>
using namespace std;
struct Node{
    int key;
    Node* pNext;
};

struct List{
    Node *pHead;
    Node *pTail;
};

Node* createNode(int data);
List createList(Node* pNode);
void addTail(List &L, int data);
void addHead(List &L, int data);
void removeHead(List &L);
void removeTail(List &L);
void removeAll(List &L);
void RemoveBefore(List &L, int val);
void printList(List L);
void removeDuplicates(List &L);
void removeAfter(List &L, int val); 
void addPos(List &L, int data, int pos);
void addBefore(List &L, int data, int val);
void addAfter(List &L, int data, int val);
List reverseList(List L);
void PrintPrimeList(List L);
void sortedList(List &L, int data);
void PrintSquareList(List L);
void RemoveKElements(List & L);
void InsertEvenNum(List &L);
void ListOfSum(List& L);
int PresentInt(List L);
List IntToList(List &L, int val);

int main(){

 	List L = createList(NULL);
 	int val;
 	cin >> val;
	L = IntToList(L, val);
	printList(L);
}

Node* createNode(int data){
    Node* pNew = new Node;
    pNew->key = data;
    pNew->pNext = NULL;
    return pNew;
}

List createList(Node* node){
	List L;
	L.pHead = node;
	L.pTail = node;
	return L;
}

void addHead(List &L, int data){
	Node *pNew = createNode(data);
	pNew->pNext = L.pHead;
	L.pHead = pNew;
	if(L.pTail == NULL) {
		L.pTail = pNew;
	}
}

void addTail(List &L, int data){
	Node* pNew = createNode(data);
	if(L.pTail == NULL) {
		L.pHead = L.pTail = pNew;
		return;
	}
		L.pTail->pNext = pNew;
		L.pTail = pNew;
}

void removeHead(List &L){
	Node* temp = L.pHead;
	L.pHead = L.pHead->pNext;
	
	if(L.pHead == NULL) {
		return;
	}
	delete temp;
}

void removeTail(List &L){
	Node* pCur = L.pHead;
	Node* pPrev = NULL;
	if(L.pHead == NULL){
		return;
	}
	while(pCur->pNext != NULL) {
		pPrev = pCur;	
		pCur = pCur->pNext;
	}
	if(pPrev == NULL) {
		delete pCur;
		L.pHead = L.pTail = NULL;
		return;
	} else {
		pPrev->pNext = NULL;
		delete pCur;
		L.pTail = pPrev;
	}
}

void removeAll(List &L){
	Node* pCur = L.pHead;
	
	while(pCur != NULL) {
		Node *pTemp = pCur;
		pCur = pCur->pNext;
		delete pTemp;
	}
	L.pHead = L.pTail = NULL;
}

int countElements(List L){
	if(L.pHead == NULL) return 0;
	Node *pCur = L.pHead;

	int count = 0;
	while(pCur != NULL) {
		count++;
		pCur = pCur->pNext;
	}
	return count;
}


void printList(List L){
	if(L.pHead == NULL) {
		return;
	}
	Node* pCur = L.pHead;
	while(pCur != NULL) {
		cout << pCur->key << " ";
		pCur = pCur->pNext;
	}
	cout << endl;
}

void RemoveBefore(List &L, int val) {
	if(L.pHead == NULL || L.pHead->pNext == NULL) return;
	Node* pCur = L.pHead;
	Node* pPrev = NULL;
	while(pCur != NULL && pCur->pNext != NULL) {
		if(pCur->pNext->key == val) {
			if(pPrev) {
				pPrev->pNext = pCur->pNext;
				delete pCur;
				pCur = pPrev->pNext;
			}
			else {
				L.pHead = pCur->pNext;
				delete pCur;
				pCur = L.pHead;
			}
		}
		else {
			pPrev = pCur;
			pCur = pCur->pNext;
		}
	}
}

void removeDuplicates(List &L) {
	Node *pCur = L.pHead;
	while(pCur != NULL) {
		Node* pPrev = pCur;
		Node* pRun = pCur->pNext;
		while(pRun != NULL) {
			  if(pPrev->key == pRun ->key) {
				pPrev->pNext = pRun->pNext;
				delete pRun;
				pRun = pPrev->pNext;
			  }
			  else {
				pPrev = pRun;
				pRun = pRun->pNext;
			  }
		}
	}
}

void removeAfter(List &L, int val) {
	if(L.pHead == NULL || L.pHead->pNext == NULL) return;
	Node* pCur = L.pHead;

	while(pCur != NULL && pCur->pNext != NULL) {
		if(pCur->key == val) {
			Node* pRun = pCur->pNext;
			if(pRun) {
				pCur->pNext = pRun->pNext;
				delete pRun;
			}
			break;
		}
		pCur = pCur->pNext;
	}
}

void addPos(List &L, int data, int pos) {
	Node* NewNode = createNode(data);
	if(pos == 0) {
		NewNode->pNext = L.pHead;
		L.pHead = NewNode;
	}
	Node* pCur = L.pHead;
	int currPos = 0;
	while(pCur != NULL && currPos < pos - 1 ) {
		currPos++;
		pCur = pCur->pNext;
	}
	
	if(pCur == NULL) {
		delete NewNode;
		return;
	}
	
	NewNode->pNext = pCur->pNext;
	pCur->pNext = NewNode;
}

void removePos(List &L, int pos) {
	if(L.pHead == NULL) {
		return;
	}
	if(pos == 0) {
		Node* temp = L.pHead;
		L.pHead = L.pHead->pNext;
		delete temp;
	}
	if(L.pHead == NULL) {
		L.pTail = NULL;
	}
	Node* pCur = L.pHead;
	Node* pPrev = NULL;
	int currentPos = 0;
	while(pCur != NULL && currentPos < pos) {
		pPrev = pCur;
		pCur=pCur->pNext;
		currentPos++;
	}
	
	if(pCur == NULL) {
		return;
	}
	pPrev->pNext = pCur->pNext;
	if(pCur->pNext == NULL) {
		L.pTail = pPrev;
	}
	delete pCur;
}

void addBefore(List &L, int data, int val){
	Node* NewNode = createNode(data);
	if(L.pHead == NULL) return;
	if(L.pHead->key ==val) {
		NewNode->pNext = L.pHead;
		L.pHead = NewNode;
		return;
	}
	
	Node* pCur = L.pHead->pNext;
	Node* pPrev = L.pHead;
	while(pCur != NULL) { 
		if(pCur->key == val) {
			NewNode->pNext = pPrev->pNext;
			pPrev->pNext = NewNode;
			return;
		}
			pPrev = pCur;	
			pCur = pCur->pNext;
	}
}

void addAfter(List &L, int data, int val) {
	Node *NewNode = createNode(data);
	if(L.pHead == NULL) return;
	
	if(L.pHead->key == val && L.pHead->pNext == NULL) {
			L.pHead->pNext = NewNode;
			L.pTail = NewNode;
			return;
	}
	Node *pCur = L.pHead->pNext;
	while(pCur != NULL) {
		if(pCur->key == val) {
			if(pCur->pNext) {
				NewNode->pNext = pCur->pNext;
				pCur->pNext = NewNode;
			}
			else {
				pCur->pNext = NewNode;
				L.pTail = NewNode;
			}
		}
		pCur = pCur->pNext;
	}
}

List reverseList(List L) {
	Node* pCur = L.pHead;
	Node* pPrev = NULL;
	Node* Next = NULL;
	L.pTail = L.pHead;
	while(pCur != NULL) {
		Next = pCur->pNext;
		pCur->pNext = pPrev;
		pPrev = pCur;
		pCur = Next;
	}
	L.pHead = pPrev;
	return L;
}
void sortedList(List &L, int data) {
	Node* NewNode = createNode(data);
	if(NewNode->key < L.pHead->key) {
		NewNode->pNext = L.pHead;
		L.pHead = NewNode;
		return;
	}
	Node* pCur = L.pHead->pNext;
	Node* pPrev = L.pHead;
	while(pCur != NULL) {
		if ((NewNode->key < pCur->key) && (NewNode->key > pPrev->key)) {
			NewNode->pNext = pPrev->pNext;
			pPrev->pNext =NewNode;
			return;
		}
		else {
			pPrev = pCur;
			pCur = pCur->pNext;
		}
	}
}

bool isPrime(int n) {
	if (n < 2) return 0;
	for(int i = 2; i < n; i++) {
		if(n % i == 0) return 0;
	}
	return 1;
}
void PrintPrimeList(List L) {
	Node* pCur = L.pHead;
	while(pCur != NULL) {
		if(isPrime(pCur->key)) {
			cout << pCur->key << " "; 
		}
		pCur = pCur->pNext;
	}
	cout << endl;
}

bool isSquare(int n) {
	int square = sqrt(n);
	if(square * square == n) return 1;
	return 0;
}

void PrintSquareList(List L) {
	Node* pCur = L.pHead;
	if(L.pHead == NULL) {
		cout << "List is empty";
		return;
	}
	int count = 0;
	while(pCur != NULL) {
		if(isSquare(pCur->key)) {
			cout << pCur->key << " ";
			count++; 
		}
		pCur = pCur->pNext;
	}
	if(count == 0) {
		cout << "Square not found!";
		return;
	}
	cout << endl;
}

void SplitList(List L, List & L1, List & L2) {
	Node* pCur = L.pHead;
	while(pCur != NULL) {
		if((pCur->key) % 2== 1) 
		{
			addTail(L1, pCur->key);
		}
		else {
			addTail(L2, pCur->key);
		}
		pCur = pCur->pNext;
	}
}

int LastPrime(List L) {
	if(L.pHead == NULL) return -1;
	Node* pCur = L.pHead;
	int tempPrime = -1;
	while(pCur != NULL) {
		if(isPrime(pCur -> key)){
			tempPrime = pCur->key;
		}
		pCur = pCur ->pNext;
	}
	return tempPrime;
}

void InsertEvenNum(List &L){

	Node *pCur = L.pHead;
	int evenNum = 2;
	while(pCur != NULL) {
		Node* pNew = createNode(evenNum);
		evenNum += 2;
		pNew->pNext = pCur;
		if(pCur == L.pHead) {
			L.pHead = pNew;
		}
		else {
			Node* pPrev = L.pHead;
			while(pPrev->pNext != pCur) {
				pPrev = pPrev->pNext;
			}
			pPrev->pNext = pNew;
		}
	pCur = pCur->pNext;
	}
}

void ListOfSum(List& L) {
	if(L.pHead == NULL) return;
	Node* pCur = L.pHead;
	Node *pPrev;
	while(pCur != NULL && pCur->pNext != NULL) {
		pPrev = pCur;
		pCur = pCur -> pNext;
		pCur->key = pPrev->key + pCur->key;	
	}
}

void MergeList(List& L, List L1, List L2) {
	while(L1.pHead == NULL && L2.pHead == NULL) return;
	
	Node* pCur1 = L1.pHead;
	while(pCur1 != NULL) {
		addTail(L, pCur1->key);
		pCur1 = pCur1->pNext;
	}
	Node* pCur2 = L2.pHead;
	while(pCur2 != NULL) {
		addTail(L, pCur2->key);
		pCur2 = pCur2->pNext;
	}
}

int PresentInt(List L) {
	if(L.pHead == NULL) return 0;
	Node* pCur = L.pHead;
	int tmp = 0;
	int pint = 0;
	while(pCur != NULL && (pCur->key >= 0 && pCur->key <= 9 )) {
		tmp = pCur->key;
		pint = pint * 10 + tmp;
		pCur = pCur->pNext;
	}
	return pint;
}

List IntToList(List &L, int val) {
	int tmp = 0;
	while(val > 0) {
		tmp = val % 10;
		Node* NewNode = createNode(tmp);
		addHead(L, NewNode->key);
		val /= 10;
	}
	
	return L;
}

Node* FindNode(List L1, List L2) {
	if(L1.pHead == NULL || L2.pHead == NULL ) return NULL;
	Node* pCur2 = L2.pHead;
	while(pCur2 != NULL) {
		pCur2 = pCur2->pNext;
	}
	Node* pCur1 = L1.pHead;
	while(pCur1 != NULL) {
		if(pCur1 -> key == pCur2->key) {
			Node* pNew = createNode(pCur1->key);
			return pNew;
		}
		pCur1 = pCur1->pNext;
	}
	return NULL;
}

bool isPallindrom(Node *pHead) {
	pHead->
}
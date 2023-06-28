#pragma once
#include<iostream>
#include<string>
#include<time.h>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
#include<math.h>
using namespace std;
string TestTXT = "TestFile1.txt";
string SearchTXT = "TestFile13.txt";
class node {
private:
	int key;
	string element;
	node* rightchild;
	node* leftchild;
	node* parent;
	int priorty;
public:
	node() :leftchild(0), rightchild(0), parent(0), key(0), element(""),priorty(0){};
	node(int k, string element) :leftchild(0), rightchild(0), parent(0), key(k), element(element), priorty(0) {};
	int getkey() { return key; }
	string getelement() { return element; }
	friend class BST;
	friend class TH;
	
	
};
class BST {
private:
	node* root;
	node* remove(int x, node* t, string element) {
		node* temp;
		if (t == NULL)
			return NULL;
		else if (x < t->key)
			t->leftchild = remove(x, t->leftchild, element);
		else if (x > t->key)
			t->rightchild = remove(x, t->rightchild, element);
		else if (x == t->key && element != t->element)//處理重複key
			t->rightchild = remove(x, t->rightchild, element);

		else if (t->leftchild && t->rightchild)
		{
			temp = findMin(t->rightchild);
			t->key = temp->key;
			t->rightchild = remove(t->key, t->rightchild, element);
		}
		else
		{
			temp = t;
			if (t->leftchild == NULL)
				t = t->rightchild;
			else if (t->rightchild == NULL)
				t = t->leftchild;
			delete temp;
		}

		return t;
	}
	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->leftchild == NULL)
			return t;
		else
			return findMin(t->leftchild);
	}
	int CheckKey(string element) {
		int value = 0;
		for (int k = 0; k < element.size(); k++) {
			value += element[k];
		}

		node* y = 0; node* x = 0;
		node* insertnode = new node(value, element);
		int newkey = value + 2000 + value % element[0];
		x = root; int ctrl = 0;
		while (x != NULL)
		{
			y = x;

			if (x->key == value && x->element != element) {
				return newkey;
			}
			if (insertnode->key < x->key) x = x->leftchild;
			else x = x->rightchild;
		}
		return value;
	}
	void inorder(node* current) {
		if (current) {
			inorder(current->leftchild);
			cout << "order: " << current->key << " , " << current->element << endl;
			inorder(current->rightchild);
		}
	}
public:
	BST() :root(0) {};
	void InsertBST( string  element) {
		node* y = 0;
		node* x = 0;
		int key = CheckKey(element);
		node* insertnode = new node(key,element);
		x = root;
		int re = 0;
		while (x!=NULL)
		{
			y = x;
			if (x->key == insertnode->key) {//判斷是否已經存在
				if (x->element == insertnode->element) re = 1;
			}
			if (insertnode->key < x->key) {
				x = x->leftchild;
			}
			else  x = x->rightchild;
		}
		if (re == 1) return;
		insertnode->parent = y;
		if (y == NULL)
			this->root = insertnode;
		else if (insertnode->key < y->key)
			y->leftchild = insertnode;
		else//等於 大於 KEY 放右邊
			y->rightchild = insertnode;
	}
	void search(string element) {
		node* current = root;
		int num = 0;
		for (int k = 0; k < element.size(); k++) {
			num += element[k];
		}
		num=CheckKey(element);
		while (current != NULL ) {
		if (num < current->key)
			current = current->leftchild;
		else if (num == current->key && element==current->element) {
			cout << "Find: key=  "<<current->key <<" , " << current->element << endl;
			return;
		}
		else current = current->rightchild;
		}
		if(!current) cout << "NO DATA : " <<element<<endl;
	}
	void useremove(string element) {
		int key = CheckKey(element);
		root = remove(key, root,element);
	}
	void CreatDiction() {
		ifstream in(TestTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						InsertBST(temp);
						head = i + 1;
						continue;
					}
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						InsertBST(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
	void Print() {
		node* current = root;
		if (!root) cout << "EMPTY TREE" << endl;
		else
			inorder(root);
	}
	void Search_Diction() {
		ifstream in(SearchTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						search(temp);
						head = i + 1;
						continue;
					}

					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						search(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
	void AlltextCompare() {
		string all, search;
		ifstream in(TestTXT);
		if (in) {
			stringstream ss;
			ss << in.rdbuf();
			string alltext(ss.str());
			all = alltext;
		}
		else cout << "no such file1" << endl;
		in.close();
		ifstream in2(SearchTXT);
		if (in2) {
			stringstream ss2;
			ss2 << in2.rdbuf();
			string alltext2(ss2.str());
			search = alltext2;
		}
		else cout << "no such file2" << endl;
		in2.close();
		if (all.find(search)) cout << "----------------------------------------------" << endl << endl <<
			"Text2 is Text1's  substring" << endl << endl << "----------------------------------------------" << endl;
		else  cout << "----------------------------------------------" << endl<<endl << 
			"Not in Text1 !" << endl<<endl<< "----------------------------------------------" << endl;
	
	}
};
class TH {
private:
	node* root;
	node* newnode(int key, string element) {
		node* temp = new node;
		temp->key = key;
		temp->element = element;
		temp->leftchild = NULL;
		temp->rightchild = NULL;
		temp->priorty = rand() % 10000 + 1;
		return temp;

	}
	bool search(node* r, int key, string element) {
		if (r == nullptr) return 0;
		if (r->key == key && r->element == element) {
			cout << "Find: key=  " << r->key << " , " << r->element << " ,p " << r->priorty << endl;
			return 1;
		}
		if (key < r->key)
			return search(r->leftchild, key, element);
		return search(r->rightchild, key, element);
	}
	void inorder(node* root)
	{
		if (root)
		{
			inorder(root->leftchild);
			cout << "order: " << root->key << " , " << root->element << " p: " << root->priorty << endl;

			inorder(root->rightchild);
		}
	}
	void deleteTH(node*& r, int key, string element) {
		if (r == nullptr) return;
		if (key < r->key) deleteTH(r->leftchild, key, element);
		else if (key > r->key) deleteTH(r->rightchild, key, element);
		else if (key == r->key && element != r->element) deleteTH(r->rightchild, key, element);
		else {
			if (r->leftchild == nullptr && r->rightchild == nullptr) {
				delete r;
				r = nullptr;
			}
			else if (r->leftchild && r->rightchild) {
				if (r->leftchild->priorty < r->rightchild->priorty) {
					rotLeft(r);
					deleteTH(r, key, element);
				}
				else {
					rotRight(r);
					deleteTH(r, key, element);
				}
			}
			else {
				node* x = (r->leftchild) ? r->leftchild : r->rightchild;
				node* y = r;
				r = x;
				delete y;
			}
		}
	}
	void rotLeft(node*& r) { //left rotation
		node* R = r->rightchild;
		node* X = r->rightchild->leftchild;
		R->leftchild = r;
		r->rightchild = X;
		r = R;
	}
	void rotRight(node*& r) { //right rotation
		node* L = r->leftchild;
		node* Y = r->leftchild->rightchild;
		L->rightchild = r;
		r->leftchild = Y;
		r = L;
	}
	bool check_exist(int value, string element) {//確認Node是否已經存在
		node* y = 0; node* x = 0;
		node* insertnode = new node(value, element);
		x = root;
		while (x != NULL)
		{
			y = x;
			if (x->key == value && x->element == element)  return 1;
			if (insertnode->key < x->key) x = x->leftchild;
			else x = x->rightchild;
		}
		return 0;
	}
	int CheckKey(string element) {
		int value = 0;
		for (int k = 0; k < element.size(); k++) {
			value += element[k];
		}

		node* y = 0; node* x = 0;
		node* insertnode = new node(value, element);
		int newkey = value + 2000 + value % element[0];
		x = root; int ctrl = 0;
		while (x != NULL)
		{
			y = x;
			if (x->key == value && x->element != element) {
				return newkey;
			}
			if (insertnode->key < x->key) x = x->leftchild;
			else x = x->rightchild;
		}
		return value;
	}
	void insertnode(node*& n, int value, string element) {
		if (n == nullptr) {
			n = newnode(value, element);
			return;
		}
		if (value < n->key) {
			insertnode(n->leftchild, value, element);
			if (n->leftchild->priorty > n->priorty&& n->leftchild != nullptr)
				rotRight(n);
		}
		else {
			insertnode(n->rightchild, value, element);
			if (n->rightchild->priorty > n->priorty&& n->rightchild != nullptr)
				rotLeft(n);
		}
	}
public:
	TH():root(0) {};
	void InsertTH(string  element) {
		int key = CheckKey(element);
		if(!check_exist(key,element))
			insertnode(root, key, element);
		
	}
	void use_search(string element) {
		int key = CheckKey(element);	
		if (!search(root, key, element)) cout << "NO DATA : "<<element<<endl;
	}
	void use_delete(string element) {
		int key = CheckKey(element);
		deleteTH(root, key, element);
	}
	void CreatDiction() {
		ifstream in(TestTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int num = 0;
				int head=0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if(line[i]==' '){
						string temp = line.substr(head, i-head);
						InsertTH(temp);
						num = 0;head = i + 1;		
						continue;
					}
					num = num + line[i];
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head+1);
						InsertTH(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
	void PrintTH() {
		node* current = root;
		if (!root) cout << "EMPTY TREE" << endl;
		else
			inorder(root);
	}
	void Search_Diction() {
		ifstream in(SearchTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						use_search(temp);
						head = i + 1;
						continue;
					}
					
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						use_search(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
};
class hnode {
private:
	string element;
	hnode* next;
	hnode* parent;
public:
	hnode() :element(" "), next(0),parent(0) {};
	hnode(string s) :element(s), next(0),parent(0) {};
	friend class Hash;
	friend class Hash2;
};
class Hash2 {//A*P^n mod m
private:
	string Hashtable[1000] = {};
	int Max = 1000;
	int ERROR = 0;
	int p = 151;//大於all字元ASCII的質數
public:
	void setarray() {
		for (int i = 0; i < Max; i++) Hashtable[i] = " ";
	}
	//A*P^n mod m
	void Hash_function2( string s) {
		unsigned long long  value = 0;
		for (int i = 0; i < s.size(); i++) {
			value = value + s[i] * pow(p, i);
		}
		if (ERROR == 1) return;
		int key = value % Max;
		int start=key;
		while (Hashtable[key] != " " && key < Max) {
			
			if (Hashtable[key] == s) return;
			key++;
			if (key == start) { cout << "NO Space ! " << endl; ERROR = 1; return; }
			if (key == Max) key = 0;
		}
		Hashtable[key] = s;
	}
	//A mod m
	void Hash_function(string s) {
		unsigned long long  value = 0;
		for (int i = 0; i < s.size(); i++) {
			value = value + s[i];
		}
		if (ERROR == 1) return;
		int key = value % Max;
		int start = key;
		while (Hashtable[key] != " " && key < Max) {

			if (Hashtable[key] == s) return;
			key++;
			if (key == start) { cout << "NO Space ! " << endl; ERROR = 1; return; }
			if (key == Max) key = 0;
		}
		Hashtable[key] = s;
	}
	void SearchHash(string target) {
		int  value = 0;
		for (int i = 0; i < target.size(); i++) {
			value = value + target[i];
		}
		if (ERROR == 1) return;
		int key = value % Max;
		int start = key;
		while (true) {

			if (Hashtable[key] == target) {
				cout << "Find: " << "Key= " << key << " ,element= " << Hashtable[key] << endl;
				return;
			}
			key++;
			if (key == start) { cout << "No Find : " << target << endl; return; }
			if (key == Max) key = 0;

		}
	}
	void SearchHash2(string target) {
		unsigned long long  value = 0;
		for (int i = 0; i < target.size(); i++) {
			value = value + target[i] * pow(p, i);
		}
		if (ERROR == 1) return;
		int key = value % Max;
		int start = key;
		while (true) {

			if (Hashtable[key] == target) {
				cout << "Find: " << "Key= " << key << " ,element= " << Hashtable[key] << endl;
				return;
			}
			key++;
			if (key == start) { cout << "No Find : " << target << endl; return; }
			if (key == Max) key = 0;
		
		}
	}
	void DeleteHash(string target) {
		int t = 0;
		int first = 0;
		for (int i = 0; i < target.size(); i++) {
			t += target[i];
		}
		int key = t % Max;
		while (true) {
			if (Hashtable[key] == target) {
				cout << "Delete successfull " << endl;
				Hashtable[key] = " ";
				return;
			}
			if (first == 0) { key = Max; first = 1; }
			key--;
			if (key < 0) { cout << "NO DATA ! " << endl; return; }
		}
	}
	void DeleteHash2(string target) {
		unsigned long long  t = 0;
		int first = 0;
		for (int i = 0; i < target.size(); i++) {
			t += target[i] * pow(p, i);;
		}
		int key = t % Max;
		while (true) {
			if (Hashtable[key] == target) {
				cout << "Delete successfull " << endl;
				Hashtable[key] = " ";
				return;
			}
			if (first == 0) { key = Max; first = 1; }
			key--;
			if (key < 0) { cout << "NO DATA ! " << endl; return; }
		}
	}
	void PrintHash() {
		for (int i = 0; i < Max; i++) {
			cout << "key= " << i << " ";
			
			cout << Hashtable[i] << endl;
		
			cout << "==================================================" << endl;
		}
	}
	void CreatDiction() {
		ifstream in(TestTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int num = 0;
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
				if (line[i] == ' ') continue;
				if ((line[i] >= 0 && line[i] <= 47) ||
					(line[i] >= 58 && line[i] <= 64) ||
					(line[i] >= 91 && line[i] <= 96)) {
					line.erase(line.begin() + i);
					continue;
				}
			}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						Hash_function(temp);
						num = 0; head = i + 1;
						continue;
					}
				num = num + line[i];
				if (i == line.size() - 1) {// last word
					string temp = line.substr(head, i - head + 1);
					Hash_function(temp);
				}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
	void CreatDiction2() {
		ifstream in(TestTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int num = 0;
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						Hash_function2(temp);
						num = 0; head = i + 1;
						continue;
					}
					num = num + line[i];
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						Hash_function2(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
	void Search_Dictionary() {
		ifstream in(SearchTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						SearchHash(temp);
						head = i + 1;
						continue;
					}
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						SearchHash(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();	
	}
	void Search_Dictionary2() {
		ifstream in(SearchTXT);
		string line;
		if (in) {
			while (getline(in, line)) {
				int head = 0;
				for (int i = 0; i < line.size(); i++) {//去除符號
					if (line[i] == ' ') continue;
					if ((line[i] >= 0 && line[i] <= 47) ||
						(line[i] >= 58 && line[i] <= 64) ||
						(line[i] >= 91 && line[i] <= 96)) {
						line.erase(line.begin() + i);
						continue;
					}
				}
				for (int i = 0; i < line.size(); i++)//抓單字
				{
					if (line[i] == ' ') {
						string temp = line.substr(head, i - head);
						SearchHash2(temp);
						head = i + 1;
						continue;
					}
					if (i == line.size() - 1) {// last word
						string temp = line.substr(head, i - head + 1);
						SearchHash2(temp);
					}
				}
			}
		}
		else cout << "no such file" << endl;
		in.close();
	}
};

class TwoThreeNode {
private:
	// Gets the value of the smallest data item in the subtree
	// rooted by this node
	int getSmallest() {
		TwoThreeNode* node = this;
		while (!node->isLeaf()) node = node->child[0];
		return node->key[0];
	}
	string getSmallestElement() {
		TwoThreeNode* node = this;
		while (!node->isLeaf()) node = node->child[0];
		return node->element[0];
	}
	// Insert into a node with 1 child
	void insert1Siblings(TwoThreeNode* newChild, int newSmallest,string s) {
		int newKey = newChild->key[0];

		newChild->parent = this;

		if (newKey < child[0]->key[0]) {
			// newNode is inserted as first child of root
			child[1] = child[0];
			child[0] = newChild;
			element[0] = getSmallestElement();//
			key[0] = child[1]->getSmallest();
		}
		else {
			// newNode is iserted as second child of root
			child[1] = newChild;
			element[1] = s;// 
			key[0] = newSmallest;
		}
	}
	// Insert into a node with 2 children
	void insert2Siblings(TwoThreeNode* newChild, int newSmallest,string s) {// +進已經有2筆資料
		int newKey = newChild->key[0];
	
		newChild->parent = this;

		if (newKey < child[0]->key[0]) {
			child[2] = child[1];
			child[1] = child[0];
			child[0] = newChild;

			key[1] = key[0];
			element[1] = element[0];//
			key[0] = child[1]->getSmallest();
			element[0] = child[1]->getSmallestElement();//
			updateParentSmallest(newSmallest,s);
		}
		else if (newKey < child[1]->key[0]) {
			child[2] = child[1];
			child[1] = newChild;

			key[1] = key[0];
			element[1] = element[0];//
			key[0] = newSmallest;
			element[0] = s;//
		}
		else {
			child[2] = newChild;
			key[1] = newSmallest;
			element[1] = s;//
		}
	}
	// Insert into a node with 3 children
	void insert3Siblings(TwoThreeNode* newChild, int newSmallest,string s) {// +進已經有３筆資料
		int newKey = newChild->key[0];
		int splitSmallest = -1;
		string splitElement;
		TwoThreeNode* splitNode = new TwoThreeNode();
		splitNode->parent = parent;

		if (newKey < child[0]->key[0] || newKey < child[1]->key[0]) {
			// newChild is inserted in current node
			splitSmallest = key[0];
			splitElement = element[0];//
			splitNode->child[0] = child[1];
			splitNode->child[1] = child[2];
			splitNode->key[0] = key[1];
			splitNode->element[0] = element[1];//

			child[1]->parent = splitNode;
			child[2]->parent = splitNode;
			newChild->parent = this;

			if (newKey < child[0]->key[0]) {
				// newChild is inserted as first child
				child[1] = child[0];
				child[0] = newChild;

				key[0] = child[1]->getSmallest();
				element[0] = child[1]->getSmallestElement();//
				updateParentSmallest(newSmallest,s);
			}
			else {
				// newChild is inserted as second child
				child[1] = newChild;

				key[0] = newSmallest;
			}
		}
		else {
			// newChild is inserted in split node
			child[2]->parent = splitNode;
			newChild->parent = splitNode;

			if (newKey < child[2]->key[0]) {
				// newChild is inserted as first child
				splitSmallest = newSmallest;
				splitElement = s;//
				splitNode->child[0] = newChild;
				splitNode->child[1] = child[2];
				splitNode->element[0] = element[1];//
				splitNode->key[0] = key[1];
			}
			else {
				// newChild is inserted as second child
				splitSmallest = key[1];
				splitElement = element[1];//
				splitNode->child[0] = child[2];
				splitNode->child[1] = newChild;
				splitNode->key[0] = newSmallest;
				splitNode->element[0] = s;//
			}
		}

		child[2] = NULL;
		key[1] = -1;

		if (parent->parent == NULL) {
			// At root, so new root needs to be created
			TwoThreeNode* newNode = new TwoThreeNode();

			parent->child[0] = newNode;
			newNode->parent = parent;
			newNode->child[0] = this;
			parent = newNode;
		}

		parent->insert(splitNode, splitSmallest,splitElement);
	}
	// Update the parent nods efor the smallest child value
	void updateParentSmallest(int data,string s) {
		switch (sibNumber()) {
		case 0: if (parent->parent != NULL) parent->updateParentSmallest(data,s); break;
		case 1:
			parent->key[0] = data;
			parent->element[0] = s;
			break;
		case 2:
			parent->key[1] = data; 
			parent->element[1] = s;
			break;
		}
	}
public:
	int key[2];
	string element[2];
	TwoThreeNode* parent, * child[3];
	// Constructor
	TwoThreeNode(int data = -1) {
		key[0] = data;
		key[1] = -1;
		parent = child[0] = child[1] = child[2] = NULL;
	}
	// Check if node is a leaf 確認是否為葉
	bool isLeaf() {
		return (child[0] == NULL);
	}
	// Get which sibling the node is (算已經有幾個資料)
	int sibNumber() {
		for (int i = 0; i < 3; ++i) {
			if (this == parent->child[i]) return i;
		}
		return -1;
	}
	// Insertion
	void insert(TwoThreeNode* newChild, int newSmallest,string s) {
		if (child[1] == NULL) insert1Siblings(newChild, newSmallest,s);
		else if (child[2] == NULL) insert2Siblings(newChild, newSmallest,s);
		else insert3Siblings(newChild, newSmallest,s);
	}
};
// TwoThreeTree class
class TwoThreeTree {
private:
	TwoThreeNode* root;
	// Find the appropriate operation point
	TwoThreeNode* findSpot(TwoThreeNode* node, int data) {
		if (node == NULL) return NULL;

		while (!node->isLeaf()) {
			if (node->key[0] == data || node->key[1] == data)
				return NULL;
			if (node->key[0] == -1 || data < node->key[0])
				node = node->child[0];
			else if (node->key[1] == -1 || data < node->key[1])
				node = node->child[1];
			else
				node = node->child[2];
		}

		if (node->key[0] == data) return NULL;
		return node->parent;
	}
	// Recursively print the subtree starting from the given node
	void print(TwoThreeNode* node, int tabs = 0) {
		for (int i = 0; i < tabs; ++i) {
			cout << "\t";
		}

		if (node == NULL) {
			cout << "`--> NULL" << endl;
			return;
		}

		cout << "`--> " << node->sibNumber()
			<< ": ( " << node->key[0] << ", " << node->key[1] << ")" << endl;

		if (!node->isLeaf()) {
			++tabs;
			print(node->child[0], tabs);
			print(node->child[1], tabs);
			print(node->child[2], tabs);
		}
	}
public:
	// Constructor
	TwoThreeTree() {
		root = new TwoThreeNode();
		root->child[0] = new TwoThreeNode();
		root->child[0]->parent = root;
	}
	// Insert
	bool insert(int data,string s) {
		TwoThreeNode* newNode = new TwoThreeNode(data);
		TwoThreeNode* spot = root->child[0];

		if (spot->child[0] == NULL) {
			// First insertion
			newNode->parent = spot;
			spot->child[0] = newNode;
		}
		else {
			spot = findSpot(spot, data);
			if (spot == NULL) return false;

			spot->insert(new TwoThreeNode(data), data,s);
		}
		return true;
	}
	// Print
	void print() {
		print(root->child[0]);
		cout << endl;
	}
};
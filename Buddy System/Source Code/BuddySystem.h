#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <Iterator>
#include <string>

using namespace std;

class Node { // block info
private:
	int value;
	int allocate;
	string name;
	Node* left;
	Node* right;
	Node* father;
	Node* brother;
	bool flag;
public:
	Node(int val) {
		value = val;
		left = nullptr;
		right = nullptr;
		father = nullptr;
		allocate = 0;
		brother = nullptr;
		flag = false;
	}

	int get_Val() { return value; }
	bool get_Flag() { return flag; }
	Node* get_Left() { return left; }
	Node* get_Right() { return right; }
	Node* get_Father() { return father; }
	Node* get_Brother() { return brother; }
	void set_Left(Node* node) { this->left = node; }
	void set_Right(Node* node) { this->right = node; }
	void set_Father(Node* node) { this->father = node; }
	void update_Val(int val) { value = val; }
	int get_Allocate() { return allocate; }
	void set_Allocate(int allo) { allocate = allo; }
	void set_Flag(bool tag) { flag = tag; }
	void set_Brother(Node* node) { this->brother = node; }
	
};


/**   allocate memory to process           */
bool Allocate(pair<string, int> &input, Node* root, Node* node, unordered_map<string, Node*> &map, list<Node*> &set);
/**   release memory of process           */
bool Release(pair<string, int> &input, Node* root, Node* node, unordered_map<string, Node*> &map, list<Node*> &set);
/**   calculate the size process need in the memory           */
int calculate(int val);
/**   print the table     */
void print(list<Node*> set, unordered_map<string, Node*> map);
/**   initial test data           */
void initial(vector<pair<string, int> > &input);
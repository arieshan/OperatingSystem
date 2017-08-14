#include "BuddySystem.h";

/**   allocate memory to process           */
bool Allocate(pair<string, int> &input, Node* root, Node* node, unordered_map<string, Node*> &map, list<Node*> &set) {
	int size = calculate(input.second);                     // calculate the size of the process need in the memory
	Node* temp = node;				
	while (temp->get_Val() > size) { 
		int split_value = temp->get_Val() / 2;
		temp->set_Flag(true);
		Node* left = new Node(split_value);
		Node* right = new Node(split_value);
		temp->set_Left(left);
		temp->set_Right(right);
		left->set_Father(temp);
		right->set_Father(temp);
		left->set_Brother(right);
		right->set_Brother(left);
		list<Node*>::iterator it = set.begin();
		for (it; it != set.end(); ++it)
			if ((*it) == temp)
				break;
		temp = temp->get_Left();
		set.insert(it,left);
		set.insert(it,right);
		set.erase(it);
	}
	temp->set_Allocate(input.second);
	temp->set_Flag(true);
	map[input.first] = temp;
	return true;
}

/**   release memory of process           */
bool Release(pair<string, int> &input, Node* root, Node* node, unordered_map<string, Node*> &map, list<Node*> &set) {
	Node* temp = map[input.first];
	temp->set_Allocate(0);
	temp->set_Flag(false);

	if (node == root) {
		root->set_Allocate(0);
		root->set_Flag(false);
	}

	while (temp->get_Brother()->get_Flag() == false) {
		Node* child_1 = temp;
		Node* child_2 = temp->get_Brother();
		list<Node*>::iterator it_child1 = set.begin();
		list<Node*>::iterator it_child2 = set.begin();
		for (it_child1; it_child1 != set.end(); ++it_child1)
			if ((*it_child1) == temp)
				break;
		for (it_child2; it_child2 != set.end(); ++it_child2)
			if ((*it_child2) == temp->get_Brother())
				break;
		temp = temp->get_Father();
		temp->set_Allocate(0);
		temp->set_Flag(false);
		set.insert(it_child1, temp);
		set.erase(it_child1);
		set.erase(it_child2);
		delete child_1;
		delete child_2;
		if (set.size() == 1)
			break;
	}
	return true;
}

int calculate(int val) {
	int result = 1;
	while (result < val)
		result *= 2;
	return result;
}

void print(list<Node*> set, unordered_map<string, Node*> map) {
	cout << "The start address is:     ";
	int start = 0;
	for (list<Node*>::iterator it = set.begin(); it != set.end(); ++it) {
		cout << start << "\t";
		start += (*it)->get_Val();
	}
	cout << endl;
	cout << "The end address is:       ";
	int end = 0;
	for (list<Node*>::iterator it = set.begin(); it != set.end(); ++it) {
		end += (*it)->get_Val();
		cout << end << "\t";
	}
	cout << endl;
	cout << "The block size is:        ";
	for (list<Node*>::iterator it = set.begin(); it != set.end(); ++it)
		cout << (*it)->get_Val() << "\t";
	cout << endl;
	cout << "The allocation is:        ";
	for (list<Node*>::iterator it = set.begin(); it != set.end(); ++it) {
		cout << (*it)->get_Allocate() << "\t";
	}


}

void initial(vector<pair<string, int> > &input) {
	pair<string, int> p0("A", 20);
	input.push_back(p0);
	pair<string, int> p1("B", 35);
	input.push_back(p1);
	pair<string, int> p2("C", 90);
	input.push_back(p2);
	pair<string, int> p3("D", 40);
	input.push_back(p3);
	pair<string, int> p4("E", 240);
	input.push_back(p4);
	pair<string, int> p5("A", -20);
	input.push_back(p5);
	pair<string, int> p6("B", -35);
	input.push_back(p6);
	pair<string, int> p7("C", -90);
	input.push_back(p7);
	pair<string, int> p8("D", -40);
	input.push_back(p8);
	pair<string, int> p9("E", -240);
	input.push_back(p9);
}
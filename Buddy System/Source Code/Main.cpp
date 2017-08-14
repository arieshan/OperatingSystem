#include "BuddySystem.h";

int main() {
	vector<pair<string, int> > input;
	int block = 2048;
	Node* root = new Node(block);
	list<Node*> children_set;
	children_set.push_back(root);
	unordered_map<string, Node*> map;

    initial(input);

	for (int i = 0; i < input.size(); i++) {
		cout << "input " << input[i].first << " with value " << input[i].second << endl;
		int val = input[i].second;
		Node* node = nullptr;
		if (val > 0) {
			for (list<Node*>::iterator it = children_set.begin(); it != children_set.end() ; it++) {
				if ((*it)->get_Val() > val && (*it)->get_Flag() == false) {
					node = (*it);
					break;
				}
			}
			Allocate(input[i], root, node, map, children_set);
			print(children_set, map);
			cout << endl;
			cout << endl;
		}
		else {
			node = map[input[i].first];
			Release(input[i], root, node, map, children_set);
			print(children_set, map);
			cout << endl;
			cout << endl;
		}
	}

	return 0;
}
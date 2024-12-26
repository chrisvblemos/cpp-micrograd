#pragma once

struct Op {
	string Name;

	Op(string _name) {
		Name = _name;
	}

	
};

class Node() {
	Node();

public:
	Node* Next;
	Node* Previous;

	Op Operation;


}
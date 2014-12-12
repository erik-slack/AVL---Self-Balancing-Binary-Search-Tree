#pragma once
#include <iostream>

class Node {
friend class AVL;
private:
	int data;
	int height;
	Node* left_child;
	Node* right_child;

public:
	Node();
	~Node();

// ANALYZERS
	int getData();
	int getHeight();
	Node* getLeftChild();
	Node* getRightChild();
};


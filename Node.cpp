#include "Node.h"

using namespace std;

Node::Node() {
	left_child = NULL;
	right_child = NULL;
	data = 0;
	height = 0;
}

Node::~Node() {
	left_child = NULL;
	right_child = NULL;
	data = -1;
	height = -1;
}

// ANALYZERS
	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	int Node::getData(){
		return data;
	}
	
	/*
	 * Returns the height of this node. The height is the number of edges
	 * from this node to this nodes farthest child.
	 */
	int Node::getHeight(){
		return height;
	}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	Node* Node::getLeftChild(){
		return left_child;
	}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	Node* Node::getRightChild(){
		return right_child;
	}


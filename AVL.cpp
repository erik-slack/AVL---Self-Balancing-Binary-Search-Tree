#include "AVL.h"

using namespace std;

AVL::AVL() {
	root = NULL;
}
AVL::~AVL() {
	clear();
	root = NULL;
}

/*
 * Returns the root node for this tree
 *
 * @return the root node for this tree.
 */
Node* AVL::getRootNode(){
	return root;
}

/*
 * Attempts to add the given int to the AVL tree
 *
 * @return true if added
 * @return false if unsuccessful (i.e. the int is already in tree)
 */
bool AVL::add(int data){
	bool was_added = false;
	
	if (root == NULL){
		root = new Node;
		root->data = data;
		was_added = true;
	} else {
		if (contains(data, root) == NULL){
			root = recursiveAdd(data, root);
			was_added = true;
		} else {
			was_added = false;
		}
	}
	
	return was_added;
}

Node* AVL::recursiveAdd(int data, Node* current_search){
	if (current_search == NULL){
		Node* location_added = new Node;
		location_added->data = data;
		return balance(location_added);
	}
	
	if (data > current_search->data){
		current_search->right_child = recursiveAdd(data, current_search->right_child);
	} else {
		current_search->left_child = recursiveAdd(data, current_search->left_child);
	}
	
	return balance(current_search);
}

Node* AVL::contains(int data, Node* current_search){
	if (current_search == NULL){return NULL;}
	
	if (current_search->data == data){
		return current_search;
	} else if (current_search->data < data){ // && current_search->right_child != NULL
		return contains(data, current_search->right_child);
	} else if (current_search->data > data){
		return contains(data, current_search->left_child);
	}
	
	return current_search;
}

void AVL::print(Node* current_print){
	if (current_print == NULL){return;}
	cout << current_print->data << " | height = " << current_print->height << " | left child = ";
	if(current_print->left_child == NULL){
		cout << "NULL ";
	} else {
		cout << current_print->left_child->data;
	}
	cout << " and right_child child = ";
	if(current_print->right_child == NULL){
		cout << "NULL";
	} else {
		cout << current_print->right_child->data;
	}
	cout << endl;
	
	print(current_print->right_child);
	print(current_print->left_child);
}

/*
 * Attempts to remove the given int from the AVL tree
 *
 * @return true if successfully removed
 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
 */
bool AVL::remove(int data){
	bool was_removed = false;
	if (root == NULL){
		// DO NOTHING
	} else {	
		Node* checker = contains(data, root);
		if (checker != NULL && (checker->data == data)){
			root = recursiveRemove(data, root);
			was_removed = true;
		} else {
			// DO NOTHING
		}
	}
	
	return was_removed;
}

Node* AVL::recursiveRemove(int data, Node* current_search){
	if (current_search == NULL){
		return NULL;
	} else if (current_search->data < data){
		current_search->right_child = recursiveRemove(data, current_search->right_child);
	} else if (current_search->data > data){
		current_search->left_child = recursiveRemove(data, current_search->left_child);
	} else {
		if (current_search->left_child == NULL){
			Node* temp = current_search->right_child;
			delete current_search;
			return temp;
		} else {
			current_search->left_child = IOP(current_search->left_child, current_search);
			return balance(current_search);
		}
	}

	return balance(current_search);
}

Node* AVL::IOP(Node* current, Node* node_to_remove){
	if (current->right_child == NULL){}
	if (current->right_child != NULL){
		current->right_child = IOP(current->right_child, node_to_remove);
		return balance(current);
	} else {
		node_to_remove->data = current->data;
		Node* temp = current->left_child;
		delete current;
		return temp;
	}	
}

/*
 * Removes all nodes from the tree, resulting in an empty tree.
 */
void AVL::clear(){
	while (root != NULL){
		remove(root->data);
	}
}

// AVL FUNCTIONS

int AVL::height(Node* node_query){
	return node_query ? node_query->height : 0;
}

void AVL::fixHeight(Node* parent){
	int hl = height(parent->left_child);
	int hr = height(parent->right_child);
	parent->height = (hl>hr ? hl : hr) + 1;
}

int AVL::heightDiff(Node* parent){
	//cout << parent->data << " | " << parent->height << " = parent height | height right = " << height(parent->right_child) << " | height left = " << height(parent->left_child) << endl;
	return height(parent->right_child) - height(parent->left_child);
}

Node* AVL::balance(Node* parent){
	fixHeight(parent);
	int heightDifference = heightDiff(parent);
	if (heightDifference == 2){
		//cout << "heightDiff == 2" << endl;
		if (heightDiff(parent->right_child) < 0)
			parent->right_child = rotateRight(parent->right_child);
		return rotateLeft(parent);
	} else if (heightDifference == -2){
		//cout << "heightDiff == -2" << endl;
		if (heightDiff(parent->left_child) > 0)
			parent->left_child = rotateLeft(parent->left_child);
		return rotateRight(parent);
	} else {
		//cout << "heightDifference = " << heightDifference << " thus no balance needed" << endl;
		return parent; // no balance needed
	}
}

Node* AVL::rotateRight(Node* pivot){
	Node* pivot2 = pivot->left_child;
	pivot->left_child = pivot2->right_child;
	pivot2->right_child = pivot;
	fixHeight(pivot);
	fixHeight(pivot2);
	return pivot2;
}
Node* AVL::rotateLeft(Node* pivot2){
	Node* pivot = pivot2->right_child;
	pivot2->right_child = pivot->left_child;
	pivot->left_child = pivot2;
	fixHeight(pivot2);
	fixHeight(pivot);
	return pivot;
}

Node* AVL::getMin (Node* parent){
    return parent->left_child?getMin(parent->left_child):parent;
}

Node* AVL::removeMin (Node* parent){
    if (parent->left_child == 0){
        return parent->right_child;
	}
    parent->left_child = removeMin(parent->left_child);
    return balance(parent);
}

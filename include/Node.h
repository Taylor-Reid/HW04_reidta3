/*
	Info
*/

#include "Starbucks.h"

class Node{
public:
	Node(Entry* c);
	Node* insert(Entry* e, Node* r, bool isXLevel);
	Entry* search(Entry* e, Node* r, bool isXLevel);

	Node* left_;
	Node* right_;

	Entry* key;
};
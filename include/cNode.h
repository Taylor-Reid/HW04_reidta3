/*
	Info
*/

#include "Census.h"

class cNode{
public:
	cNode(cEntry* c);
	cNode* insert(cEntry* e, cNode* r, bool isXLevel);
	cEntry* search(cEntry* e, cNode* r, bool isXLevel);

	cNode* left_;
	cNode* right_;

	cEntry* key;
};
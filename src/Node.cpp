/*
Notes & info
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"

using namespace ci;
using namespace ci::app;
using namespace std;



Node::Node(Entry* c){
	key=c;
	left_=NULL;
	right_=NULL;
}

Node* Node::insert(Entry* e, Node* r, bool isXlevel){
	if(e != NULL){
		if(r == NULL) return new Node(e);
		if(isXlevel){
			if(e->x <= r->key->x){
				r->left_ = insert(e,r->left_,!isXlevel);
			}else{
				r->right_ = insert(e,r->right_,!isXlevel);
			}
		}else{
			if(e->y <= r->key->y){
				r->left_ = insert(e,r->left_,!isXlevel);
			}else{
				r->right_ = insert(e,r->right_,!isXlevel);
			}
		}
	}
	return r;
}

Entry* Node::search(Entry* e, Node* r, bool isXlevel){
	if(r == NULL) return NULL;
	if(r->key == e) return r->key; // probably doesn't apply since we are not given a name... need to work it out...
	Entry* found;
	if(isXlevel){
		if(e->x < r->key->x){
			if(r->left_==NULL){
				found = r->key;
			}else{
				found = search(e,r->left_,!isXlevel);
			}
		}else{
			if(r->right_==NULL){
				found = r->key;
			}else{
				found = search(e,r->right_,!isXlevel);
			}
		}
	}else{
		if(e->y < r->key->y){
			if(r->left_==NULL){
				found = r->key;
			}else{
				found = search(e,r->left_,!isXlevel);
			}
		}else{
			if(r->right_==NULL){
				found = r->key;
			}else{
				found = search(e,r->right_,!isXlevel);
			}
		}
	}
	Entry* current = r->key;
	double dCurr= sqrt(((current->x)-(e->x))*((current->x)-(e->x))-((current->y)-(e->y))*((current->y)-(e->y)));
	double dFound= sqrt(((found->x)-(e->x))*((found->x)-(e->x))-((found->y)-(e->y))*((found->y)-(e->y)));
	if(dCurr < dFound){
		found=current;
	}
	return found;
}
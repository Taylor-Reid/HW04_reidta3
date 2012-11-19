/*
This class contains the insert and search functions essential to this project. 
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cNode.h"

using namespace ci;
using namespace ci::app;
using namespace std;



cNode::cNode(cEntry* c){
	key=c;
	left_=NULL;
	right_=NULL;
}

cNode* cNode::insert(cEntry* e, cNode* r, bool isXlevel){
	if(e != NULL){
		if(r == NULL) return new cNode(e);
		if(isXlevel){//split based on x
			//if it is less than the checked starbucks, keep checking the left
			if(e->x <= r->key->x){
				r->left_ = insert(e,r->left_,!isXlevel);
			}else{//otherwise check the right.
				r->right_ = insert(e,r->right_,!isXlevel);
			}
		}else{// split based on y, same procedure as x.
			if(e->y <= r->key->y){
				r->left_ = insert(e,r->left_,!isXlevel);
			}else{
				r->right_ = insert(e,r->right_,!isXlevel);
			}
		}
	}
	return r;
}

cEntry* cNode::search(cEntry* e, cNode* r, bool isXlevel){

	bool checkedLeft;// will be used in determining what boundary to check the other side of.
	if(r == NULL) return NULL;
	cEntry* found;

	//if it is x level, determine which side to check based on x
	if(isXlevel){
		//if it is less, check to the left.
		if(e->x <= r->key->x){
			checkedLeft=true;
			//if there is no left, set the current starbucks as the found starbucks.
			if(r->left_==NULL){
				found = r->key;
			}else{//otherwise search the left
				found = search(e,r->left_,!isXlevel);
			}
		}else{// same as above, but checking the right.
			checkedLeft=false;
			if(r->right_==NULL){
				found = r->key;
			}else{
				found = search(e,r->right_,!isXlevel);
			}
		}
	}else{//otherwise check y, same procedure as x. 
		if(e->y <= r->key->y){
			checkedLeft=true;
			if(r->left_==NULL){
				found = r->key;
			}else{
				found = search(e,r->left_,!isXlevel);
			}
		}else{
			checkedLeft=false;
			if(r->right_==NULL){
				found = r->key;
			}else{
				found = search(e,r->right_,!isXlevel);
			}
		}
	}
	cEntry* current = r->key;
	//d calculated as sqrt( (x1-x2)^2 + (y1-y2)^2 )
	double dCurr= sqrt(((current->x)-(e->x))*((current->x)-(e->x))+((current->y)-(e->y))*((current->y)-(e->y)));
	double dFound= sqrt(((found->x)-(e->x))*((found->x)-(e->x))+((found->y)-(e->y))*((found->y)-(e->y)));
	//checks whether the found starbucks or the current starbucks is closer. 
	if(dCurr < dFound){
		found=current;
		dFound=dCurr;
	}
	
	bool tooClose = false;// is the boundary closer than the current starbucks location?
	//determines if too close based on x or y level
	if(isXlevel){
		if(dFound > (found->x - r->key->x)){
			tooClose=true;
		}
	}else{
		if(dFound > (found->y - r->key->y)){
			tooClose=true;
		}
	}

	if(tooClose){
		cEntry* other = r->key; // set to this entry, but will get changed when checking other side...
		//because we are close to the boundary, if we checked left, we will now check right...
		if(checkedLeft){
			//provided right is not empty, we will check it, otherwise other stays as the current entry
			if(r->right_ != NULL){
				other = search(e,r->right_,!isXlevel);
			}
		}else{// and if we checked right, we will now check left...
			if(r->left_ != NULL){
				other = search(e,r->left_,!isXlevel);
			}
		}
		double dOther= sqrt(((other->x)-(e->x))*((other->x)-(e->x))+((other->y)-(e->y))*((other->y)-(e->y)));
		//determines closest of the currently found and the closest from the other side
		if(dOther < dFound){
			found=other;
			dFound=dOther;
		}
	}
	return found;
}
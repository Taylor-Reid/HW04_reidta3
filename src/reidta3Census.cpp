
#include "reidta3Census.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;
using namespace std;

reidta3Census::reidta3Census(){
	root = new cNode(NULL);
}

void reidta3Census::build(cEntry* c, int n){
	
	vector <cEntry> data;

	for(int i = 0; i<n ; i++){
		data.push_back(c[i]);
	}
	
	//Erase one of all sets of duplicates
	for(int i = 0; i< data.size()-1; i++){
		for(int j = i+1; j<data.size();j++){
			if(abs(data[i].x-data[j].x)<=0.0001  &&  abs(data[i].y-data[j].y)<=0.0001){
				data.erase(data.begin()+i-1);
			}
		}
	}
	//randomize
	random_shuffle(data.begin(),data.end());
	//create new array with entries
	cEntry* info = new cEntry[data.size()];
	
	n=data.size();

	for(int i = 0; i<n ; i++){
		info[i]=data[i];
	}

	//form into k-d tree structure
	root->key=&info[0];
	for (int i = 1; i<n ; i++){
		//heavy lifting done by insert function of the node class.
		root->insert(&info[i],root,true);
	}
}

cEntry* reidta3Census::getNearest(double x, double y){
	cEntry* check = new cEntry;
	check->x=x;
	check->y=y;
	// search function of node classes looks for closest entry of subtree defined by root
	// returns the result to wherever it was called
	return root->search(check,root,true);
}
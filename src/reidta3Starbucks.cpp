/*
* Got help using vectors from github.com/dwyguy/HW04dwyermw
*/
#include "reidta3Starbucks.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;
using namespace std;

reidta3Starbucks::reidta3Starbucks(){
	root = new Node(NULL);
}

void reidta3Starbucks::build(Entry* c, int n){
	
	vector <Entry> data;

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
	Entry* info = new Entry[data.size()];
	
	n=data.size();

	for(int i = 0; i<n ; i++){
		info[i]=data[i];
	}

	//form into k-d tree structure
	root->key=&info[0];
	for (int i = 1; i<n ; i++){
		root->insert(&info[i],root,true);
	}
}

Entry* reidta3Starbucks::getNearest(double x, double y){
	Entry* check;
	check->x=x;
	check->y=y;
	return root->search(check,root,true);
}
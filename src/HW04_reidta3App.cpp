/**
 * @file HW04_reidta3.cpp
 * CSE 274 - Fall 2012
 * My solution for HW04 phase 2.
 *
 * @author Taylor Reid
 * @date 2012-10-29
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 *
 * @note I beleive this project satisfies all basic goals.
 *
 * @note Got help with using vectors and file I/O from github.com/dwyguy/HW04dwyermw
 *
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Cinder.h"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Starbucks.h"
#include "reidta3Starbucks.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_reidta3App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	reidta3Starbucks* starTree;
};

void HW04_reidta3App::setup()
{
	starTree = new reidta3Starbucks();

	//create input stream from t data file and setup varaibles to be used
	ifstream in("../resources/Starbucks_2006.csv");
	vector <Entry> data;
	string id;
	double d;
	char spacer;

	while(in.good()){
		//create new enty to be added to vector array
		Entry* e = new Entry;

		//gets the string identifier, which is the first item and ends with a ','
		getline(in,id,',');
		e->identifier=id;
		
		//get the x value (the first double)
		in.get();
		in >> d;
		e->x = d;

		// hop over the ',', found that if you don't do this, it doesn't work very well.. =)
		in >> spacer;

		//get the y value (second double)
		in >> d;
		e->y = d;

		//push to vector array
		data.push_back(*e);

		//cout << id << flush;
	}
	//create array from vector entries
	int n = data.size();
	Entry* starArray = new Entry[n];
	for(int i = 0; i<n ; i++){
		starArray[i]=data[i];
	}

	//use build function to create the tree structure from the array of items
	starTree->build(starArray,n);
	Entry* nearestStar;

	//find closest starbucks to given poin
	double findX = .03;
	double findY = .14;
	nearestStar = starTree->getNearest(findX,findY);
	cout << nearestStar->identifier << nearestStar->x << nearestStar->y << endl;

	//compare to brute force array search:
	Entry* closest = &starArray[0];
	Entry* current = &starArray[0];
	for(int i = 1; i<n ; i++){
		current = &starArray[i];
		double dCurr= sqrt(((current->x)-(findX))*((current->x)-(findX))+((current->y)-(findY))*((current->y)-(findY)));
		double dClosest= sqrt(((closest->x)-(findX))*((closest->x)-(findX))+((closest->y)-(findY))*((closest->y)-(findY)));
		//checks whether the found starbucks or the current starbucks is closer. 
		if(dCurr < dClosest){
			closest=current;
			dClosest=dCurr;
		}
	}


	//find closest starbucks to given poin
	findX=0.76;
	findY=0.24;
	nearestStar = starTree->getNearest(findX,findY);
	cout << nearestStar->identifier << nearestStar->x << nearestStar->y << endl;

	//compare to brute force array search:
	closest = &starArray[0];
	current = &starArray[0];
	for(int i = 1; i<n ; i++){
		current = &starArray[i];
		double dCurr= sqrt(((current->x)-(findX))*((current->x)-(findX))+((current->y)-(findY))*((current->y)-(findY)));
		double dClosest= sqrt(((closest->x)-(findX))*((closest->x)-(findX))+((closest->y)-(findY))*((closest->y)-(findY)));
		//checks whether the found starbucks or the current starbucks is closer. 
		if(dCurr < dClosest){
			closest=current;
			dClosest=dCurr;
		}
	}

}

void HW04_reidta3App::mouseDown( MouseEvent event )
{
}

void HW04_reidta3App::update()
{
}

void HW04_reidta3App::draw()
{
	 
}

CINDER_APP_BASIC( HW04_reidta3App, RendererGl )

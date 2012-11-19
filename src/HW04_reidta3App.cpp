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
 * @ going to use phase three req: A), B), G) (e&f)
 *
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Cinder.h"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Starbucks.h"
#include "reidta3Starbucks.h"
#include "Census.h"
#include "reidta3Census.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_reidta3App : public AppBasic {
  public:
	static const int appWidth=900;
	static const int appHeight=600;
	static const int textureSize=1024;

	void prepareSettings(Settings* settings);

	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	reidta3Starbucks* starTree;
	Entry* starArray;
	Entry* nearestStar;

	reidta3Census* cTree00;
	cEntry* cArray00;
	reidta3Census* cTree10;
	cEntry* cArray10;

	int frameNum;
	int itemNum;
	int itemNum00;
	int itemNum10;
	Surface* mySurface_;
	gl::Texture map1;
	gl::Texture map2;
	int x1;
	int y1;
	int max00;
	int min00;
	int max10;
	int min10;
	int offset;
	//correction factors to lign up starbucks with map
	double mx;
	double bx;
	double my;
	double by;

	int pointX;
	int pointY;
	double dubX;
	double dubY;
	int nearestX;
	int nearestY;
	
	int mapOption;
	int displayOption;
};

void HW04_reidta3App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void HW04_reidta3App::setup()
{
	//********************************** Create Starbucks Tree **********************************************
	

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
	itemNum=n;
	starArray = new Entry[n];
	for(int i = 0; i<n ; i++){
		starArray[i]=data[i];
	}
	//use build function to create the tree structure from the array of items
	starTree->build(starArray,n);

	/*find closest starbucks to given poin
	double findX = .03;
	double findY = .14;
	nearestStar = starTree->getNearest(findX,findY);
	*/

	/*
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
	}*/
	//********************************** Create Census Trees **********************************************
	//Sampe Process as starbucks tree
	cTree00 = new reidta3Census();

	//create input stream from t data file and setup varaibles to be used
	ifstream in1("../resources/Census_2000.csv");
	vector <cEntry> cdata00;

	//int extra;
	int pop1;
	max00=NULL;
	min00=NULL;

	while(in1.good()){
		cEntry* ce = new cEntry;
		//hop over the first 4 items
		for(int i =0; i < 4 ; i++){
			getline(in1,id,',');
		}

		//get the population value
		in1 >> pop1;
		ce->pop = pop1;

		// hop over the ','
		in1.get();

		//get the x value
		in1 >> d;
		ce->x = d;

		// hop over the ','
		in1.get();

		//get the x value
		in1 >> d;
		ce->y = d;

		if(max00==NULL){
			max00=pop1;
			min00=pop1;
		}else{
			if(pop1 > max00){
				max00=pop1;
			}else if(pop1 < min00){
				min00=pop1;
			}
		}

		cdata00.push_back(*ce);
	}
	n = cdata00.size();
	itemNum00=n;
	cArray00 = new cEntry[n];
	for(int i = 0; i<n ; i++){
		cArray00[i]=cdata00[i];
	}
	//cTree00->build(cArray00,n);

	//Now for the C10 data
	cTree10 = new reidta3Census();

	ifstream in2("../resources/Census_2010.csv");
	vector <cEntry> cdata10;
	
	while(in2.good()){
		cEntry* ce = new cEntry;
		
		//hop over the first 4 items
		for(int i =0; i < 4 ; i++){
			getline(in2,id,',');
		}

		//get the population value
		in2 >> pop1;
		ce->pop = pop1;

		// hop over the ','
		in2.get();

		//get the x value
		in2 >> d;
		ce->x = d;

		// hop over the ','
		in2.get();

		//get the x value
		in2 >> d;
		ce->y = d;

		if(max10==NULL){
			max10=pop1;
			min10=pop1;
		}else{
			if(pop1 > max10){
				max10=pop1;
			}else if(pop1 < min10){
				min10=pop1;
			}
		}

		cdata10.push_back(*ce);
	}
	n = cdata10.size();
	itemNum10=n;
	cArray10 = new cEntry[n];
	for(int i = 0; i<n ; i++){
		cArray10[i]=cdata10[i];
	}
	//cTree10->build(cArray10,n);


	//********************************** Graphic Section **********************************************

	frameNum=0;
	mySurface_= new Surface(textureSize,textureSize,true,SurfaceChannelOrder::RGBA);
	map1 = loadImage("../resources/mapUSA1 - Copy.png");
	map2 = loadImage("../resources/mapUSA2 - Copy.png");

	mx=1.1;
	bx=0;
	my=1.;
	by=20;

	pointX=0;
	pointY=600;
	nearestX=0;
	nearestY=600;

	mapOption=0;
	displayOption=0;

	//Get our array of pixel information
	uint8_t* dataArray = (*mySurface_).getData();
	for(int i = 0; i < textureSize*textureSize; i++){
		dataArray[4*i+0]=0;
		dataArray[4*i+1]=0;
		dataArray[4*i+2]=0;
		dataArray[4*i+3]=255;
	}
	
	//people per starbucks

}

void HW04_reidta3App::mouseDown( MouseEvent event )
{
	int mouseX=event.getX();
	int mouseY=event.getY();

	if(mouseX <= 50 && mouseY >= 550){
		mapOption=(mapOption+1)%3;
	}else if(mouseX <= 100 && mouseY >= 550){
		displayOption=(displayOption+1)%4;
	}else{
		pointX=mouseX;
		pointY=mouseY;

		//this here needs fixed
		dubX=((double(pointX)-bx)/double(mx))/appWidth;
		dubY=1-((double(pointY)-by)/double(my))/appHeight;
		nearestStar = starTree->getNearest(dubX,dubY);
		nearestX = int(((nearestStar->x)*appWidth)*mx+bx);
		nearestY = int(((1-nearestStar->y)*appHeight)*my+by);

		//x1=int(((starArray[i].x)*appWidth)*mx+bx);
		//y1=int(((1-starArray[i].y)*appHeight)*my+by);
	}


	
}

void HW04_reidta3App::update()
{
	//Get our array of pixel information
	uint8_t* dataArray = (*mySurface_).getData();



	frameNum++;
}

void HW04_reidta3App::draw()
{
	// Draws map
	gl::setMatricesWindow( getWindowSize() );
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );

	gl::color(Color8u(255,255,255));
	if(mapOption != 0){
		if(mapOption == 1){
			gl::draw(map1,cinder::Rectf(0,0,appWidth,appHeight));
		}else{
			gl::draw(map2,cinder::Rectf(0,0,appWidth,appHeight));
		}
	}

	//Draws Starbucks locations
	if(displayOption==0){
		gl::color(Color8u(255,0,0));
		for(int i = 0; i<itemNum ; i++){
			x1=int(((starArray[i].x)*appWidth)*mx+bx);
			y1=int(((1-starArray[i].y)*appHeight)*my+by);
			gl::drawSolidRect(cinder::Rectf(x1,y1,x1+1,y1+1));
		}
	//draw census 2000 information
	}else if(displayOption==1){
		for(int i = 0; i<itemNum00 ; i++){
			offset=255*(cArray00[i].pop-min00)/(5000);
			if(offset>255){
				offset=255;
			}
			gl::color(Color8u(255-offset,0+offset,0));
			x1=int(((cArray00[i].x)*appWidth)*mx+bx);
			y1=int(((1-cArray00[i].y)*appHeight)*my+by);
			gl::drawSolidRect(cinder::Rectf(x1,y1,x1+1,y1+1));
		}
	//draw census 2010 information
	}else if(displayOption==2){
		for(int i = 0; i<itemNum10 ; i++){
			offset=(255*(cArray10[i].pop-min10))/(5000);
			if(offset>255){
				offset=255;
			}
			gl::color(Color8u(255-offset,0+offset,0));
			x1=int(((cArray10[i].x)*appWidth)*mx+bx);
			y1=int(((1-cArray10[i].y)*appHeight)*my+by);
			gl::drawSolidRect(cinder::Rectf(x1,y1,x1+1,y1+1));
		}
	// census 2010 - census 2000
	}else{
		for(int i = 0; i<itemNum00 && i<itemNum10 ; i++){
			offset=128*(cArray10[i].pop-cArray00[i].pop)/(1000);
			if(offset>128){
				offset=128;
			}if(offset<-128){
				offset=-128;
			}
			gl::color(Color8u(128-offset,127+offset,0));
			x1=int(((cArray00[i].x)*appWidth)*mx+bx);
			y1=int(((1-cArray00[i].y)*appHeight)*my+by);
			gl::drawSolidRect(cinder::Rectf(x1,y1,x1+1,y1+1));
		}
	}

	//draws mouse click marker
	gl::color(Color8u(0,0,255));
	gl::drawSolidRect(cinder::Rectf(pointX-1,pointY-1,pointX+1,pointY+1));
	gl::drawSolidCircle(cinder::Vec2f(pointX+2,pointY+2),1);
	gl::drawSolidCircle(cinder::Vec2f(pointX+2,pointY-2),1);
	gl::drawSolidCircle(cinder::Vec2f(pointX-2,pointY-2),1);
	gl::drawSolidCircle(cinder::Vec2f(pointX-2,pointY+2),1);
	

	//indicate nearest starbucks
	gl::color(Color8u(0,0,255));
	gl::drawSolidRect(cinder::Rectf(nearestX+1,nearestY+1,nearestX+1+1,nearestY+1+1));
	gl::drawSolidRect(cinder::Rectf(nearestX+1,nearestY-1,nearestX+1+1,nearestY+1-1));
	gl::drawSolidRect(cinder::Rectf(nearestX-1,nearestY-1,nearestX+1-1,nearestY+1-1));
	gl::drawSolidRect(cinder::Rectf(nearestX-1,nearestY+1,nearestX+1-1,nearestY+1+1));
	gl::drawSolidRect(cinder::Rectf(nearestX+2,nearestY+2,nearestX+1+2,nearestY+1+2));
	gl::drawSolidRect(cinder::Rectf(nearestX+2,nearestY-2,nearestX+1+2,nearestY+1-2));
	gl::drawSolidRect(cinder::Rectf(nearestX-2,nearestY-2,nearestX+1-2,nearestY+1-2));
	gl::drawSolidRect(cinder::Rectf(nearestX-2,nearestY+2,nearestX+1-2,nearestY+1+2));

	//Draws the buttons
	gl::color(Color8u(150,150,150));
	gl::drawSolidRect(cinder::Rectf(0,550,50,600));
	gl::drawSolidRect(cinder::Rectf(50,550,100,600));
	
	if(mapOption==0){
		gl::color(Color8u(255,255,255));
		gl::draw(map1,cinder::Rectf(5,555,45,595));
	}else if(mapOption==1){
		gl::color(Color8u(255,255,255));
		gl::draw(map2,cinder::Rectf(5,555,45,595));
	}else{
		gl::color(Color8u(0,0,0));
		gl::drawSolidRect(cinder::Rectf(5,555,45,595));
	}
	if(displayOption==0){
		gl::color(Color8u(255,0,0));
		gl::drawSolidRect(cinder::Rectf(55,555,95,595));
	}else if(displayOption==1){
		gl::color(Color8u(0,255,0));
		gl::drawSolidRect(cinder::Rectf(55,555,95,595));
	}else if(displayOption==2){
		gl::color(Color8u(0,0,255));
		gl::drawSolidRect(cinder::Rectf(55,555,95,595));
	}else{
		gl::color(Color8u(0,0,255));
		gl::drawSolidRect(cinder::Rectf(55,555,75,595));
		gl::color(Color8u(0,255,0));
		gl::drawSolidRect(cinder::Rectf(75,555,95,595));
	}
}

CINDER_APP_BASIC( HW04_reidta3App, RendererGl )

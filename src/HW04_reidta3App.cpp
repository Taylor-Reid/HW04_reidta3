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

	ifstream in("../resources/Starbucks_2006.csv");
	vector <Entry> data;
	string id;
	double d;
	char spacer;

	while(in.good()){
		Entry* e = new Entry;

		getline(in,id,',');
		e->identifier=id;
		
		in.get();
		in >> d;
		e->x = d;

		in >> spacer;

		in >> d;
		e->y = d;

		data.push_back(*e);

		//cout << id << flush;
	}
	int n = data.size();
	Entry* starArray = new Entry[n];
	for(int i = 0; i<n ; i++){
		starArray[i]=data[i];
	}

	starTree->build(starArray,n);

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

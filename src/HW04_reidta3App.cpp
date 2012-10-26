#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Cinder.h"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Starbucks.h"
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
};

void HW04_reidta3App::setup()
{
}

void HW04_reidta3App::mouseDown( MouseEvent event )
{
}

void HW04_reidta3App::update()
{
}

void HW04_reidta3App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_reidta3App, RendererGl )

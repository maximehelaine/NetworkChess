#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NetworkChessApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NetworkChessApp::setup()
{
}

void NetworkChessApp::mouseDown( MouseEvent event )
{
}

void NetworkChessApp::update()
{
}

void NetworkChessApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( NetworkChessApp, RendererGl )

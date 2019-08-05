#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1400, 1200, OF_WINDOW);
	//ofSetupOpenGL(2160, 3840, OF_FULLSCREEN);
	ofSetupOpenGL(3000, 2000, OF_FULLSCREEN);
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

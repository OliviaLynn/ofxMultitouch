#include "ofApp.h"

//#define RUN_FULLSCREEN
//========================================================================
int main( ){
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
#ifdef RUN_FULLSCREEN
	settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN
#else
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
#endif

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();
}

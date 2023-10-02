#pragma once

#include "ofMain.h"
#include "ofxMultitouch.h"
#include "TouchGroup.h"

class ofApp : public ofBaseApp {

public:

	ofImage img;
	float imgScale;
	float lastScale;

	void setup();
	void update();
	void draw();
	void exit();

	void doCalculations();
	
	void keyPressed(int key);
	void keyReleased(int key);

	// add the touch listeners
	void touchDown(ofTouchEventArgs& touch);
	void touchMoved(ofTouchEventArgs& touch);
	void touchUp(ofTouchEventArgs& touch);

	void simulateGesture(int, int, int, int, int, int, int, int);

	void drawTouches();

};
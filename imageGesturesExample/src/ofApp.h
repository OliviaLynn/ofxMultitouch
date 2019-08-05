#pragma once

#include "ofMain.h"
#include "ofxWinTouchHook.h"
#include "TouchGroup.h"

class ofApp : public ofBaseApp {

public:

	ofImage img;
	float imgScale;
	float lastScale;

	void setup();
	void update();
	void draw();

	void doCalculations();
	
	void keyPressed(int key);
	void keyReleased(int key);

	// add the touch listeners
	void touchDown(ofTouchEventArgs& touch);
	void touchMove(ofTouchEventArgs& touch);
	void touchUp(ofTouchEventArgs& touch);

	void simulateGesture(int, int, int, int, int, int, int, int);

	void drawTouches();

};
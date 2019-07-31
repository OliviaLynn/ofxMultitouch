#pragma once

#include "ofMain.h"
#include "ofxMultitouch.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// add the touch listeners
		void touchDown(ofTouchEventArgs& touch);
		void touchMove(ofTouchEventArgs& touch);
		void touchUp(ofTouchEventArgs& touch);
		
};
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "TouchGroup.h"
#include "ofxMultitouch.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		
		void drawPixel(int x, int y, unsigned char val);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		void applyStroke();
		void setStrokeColor(int x, int y);

		// add the touch listeners
		void touchDown(ofTouchEventArgs& touch);
		void touchMoved(ofTouchEventArgs& touch);
		void touchUp(ofTouchEventArgs& touch);
		
        ofxCvContourFinder 	contourFinder;



};


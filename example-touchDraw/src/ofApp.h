#pragma once

#include "ofMain.h"
#include "ofxMultitouch.h"
#include "MeshBundle.h"

struct Path {
	ofMesh mesh;
	int id;
	ofColor clr;
};

class ofApp : public ofBaseApp{

	public:
		ofMesh mesh;
		map<int, MeshBundle> bundles;

		void setup();
		void update();
		void draw();

		ofImage grab;
		ofImage grabbing;

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseMoved(int x, int y);

		// add the touch listeners
		void touchDown(ofTouchEventArgs& touch);
		void touchMoved(ofTouchEventArgs& touch);
		void touchUp(ofTouchEventArgs& touch);
		void mouseButtonDown(ofMouseEventArgs& mouse);
		void mouseButtonUp(ofMouseEventArgs& mouse);
		
};

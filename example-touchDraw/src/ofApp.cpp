#include "ofApp.h"

ofMatrix4x4 m;
ofVec3f dragStart(0, 0, 0);
bool mouseIsDown = false;
ofVec2f mousePostion(0, 0);

// TODO clean globals
// TODO justify eschewing the mousePressed, etc functions in favor of
// our own explicitly mouse-only (no touchie) events

//--------------------------------------------------------------
void ofApp::setup(){

	m = ofMatrix4x4::newIdentityMatrix();
	
	// visual setup
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	ofLog() << "IMG LOADED: " << grab.loadImage("images/grab.png");
	ofLog() << "IMG LOADED: " << grabbing.loadImage("images/grabbing.png");

	// enable the Windows Touch Hook
	ofxMultitouch::EnableTouch();

	// add touch listeners
	ofAddListener(ofxMultitouch::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxMultitouch::touchMoved, this, &ofApp::touchMove);
	ofAddListener(ofxMultitouch::touchUp, this, &ofApp::touchUp);
	ofAddListener(ofxMultitouch::mouseButtonDown, this, &ofApp::mouseButtonDown);
	ofAddListener(ofxMultitouch::mouseButtonUp, this, &ofApp::mouseButtonUp);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofMultMatrix(m);

	// Draw the touch paths
	if (!bundles.empty()) {
		ofEnableSmoothing();
		ofSetLineWidth(1.0);
		map<int, MeshBundle>::iterator it;
		for (it = bundles.begin(); it != bundles.end(); ++it) {
			(it->second).mesh.draw();
		}
	}

	ofPopMatrix();

	// Display the frame rate
	ofDrawBitmapString(ofToString(roundf(ofGetFrameRate())), 100, 100);
	if (grab.isAllocated()) {
		if (mouseIsDown) {
			grabbing.draw(mousePostion);
		}
		else {
			//grab.draw(mousePostion);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Clear everything
	if (key == ' ') {
		bundles.clear();
	}
	// Reset the panning
	else if (key == '0') {
		m.set(ofMatrix4x4::newIdentityMatrix());
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (mouseIsDown) {
		m.translate(ofVec3f(x, y, 0) - dragStart);
		dragStart.set(x, y, 0);
		mousePostion.set(x, y);
	}
}

void ofApp::mouseMoved(int x, int y) {
	if (mouseIsDown) {
		//mousePostion.set(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseButtonDown(ofMouseEventArgs & mouse) {
	mouseIsDown = true;
	ofLog() << "mouse is down? " << mouseIsDown;
}

//--------------------------------------------------------------
void ofApp::mouseButtonUp(ofMouseEventArgs & mouse) {
	mouseIsDown = false;
	ofLog() << "mouse is down? " << mouseIsDown;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	dragStart.set(x, y, 0);
	mousePostion.set(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch) {
	// Create a new path to represent this new touch
	// Give it the touch's id, then add this first x,y point to the path's mesh
	MeshBundle newBundle(touch.id);
	bundles[touch.id] = newBundle;
}

//--------------------------------------------------------------
void ofApp::touchMove(ofTouchEventArgs & touch) {
	// Optional feature, just for fun
	//		false: example will function as normal, one ofMesh per touch
	//		true: creates a web between each current touch, all one ofMesh
	bool toggleWeb = false;

	// Find the path whose id matches our touch's id, 
	// then add a new point to that path
	ofVec3f newPoint(touch.x, touch.y);
	newPoint -= m.getTranslation();
	if (!bundles.empty()) {
		map<int, MeshBundle>::iterator it;
		for (it = bundles.begin(); it != bundles.end(); ++it) {
			if (toggleWeb || ((it->second.id) == touch.id)) {
				(it->second).mesh.addVertex(newPoint);
				(it->second).mesh.addColor(it->second.clr);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch) {
}

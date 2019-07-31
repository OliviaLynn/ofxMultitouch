#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// visual setup
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();

	// enable the Windows Touch Hook
	ofxMultitouch::EnableTouch();

	// add touch listeners
	ofAddListener(ofxMultitouch::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxMultitouch::touchMoved, this, &ofApp::touchMove);
	ofAddListener(ofxMultitouch::touchUp, this, &ofApp::touchUp);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw the touch paths
	if (!bundles.empty()) {
		ofEnableSmoothing();
		ofSetLineWidth(1.0);
		map<int, MeshBundle>::iterator it;
		for (it = bundles.begin(); it != bundles.end(); ++it) {
			(it->second).mesh.draw();
		}
	}

	// Display the frame rate
	ofDrawBitmapString(ofToString(roundf(ofGetFrameRate())), 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Clear everything
	if (key == ' ') {
		bundles.clear();
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

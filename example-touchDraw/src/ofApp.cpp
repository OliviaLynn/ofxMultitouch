#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

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
	if (!bundles.empty()) {
		ofEnableSmoothing();
		ofSetLineWidth(1.0);
		map<int, MeshBundle>::iterator it;
		for (it = bundles.begin(); it != bundles.end(); ++it) {
			(it->second).mesh.draw();
		}
	}

	ofDrawBitmapString(ofToString(roundf(ofGetFrameRate())), 100, 100);

	/*	CIRCLES
	list<ofTouchEventArgs> ::iterator it;
	for (it = touches.begin(); it != touches.end(); ++it) {
		ofDrawCircle((*it).x, (*it).y, 60);
	}*/

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
	//activeBundles.push_back(newBundle);
	bundles[touch.id] = newBundle;

	//	CIRCLES
	//touches.push_back(touch);
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
	/*	CIRCLES
	std::list <ofTouchEventArgs> ::iterator it;
	for (it = touches.begin(); it != touches.end(); ++it) {
		if (it->id == touch.id) {
			*it = touch;
		}
	}*/
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch) {

	//	CIRCLES
	//ofTouchEventArgs touchToRemove;
	//std::list <ofTouchEventArgs> ::iterator it;
	//for (it = touches.begin(); it != touches.end(); ++it) {
	//	if (it->id == touch.id) {
	//		//ofLog() << "[" << it->id << "] !! ";
	//		touchToRemove = *it;
	//	}
	//}
	//touches.remove(touchToRemove);
}

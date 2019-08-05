#include "ofApp.h"
// w 1.30-7
// h 3-8:40, 11:40-12:30

TouchGroup tG;

ofMatrix4x4 preM, M;

ofVec2f offsetM;

float scale;

int counter = 0;

int lockoutTimer = 0;
int lockoutDuration = 10;

void ofApp::setup() {

	ofBackground(140);
	ofSetFrameRate(60);
	ofHideCursor();

	preM = ofMatrix4x4::newIdentityMatrix();
	M = ofMatrix4x4::newIdentityMatrix();

	scale = 1;

	//doCalculations();

	preM = ofMatrix4x4::newIdentityMatrix();
	M = ofMatrix4x4::newIdentityMatrix();

	// enable the Windows Touch Hook
	ofxWinTouchHook::EnableTouch();

	// add touch listeners
	ofAddListener(ofxWinTouchHook::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxWinTouchHook::touchMoved, this, &ofApp::touchMove);
	ofAddListener(ofxWinTouchHook::touchUp, this, &ofApp::touchUp);

	// Load the image
	img.load("images/turtle.jpeg");


}

void ofApp::update() {
	if (lockoutTimer > 0) {
		lockoutTimer -= 1;
	}

}

void ofApp::draw() {

	ofSetColor(255);

	ofPushMatrix();
	ofMultMatrix(M);
	img.draw(0, 0);
	ofPopMatrix();

	drawTouches();
}

void ofApp::drawTouches() {
	int rad = 60;

	// Prev touches
	ofSetColor(255, 0, 0, 200); // red
	//ofDrawLine(tG.prevTouches[0], tG.prevTouches[1]);
	ofDrawCircle(tG.prevTouches[0], rad);
	ofSetColor(255, 50, 50, 200); // light red
	ofDrawCircle(tG.prevTouches[1], rad);
	ofDrawCircle(tG.prevTouches[2], rad);

	// Touches
	ofSetColor(0, 0, 255, 200); // blue
	//ofDrawLine(tG.touches[0], tG.touches[1]);
	ofDrawCircle(tG.touches[0], rad);
	ofSetColor(0, 50, 255, 200); // light blue
	ofDrawCircle(tG.touches[1], rad);
	ofDrawCircle(tG.touches[2], rad);

	// Other
	ofSetColor(255, 255, 255);
	ofDrawCircle(tG.initialLocation, rad);
}

void ofApp::keyPressed(int key) {
	if (key == '1') {
		ofLog() << "------> 1";
		simulateGesture(
			0, 100,
			200, 100,
			0, 100,
			141.4, 241.4
		);
	}
	else if (key == '2') {
		ofLog() << "------> 2";

		simulateGesture(
			0, 100, 
			200, 100,
			100, 100,
			300, 100
		);
	}
	else if (key == '3') {
		ofLog() << "------> 3";
		simulateGesture(
			0, 100,
			141.4, 241.4,
			0, 100,
			200, 100
		);
	}
	else if (key == ' ') {
		ofLog() << "--> SPACE";
		preM = ofMatrix4x4::newIdentityMatrix();
		M = ofMatrix4x4::newIdentityMatrix();
		simulateGesture(
			0, 100,
			200, 100,
			0, 100,
			200, 100
		);
	}
}

void ofApp::simulateGesture(int p0x, int p0y, int p1x, int p1y, int t0x, int t0y, int t1x, int t1y) {
	
	tG.prevTouches[0].set(p0x, p0y);
	tG.prevTouches[1].set(p1x, p1y);
	tG.touches[0].set(t0x, t0y);
	tG.touches[1].set(t1x, t1y);

	// onboarding touches to tG
	ofVec2f v(1, 0);
	tG.initialAngle = v.angle(tG.prevTouches[1] - tG.prevTouches[0]);
	tG.currentAngle = v.angle(tG.touches[1] - tG.touches[0]);

	tG.initialDistance = tG.prevTouches[0].distance(tG.prevTouches[1]);
	tG.currentDistance = tG.touches[0].distance(tG.touches[1]);

	tG.initialLocation = tG.prevTouches[0].getMiddle(tG.prevTouches[1]);
	tG.currentLocation = tG.touches[0].getMiddle(tG.touches[1]);

	// doing calcs

	ofVec2f pivot = tG.initialLocation;

	ofVec2f deltaLocation(tG.currentLocation - tG.initialLocation);
	float deltaDistance = (tG.currentDistance / tG.initialDistance);
	float deltaAngle = tG.currentAngle - tG.initialAngle;

	M = preM;

	// Get the existing transformations we need to apply to our translations:
	ofVec3f trn;
	ofQuaternion rot;
	ofVec3f scl;
	ofQuaternion so;
	M.decompose(trn, rot, scl, so);
	ofLog() << "Orig Translation: " << roundf(trn.x);

	// REMEMBER, READ BOTTOM TO TOP

	M.preMultTranslate(deltaLocation.rotate(-rot.getEuler().z));
	M.preMultTranslate (( (pivot - trn)/scl).rotate(-rot.getEuler().z));
	M.preMultRotate(ofQuaternion(deltaAngle, ofVec3f(0, 0, 1)));
	M.preMultScale	   (ofVec2f (deltaDistance, deltaDistance));
	M.preMultTranslate ((-(pivot - trn)/scl).rotate(-rot.getEuler().z));

	preM = M;
}

void ofApp::keyReleased(int key) {

}

void ofApp::touchDown(ofTouchEventArgs & touch) {
	tG.AddTouch(touch);

	ofLog() << tG.numTouches << " touch(es)";

	if (tG.numTouches == 2) {
		ofLog() << tG.numTouches << " touch(es)";
		doCalculations();

	}
	else if (tG.numTouches == 3) {
		ofLog() << tG.numTouches << " touch(es)";
		doCalculations();

	}
}

void ofApp::touchMove(ofTouchEventArgs & touch) {
	if (lockoutTimer == 0) {
		tG.MoveTouch(touch);
		doCalculations();
	}
}

void ofApp::touchUp(ofTouchEventArgs & touch) {
	if (tG.numTouches == 2) {
		preM = M;
	}
	else if (tG.numTouches == 3) {
		preM = M;
		lockoutTimer = lockoutDuration;
	}

	tG.RemoveTouch(touch);
	ofLog() << tG.numTouches << " touch(es)";
}

void ofApp::doCalculations() {


	if (tG.numTouches >= 2) {
	//if (true) {

		ofVec2f pivot = tG.initialLocation;

		ofVec2f deltaLocation(tG.currentLocation - tG.initialLocation);
		float deltaDistance = (tG.currentDistance / tG.initialDistance);

		M = preM;

		// Get the existing transformations we need to apply to our translations:
		ofVec3f trn;
		ofQuaternion rot;
		ofVec3f scl;
		ofQuaternion so;
		M.decompose(trn, rot, scl, so);

		// REMEMBER: READ THESE FROM BOTTOM TO TOP

		M.preMultTranslate(deltaLocation/scl);
		M.preMultTranslate(((pivot - trn) / scl));
		M.preMultScale(ofVec2f(deltaDistance, deltaDistance));
		M.preMultTranslate((-(pivot - trn) / scl));

		// Clamping
		// RN: a bit of a jump/wiggle as it transitions between bigger than the screen and smaller than 
		// the screen. TODO decide how to resolve this

		/*
		M.decompose(trn, rot, scl, so);
		if (img.getWidth() * scl.x < ofGetWidth()) {
			if (trn.x < 0) {
				M.setTranslation(ofVec3f(0, trn.y, trn.z));
			}
			else if (trn.x > ofGetWidth() - (img.getWidth() * scl.x)) {
				M.setTranslation(ofVec3f(ofGetWidth() - (img.getWidth() * scl.x), trn.y, trn.z));
			}
		}
		M.decompose(trn, rot, scl, so);
		if (img.getHeight() * scl.y < ofGetHeight()) {
			if (trn.y < 0) {
				M.setTranslation(ofVec3f(trn.x, 0, trn.z));
			}
			else if (trn.y > ofGetHeight() - (img.getHeight() * scl.y)) {
				M.setTranslation(ofVec3f(trn.x, ofGetHeight() - (img.getHeight() * scl.y), trn.z));
			}
		}
		*/

	}
}


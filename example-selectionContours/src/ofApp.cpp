#include "ofApp.h"

ofxCvGrayscaleImage whiteStroke, bigWhiteStroke;
ofxCvGrayscaleImage blackStroke, bigBlackStroke;
ofxCvGrayscaleImage preStroke, bigPreStroke;
ofxCvGrayscaleImage allTogether, bigAllTogether;
unsigned char * PIX_WHITE;
unsigned char * PIX_BLACK;
unsigned char * PIX_PRE;
//unsigned char * PIX_ALL;
cv::Mat PIX_ALL;

/*
int SCALE = 25;
int PWIDTH = 20;
int PHEIGHT = 20;
*/
int SCALE = 125;
int PWIDTH = 4;
int PHEIGHT = 4;


int THRESHOLD = 70;
int LINE_WEIGHT = 4;
int MAX_BLOBS = 16;

unsigned char currentStrokeColor = 0;


//--------------------------------------------------------------
void ofApp::setup(){

	// enable the Windows Touch Hook
	ofxMultitouch::EnableTouch();

	// add touch listeners
	
	ofAddListener(ofxMultitouch::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxMultitouch::touchMoved, this, &ofApp::touchMove);
	ofAddListener(ofxMultitouch::touchUp, this, &ofApp::touchUp);

	PIX_WHITE = new unsigned char[PWIDTH * PHEIGHT];
	PIX_BLACK = new unsigned char[PWIDTH * PHEIGHT];
	PIX_PRE = new unsigned char[PWIDTH * PHEIGHT];
	//PIX_ALL = new unsigned char[PWIDTH * PHEIGHT];
	PIX_ALL.create(PHEIGHT, PWIDTH, CV_8UC1(0));

	for (int i = 0; i < PWIDTH*PHEIGHT; i++) {
		*(PIX_WHITE + i) = 0;
		*(PIX_BLACK + i) = 255;
		*(PIX_PRE + i) = 0;
		//*(PIX_ALL + i) = 0;
	}
	/*
	whiteStroke = ofxCvGrayscaleImage();
	blackStroke = ofxCvGrayscaleImage();
	preStroke = ofxCvGrayscaleImage();
	allTogether = ofxCvGrayscaleImage();
	*/
	whiteStroke.setFromPixels(PIX_WHITE, PWIDTH, PHEIGHT);
	blackStroke.setFromPixels(PIX_BLACK, PWIDTH, PHEIGHT);
	preStroke.setFromPixels(  PIX_PRE,   PWIDTH, PHEIGHT);
	//allTogether.setFromPixels(PIX_ALL, PWIDTH, PHEIGHT);
	ofxCv::toOf(PIX_ALL, &allTogether);

	bigWhiteStroke.allocate(PWIDTH*SCALE, PHEIGHT*SCALE);
	bigBlackStroke.allocate(PWIDTH*SCALE, PHEIGHT*SCALE);
	bigPreStroke.allocate(PWIDTH*SCALE, PHEIGHT*SCALE);
	bigAllTogether.allocate(PWIDTH*SCALE, PHEIGHT*SCALE);

}

//--------------------------------------------------------------
void ofApp::update(){

	for (int i = 0; i < PWIDTH*PHEIGHT; i++) {
		*(PIX_ALL + i) = *(PIX_WHITE + i) | *(PIX_PRE + i);
		*(PIX_ALL + i) = *(PIX_ALL + i) & *(PIX_BLACK + i);
	}

	whiteStroke.setFromPixels(PIX_WHITE, PWIDTH, PHEIGHT);
	blackStroke.setFromPixels(PIX_BLACK, PWIDTH, PHEIGHT);
	preStroke.setFromPixels(PIX_PRE, PWIDTH, PHEIGHT);
	allTogether.setFromPixels(PIX_ALL, PWIDTH, PHEIGHT);

	/*
	whiteStroke.contrastStretch();
	blackStroke.contrastStretch();
	preStroke.contrastStretch();
	allTogether.contrastStretch();
	*/

	bigWhiteStroke.scaleIntoMe(whiteStroke);
	bigBlackStroke.scaleIntoMe(blackStroke);
	bigPreStroke.scaleIntoMe(preStroke);
	bigAllTogether.scaleIntoMe(allTogether);

	contourFinder.findContours(bigAllTogether, 0, (SCALE*PWIDTH * SCALE*PHEIGHT), MAX_BLOBS, true);	// find holes

	

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100);
	ofSetLineWidth(LINE_WEIGHT);

	ofSetColor(255);
	bigAllTogether.draw(0, 0);

	ofSetColor(55, 55, 255);
	bigBlackStroke.draw(PWIDTH*SCALE, 0);

	ofSetColor(255, 255, 55);
	bigPreStroke.draw(0, PHEIGHT*SCALE);

	ofSetColor(55, 255, 255);
	bigWhiteStroke.draw(PWIDTH*SCALE, PHEIGHT*SCALE);

	ofSetColor(255);
	contourFinder.draw(0,0);
/*
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 600);*/
	


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	switch (key){
		case ' ':
			applyStroke();
			break;
		case '+':
			break;
		case '-':
			break;
		case '1':

			break;
	}
}

//--------------------------------------------------------------
void ofApp::setStrokeColor(int x, int y) {
	int px = x / SCALE;
	int py = y / SCALE;
	currentStrokeColor = ~(*(PIX_ALL + (PWIDTH*py) + px));
	ofLog() << "Current Color: " << (int)(*(PIX_ALL + (PWIDTH*py) + px));
	ofLog() << "Current Stroke Color: " << (int)currentStrokeColor;
}

//--------------------------------------------------------------
void ofApp::drawPixel(int x, int y, unsigned char val) {
	int px = x / SCALE;
	int py = y / SCALE;
	
	if (px < 0 || py < 0) {
		ofLog() << "Out of bounds!";
	}
	else if (px >= PWIDTH || py >= PHEIGHT) { 
		ofLog() << "Out of bounds!";
	}
	else {
		if (val == 0) {
			*(PIX_BLACK + (PWIDTH*py) + px) = val;
		}
		else if (val == 255) {
			*(PIX_WHITE + (PWIDTH*py) + px) = val;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//if (button == OF_MOUSE_BUTTON_LEFT) {
	//	drawPixel(x, y, currentStrokeColor);
	//}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//setStrokeColor(x, y);
	//if (button == OF_MOUSE_BUTTON_LEFT) {
	//	drawPixel(x, y, currentStrokeColor);
	//}
}


void ofApp::touchDown(ofTouchEventArgs & touch) {
	//tG.AddTouch(touch);
	ofLog() << "TOUCH DOWN";
	setStrokeColor(touch.x, touch.y);
	drawPixel(touch.x, touch.y, currentStrokeColor);
}
void ofApp::touchMove(ofTouchEventArgs & touch) {
	drawPixel(touch.x, touch.y, currentStrokeColor);
}
void ofApp::touchUp(ofTouchEventArgs & touch) {
	applyStroke();
}

void ofApp::applyStroke() {
	for (int i = 0; i < PWIDTH*PHEIGHT; i++) {
		*(PIX_PRE + i) = *(PIX_WHITE + i) | *(PIX_PRE + i);
		*(PIX_PRE + i) = *(PIX_PRE + i) & *(PIX_BLACK + i);
		*(PIX_WHITE + i) = 0;
		*(PIX_BLACK + i) = 255;
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

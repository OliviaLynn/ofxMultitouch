#pragma once

#include "ofxWinTouchHook.h"

class TouchGroup
{
public:

	ofVec2f touches[3];
	ofVec2f prevTouches[3];
	int touchId[3];
	int numTouches;
	ofVec2f pivot;

	float initialDistance;
	float currentDistance;
	ofVec2f initialLocation;
	ofVec2f currentLocation;
	float initialAngle;
	float currentAngle;

	TouchGroup();
	~TouchGroup();

	void AddTouch(ofTouchEventArgs & touch);
	void RemoveTouch(ofTouchEventArgs & touch);
	void MoveTouch(ofTouchEventArgs & touch);
	void DrawTouches();

	void moveTouchUpdateCalcs();

	ofVec2f GetTouchLocation();
};


#include "TouchGroup.h"

// TODO macros/enum for numTouches==0 etc

// TODO add in grace period of a second or whatever time to prevent zooming while ending/starting a 
// three-finger pan

TouchGroup::TouchGroup() {

	// Tracking current touch locations
	numTouches = 0;
	touches[0] = ofVec2f(0, 0);
	touches[1] = ofVec2f(0, 0);
	touches[2] = ofVec2f(0, 0);
	prevTouches[0] = ofVec2f(0, 0);
	prevTouches[1] = ofVec2f(0, 0);
	prevTouches[3] = ofVec2f(0, 0);

	   

}

TouchGroup::~TouchGroup() {

}

void TouchGroup::AddTouch(ofTouchEventArgs & touch) {
	if (numTouches == 0) {
		touches[0].set(touch.x, touch.y);
		touches[1].set(touch.x+1, touch.y+1);
		prevTouches[0].set(touches[0]);
		prevTouches[1].set(touches[1]);
		touchId[0] = touch.id;
		numTouches++;
	}
	else if (numTouches == 1) {
		touches[1].set(touch.x, touch.y);
		prevTouches[1].set(touches[1]);
		touchId[1] = touch.id;
		numTouches++;

		// Two touches: zoom

		initialDistance = touches[0].distance(touches[1]);
		currentDistance = touches[0].distance(touches[1]);
	}
	else if (numTouches == 2) {
		touches[2].set(touch.x, touch.y);
		prevTouches[2].set(touches[2]);
		touchId[2] = touch.id;
		numTouches++;

		// Three touches: pan

		initialLocation = GetTouchLocation(); // touches[0].getMiddle(touches[1]);
		currentLocation = GetTouchLocation(); // touches[0].getMiddle(touches[1]);

	}
}

void TouchGroup::MoveTouch(ofTouchEventArgs & touch) {

	// TODO maybe generalize this to update any touch, based on matching touch ID?
	// Something in this isn't working

	if (numTouches == 1) {
		prevTouches[0].set(touches[0]);
		prevTouches[1].set(touches[1]);
		touches[0].set(touch.x, touch.y);
		touches[1].set(touch.x, touch.y);
	}
	else if (numTouches == 2) {
		if (touch.id == touchId[0]) {
			prevTouches[0].set(touches[0]);
			touches[0].set(touch.x, touch.y);
		}
		else {
			prevTouches[1].set(touches[1]);
			touches[1].set(touch.x, touch.y);
		}

		moveTouchUpdateCalcs();

	}
	else if (numTouches == 3) {
		// TODO something more elegant
		if (touch.id == touchId[0]) {
			prevTouches[0].set(touches[0]);
			touches[0].set(touch.x, touch.y);
		}
		else if (touch.id == touchId[1]) {
			prevTouches[1].set(touches[1]);
			touches[1].set(touch.x, touch.y);
		}
		else {
			prevTouches[2].set(touches[2]);
			touches[2].set(touch.x, touch.y);
		}

		moveTouchUpdateCalcs();

	}
}

void TouchGroup::moveTouchUpdateCalcs() {
	if (numTouches == 2) {
		currentDistance = touches[0].distance(touches[1]);
	}
	else if (numTouches == 3) {
		currentLocation = GetTouchLocation(); //touches[0].getMiddle(touches[1]);
	}
}

void TouchGroup::RemoveTouch(ofTouchEventArgs & touch) {
	if (numTouches == 1) {
		numTouches--;
	}
	else if (numTouches == 2) {
		prevTouches[0].set(touches[0]);
		prevTouches[1].set(touches[1]);
		if (touch.id == touchId[0]) {
			touches[0] = touches[1];
		}
		numTouches--;
	}
	else if (numTouches == 3) {
		if (touch.id == touchId[0]) {
			touches[0] = touches[2];
		}
		if (touch.id == touchId[1]) {
			touches[1] = touches[2];
		}
		prevTouches[0].set(touches[0]);
		prevTouches[1].set(touches[1]);
		prevTouches[2].set(touches[2]); // TODO is this right?
		numTouches--;
	}
}

ofVec2f TouchGroup::GetTouchLocation() {
	ofVec2f loc(0, 0);
	loc.x = (touches[0].x + touches[1].x + touches[2].x)/3;
	loc.y = (touches[0].y + touches[1].y + touches[2].y)/3;
	return loc;
}

void TouchGroup::DrawTouches() {
}


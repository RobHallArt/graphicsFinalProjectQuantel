#include "animator.h"

animator::animator(float _fadeTime, int _loopMode, float _low, float _high, char _activateKey) {
	fadeTime = _fadeTime;
	loopMode = _loopMode;
	activateKey = _activateKey;
	low = _low;
	high = _high;
}

animator::animator(float _fadeTime, int _loopMode, char _activateKey) {
	fadeTime = _fadeTime;
	loopMode = _loopMode;
	activateKey = _activateKey;
	low = 0;
	high = 1;
}

void animator::update() {
	if (ofGetElapsedTimeMillis() - startTime >= fadeTime || ofGetElapsedTimeMillis() - startTime < 0) {
		isAnimating = FALSE;
		loopModeDirection = !loopModeDirection;
	}
	if (isAnimating && loopMode == 1) {
		value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, low, high);
	}
	else if (isAnimating && loopMode == 2) {
		if (loopModeDirection) {
			value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, low, high);
		}
		else {
			value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, high, low);
		}
	}
}

void animator::trigger(char _keyPressed) {

}
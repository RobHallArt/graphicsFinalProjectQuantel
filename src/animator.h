#pragma once
#include "ofMain.h"

class animator {
	public :

		char activateKey;
		float fadeTime;
		int loopMode;
		float low;
		float high;
		float value;
		float startTime;
		bool isAnimating;
		bool loopModeDirection;

		animator(float _fadeTime, int _loopMode, float _low, float _high, char _activateKey);
		animator(float _fadeTime, int _loopMode, char _activateKey);

		void update();
		void trigger(char _keyPressed);
		
};
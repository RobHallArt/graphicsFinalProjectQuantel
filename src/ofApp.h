#pragma once

#include "ofMain.h"
#include "animator.h"
using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int mode;
		
		ofVideoGrabber vidGrabber;
		ofVideoGrabber vidGrabber2;

		ofPlanePrimitive plane;

		ofPlanePrimitive plane2;

		ofPlanePrimitive plane3;

		ofVboMesh deformPlane;
		ofCamera cam;


		ofLight pointLight;
		ofLight pointLight2;
		ofLight pointLight3;
		ofMaterial material;
		animator anim1{ 2000,2,0,255,'g' };
		animator anim2{ 2000,2,5,0,'g' };
		

		ofShader surfaceShader;
		vec3 zoomLevel;

		vec4 matAmbient;
		vec4 matDiffuse;
		vec4 matSpecular;
		float matShininess;
		vec4 lightPosition;
		vec4 lightColor;
};

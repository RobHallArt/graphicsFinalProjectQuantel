#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofDisableArbTex();
	vidGrabber.setup(640, 480, true);

	plane.set(ofGetWidth(),ofGetHeight());
	plane.setResolution(20, 20);
	plane.resizeToTexture(vidGrabber.getTexture(), .5);

	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(1, 1, 1));
	pointLight.setSpecularColor(ofFloatColor(1, 1, 1));

	pointLight2.setDiffuseColor(ofFloatColor(1, 1, 1));
	pointLight2.setSpecularColor(ofFloatColor(1, 1, 1));

	pointLight3.setDiffuseColor(ofFloatColor(1, 1, 1));
	pointLight3.setSpecularColor(ofFloatColor(1, 1, 1));


	material.setShininess(120);
	material.setSpecularColor(ofColor(255, 255, 255, 255));
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	pointLight.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight() / 2, 500);
	pointLight2.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
		ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

	pointLight3.setPosition(
		cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
		sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
		cos(ofGetElapsedTimef()*.2) * ofGetWidth()
	);

	*/


	pointLight.setPosition(0,0, 500);
	pointLight2.setPosition(0,0, -300);
	pointLight3.setPosition(0, 0, 0);

	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
	cam.begin();

	ofEnableDepthTest();

	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	pointLight3.enable();

	vidGrabber.getTexture().bind();

	deformPlane = plane.getMesh();
	// x = columns, y = rows //
	ofVec3f planeDims = plane.getResolution();
	float planeAngleX = ofGetElapsedTimef()*1.5;
	float planeAngleInc = 10.f / (float)planeDims.x;
	int PDX = planeDims.x;
	ofVec3f vert;

	for (size_t i = 0; i < deformPlane.getNumIndices(); i++) {
		// it is simpler than I imagined, its just cos over the whole thing.
		//planeAngleX += planeAngleInc;
		int ii = deformPlane.getIndex(i);
		vert = deformPlane.getVertex(ii);
		//vert.z += cos(planeAngleX) * 15 + 200;
		// so we have i%PDX which is the x position
		int help  = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 100)+1;
		vert.z = i % help;
		deformPlane.setVertex(ii, vert);
	}

	ofRotateX(ofGetFrameNum()*0.05);
	material.begin();
	ofFill();
	plane.transformGL();
	
	deformPlane.draw();
	plane.restoreTransformGL();
	material.end();

	vidGrabber.getTexture().unbind();

	ofDisableDepthTest();

	ofFill();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
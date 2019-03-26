#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	mode = 1;
	
	ofSetVerticalSync(true);
	ofDisableArbTex();
	vidGrabber2.listDevices();
	vidGrabber.setDeviceID(1);
	vidGrabber.setup(640, 480, true);
	vidGrabber2.setDeviceID(2);
	vidGrabber2.setup(640, 480, true);

	
	
	if (mode == 0) {
		plane.set(ofGetWidth(), ofGetHeight());
		plane.setResolution(20, 20);
		plane.resizeToTexture(vidGrabber.getTexture(), .5);
		plane.setMode(OF_PRIMITIVE_TRIANGLES);
		plane.setUseVbo(TRUE);

		plane2.set(ofGetWidth(), ofGetHeight());
		plane2.setResolution(20, 20);
		plane2.resizeToTexture(vidGrabber2.getTexture(), .5);
		plane2.setMode(OF_PRIMITIVE_TRIANGLES);
		plane2.setUseVbo(TRUE);

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
	else if (mode == 1) {
		surfaceShader.load("julia");
		zoomLevel = vec3(0, 0, 4.0);
		matAmbient = vec4(0.1f, 0.1f, 0.2f, 1.0f);
		matDiffuse = vec4(0.2f, 0.5f, 0.7f, 1.0f);
		matSpecular = vec4(3.5f, 4.0f, 5.0f, 1.0f);
		matShininess = 500.0f;
		lightPosition = vec4(10.0f, 10.0f, 20.0f, 1.0f);
		lightColor = vec4(1.0f, 1.0f, 0.8f, 1.0f);
	}

}

//--------------------------------------------------------------
void ofApp::update() {
	
	if (mode == 0) {
	pointLight.setPosition(0, 0, 500);
	pointLight2.setPosition(0, 0, -300);
	pointLight3.setPosition(0, 0, 0);
	}
	
	vidGrabber.update();
	vidGrabber2.update();
	anim1.update();
	anim2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	if (mode == 0) {
		cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
		cam.begin();

		ofEnableDepthTest();

		ofEnableLighting();
		pointLight.enable();
		pointLight2.enable();
		pointLight3.enable();

		vidGrabber2.getTexture().bind();
		ofPushMatrix();
		ofTranslate(0, 0, -10);
		ofScale(3.5);

		plane2.draw();


		ofPopMatrix();
		vidGrabber2.getTexture().unbind();

		vidGrabber.getTexture().bind();

		deformPlane = plane.getMesh();
		// x = columns, y = rows //
		ofVec3f planeDims = plane.getResolution();
		float planeAngleX = ofGetElapsedTimef()*1.5;
		float planeAngleInc = 10.f / (float)planeDims.x;
		int PDX = planeDims.x;
		ofVec3f vert;
		//deformPlane.get
		for (int i = 0; i < deformPlane.getNumIndices(); i++) {
			// it is simpler than I imagined, its just cos over the whole thing.
			//planeAngleX += planeAngleInc;
			int ii = deformPlane.getIndex(i);
			vert = deformPlane.getVertex(ii);
			//vert.z += cos(planeAngleX) * 15 + 200;
			// so we have i%PDX which is the x position
			float help = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 10);
			float help2 = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 0.01);

			//vert.z = (ii % PDX)*help*10;

			//vert.z += sin((ofGetElapsedTimeMillis()*help2)+(ii % PDX))*help;
			vert.y -= sin((ofGetElapsedTimeMillis()*0.01) + (ii % PDX))*anim2.value;
			deformPlane.setVertex(ii, vert);
		}
		ofScale(3.5);

		//ofRotateX(ofGetFrameNum()*0.2);
		//material.begin();
		ofPushStyle();
		//ofSetColor(255, 255, 255, ofMap(ofGetMouseX(), 0, ofGetWidth(), 255, 0));
		ofSetColor(255, 255, 255, anim1.value);
		ofFill();
		plane.transformGL();



		deformPlane.draw();




		//deformPlane.drawWireframe();
		plane.restoreTransformGL();
		//material.end();

		vidGrabber.getTexture().unbind();

		ofDisableDepthTest();

		ofFill();
		ofPopStyle();

		cam.end();
	}
	else if (mode == 1) {
		vidGrabber2.getTexture().bind();

		surfaceShader.begin();
		surfaceShader.setUniform4f("matAmbient", matAmbient);
		surfaceShader.setUniform4f("matDiffuse", matDiffuse);
		surfaceShader.setUniform4f("matSpecular", matSpecular);
		surfaceShader.setUniform1f("matShininess", matShininess);
		surfaceShader.setUniform4f("lightPosition", lightPosition);
		surfaceShader.setUniform4f("lightColor", lightColor);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		surfaceShader.end();

		vidGrabber2.getTexture().unbind();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	anim1.trigger(key);
	anim2.trigger(key);
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
	if (button == 0) {
		zoomLevel.x += ofMap(x, 0, ofGetWidth(), -0.1, 0.1);
		zoomLevel.y += ofMap(y, 0, ofGetHeight(), -0.1, 0.1);
		zoomLevel.z += 0.1;
	}

	if (button == 2) {
		zoomLevel.x -= ofMap(x, 0, ofGetWidth(), -0.1, 0.1);
		zoomLevel.y -= ofMap(y, 0, ofGetHeight(), -0.1, 0.1);
		zoomLevel.z -= 0.1;
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

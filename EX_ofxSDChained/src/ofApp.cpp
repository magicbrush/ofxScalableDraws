#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	I.reset(new ofImage);
	I->loadImage("Button.png");

	IBack.reset(new ofImage);
	IBack->loadImage("ButtonBack.png");

	IFront.reset(new ofImage);
	IFront->loadImage("ButtonFront.png");

	ofxSDChained::TransformParams TBack(0,0,1.2f,1.2f);
	ofxSDChained::Margin MBack;
	ofxSDChained::TransformParams TFront(0,0,0.618f,0.618f);
	ofxSDChained::Margin MFront;	
	S.reset(new ofxSDChained(I,IBack,TBack,MBack,IFront,TFront,MFront));

	RDisp = ofRectangle(0,0,100,100);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	S->draw(RDisp.x,RDisp.y,RDisp.width,RDisp.height);
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
	RDisp.width = x - RDisp.x;
	RDisp.height = y - RDisp.y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	RDisp.x = x;
	RDisp.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

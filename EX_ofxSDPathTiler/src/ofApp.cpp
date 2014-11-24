#include "ofApp.h"
#include "ofxScalableDraws.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ITile.reset(new ofImage);
	ITile->loadImage("Tile.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofRectangle R0(0,0,ofGetWidth(),ofGetHeight());
	if(PTiler.use_count()>0)
	{
		ofPushMatrix();
		ofPushStyle();
		PTiler->draw(R0.x,R0.y,R0.width,R0.height);
		ofPopStyle();
		ofPopMatrix();

		ofPushStyle();
		ofNoFill();
		ofRect(PTiler->PathBoundRect);
		ofRect(R);
		ofSetColor(ofColor::red);
		ofRect(R0);
		ofPopStyle();
	}	

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
	PMouse.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	PMouse.clear();
	PMouse.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	R = PMouse.getBoundingBox();
	if(PTiler.use_count()==0)
	{
		PTiler.reset(
			new ofxSDPathTiler(ITile,PMouse));
	}
	else
	{
		PTiler->addPolyline(PMouse);
	}
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

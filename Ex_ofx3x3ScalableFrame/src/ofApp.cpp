#include "ofApp.h"
#include "ofxScalableDraws.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ICorner.reset(new ofImage);
	ICorner->loadImage("Corner.jpg");
	IEdge.reset(new ofImage);
	IEdge->loadImage("Edge.jpg");
	TEdge.reset(new ofxTile(IEdge,true,false,false));
	IFill.reset(new ofImage);
	IFill->loadImage("Fill.jpg");	
	TFill.reset(new ofxTile(IFill,true,true,false));
	sf3x3.reset(new ofx3x3ScalableFrame(ICorner,TEdge,TFill,45.0f));

	DrawRect = ofRectangle(0,0,200,200);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	sf3x3->draw(
		DrawRect.x, 
		DrawRect.y, 
		DrawRect.width,
		DrawRect.height);
	ofPopMatrix();


	ofPushMatrix();
	ofPushStyle();
	ofNoFill();
	ofSetColor(0);
	ofRect(DrawRect);
	ofPopStyle();
	ofPopMatrix();

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
	setDrawRectShape(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	setDrawRectPos(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	setDrawRectShape(x,y);
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

void ofApp::setDrawRectShape( int x, int y )
{
	DrawRect.width = x - DrawRect.x;
	DrawRect.height = y - DrawRect.y;
}

void ofApp::setDrawRectPos( int x, int y )
{
	DrawRect.x = x;
	DrawRect.y = y;
}

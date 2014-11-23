#include "ofApp.h"
#include "ofxSDRectFrame.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ITile.reset(new ofImage);
	ITile->loadImage("Tile.jpg");

	RF.reset(new ofxSDRectFrame(ITile));

	R.set(200,200,200,200);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	RF->draw(R.x,R.y,R.getWidth(),R.getHeight());


	float x = 10;
	float y = 25;
	float step = 25;

	ofPushStyle();
	ofNoFill();
	ofSetLineWidth(2.0f);
	ofSetColor(255,0,0,80);
	ofRect(R);
	ofPopStyle();


	ofDrawBitmapString("mouse drag: define the frame rectangle",x,y);

	y+= step;
	ofDrawBitmapString("F1/F2: +/- Edge",x,y);
	
	y+= step;
	ofDrawBitmapString("F3/F4: +/- Section Length",x,y);

	y+= step;
	ofDrawBitmapString("F5: switch Frame Position",x,y);

	y+= step;
	ofDrawBitmapString("F6: change repeat mode",x,y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


	if(OF_KEY_F1==key||OF_KEY_F2 ==key)
	{
		float m = 2.0f*((key-OF_KEY_F1)-0.5f);
		float edge = RF->getEdge();
		edge+=m;
		edge = ofClamp(edge,1.0f,200.0f);
		RF->setEdge(edge);
	}	
	else if(OF_KEY_F3==key||OF_KEY_F4==key)
	{
		float m = 2.0f*((key-OF_KEY_F3)-0.5f);
		float sectionLen = RF->getSectionLength();
		sectionLen += m;
		sectionLen = ofClamp(sectionLen,1.0f,512.0f);
		RF->setSectionLength(sectionLen);
	}
	else if(OF_KEY_F5==key)
	{
		ofxSDRectFrame::FramePositon FPos = RF->getFramePosition();
		int fPos = (int)FPos;
		fPos ++;
		fPos = fPos%3;
		RF->setFramePosition((ofxSDRectFrame::FramePositon)fPos);
	}
	else if(OF_KEY_F6==key)
	{
		bool bXMirror = RF->getWrapXMirrored();
		RF->setWrapXMirrored(!bXMirror);
	}
	


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	setRectShape(x, y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	R.setPosition(x,y);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	setRectShape(x, y);
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

void ofApp::setRectShape( int x, int y )
{
	float dx,dy;
	dx = x-R.getMinX();
	dy = y-R.getMinY();
	R.setWidth(dx);
	R.setHeight(dy);
}

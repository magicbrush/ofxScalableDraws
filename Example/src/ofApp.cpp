#include "ofApp.h"
#include "ofxSDTile.h"

//--------------------------------------------------------------
void ofApp::setup(){
	I.reset(new ofImage);
	I->loadImage("Tile.jpg");
	I->resize(256,256);
	pTile.reset(new ofxSDTile(I));	

	mx = 100;
	my = 0;
	mw = 200;
	mh = 300;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	I->draw(0,0,100,100);
	pTile->draw(mx,my,mw,mh);


	float x = 10;
	float y = 25;
	float step = 25;

	ofDrawBitmapString("mouse drag: define the tiling rectangle",x,y);
	y+= step;
	ofDrawBitmapString("F1: try setAnchorPercent(-0.3f,-0.6f)",x,y);
	y+= step;
	ofDrawBitmapString("F2: try setAnchorPoint(20,-50)",x,y);
	y+= step;
	ofDrawBitmapString("F3: resetAnchor()",x,y);
	y+= step;
	ofDrawBitmapString("F4: decrease scale",x,y);
	y+= step;
	ofDrawBitmapString("F5: increase scale",x,y);
	y+= step;
	ofDrawBitmapString("F6: toggle repeat mode",x,y);
	y+= step;
	ofDrawBitmapString("F7: toggle x tiling",x,y);
	y+= step;
	ofDrawBitmapString("F8: toggle y tiling",x,y);
	y+= step;
	ofDrawBitmapString("F9: toggle truncate tiling",x,y);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key==OF_KEY_F1)
	{
		pTile->setAnchorPercent(-0.3f,-0.6f);
	}
	else if(key==OF_KEY_F2)
	{
		pTile->setAnchorPoint(20,-50);
	}
	else if(key==OF_KEY_F3)
	{
		pTile->resetAnchor();
	}
	else if(key==OF_KEY_F4)
	{
		ofVec2f S = pTile->getScale();
		S = S*0.8f;
		pTile->setScale(S);
	}
	else if(key==OF_KEY_F5)
	{
		ofVec2f S = pTile->getScale();
		S = S/0.8f;
		pTile->setScale(S);
	}
	else if(key==OF_KEY_F6)
	{		
		bool mirrorRep = pTile->getRepeatMode();
		pTile->setRepeatMode(!mirrorRep);
	}	
	else if(key==OF_KEY_F7)
	{
		bool xTiling = pTile->getXTiling();
		pTile->setXTiling(!xTiling);
	}	
	else if(key==OF_KEY_F8)
	{
		bool yTiling = pTile->getYTiling();
		pTile->setYTiling(!yTiling);
	}
	else if(key==OF_KEY_F9)
	{
		bool bTrucateTiling = pTile->getTruncateTiling();
		pTile->setTrucateTiling(!bTrucateTiling);
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
	mw = x-mx;
	mh = y-my;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mx = x;
	my = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	mw = x-mx;
	mh = y-my;

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

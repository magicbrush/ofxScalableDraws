#include "ofApp.h"
#include "ofxScalableDraws.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ICorner.reset(new ofImage);
	ICorner->loadImage("Corner.jpg");
	IEdge.reset(new ofImage);
	IEdge->loadImage("Edge.jpg");
	TEdge.reset(new ofxSDTile(IEdge,true,false,false));
	IFill.reset(new ofImage);
	IFill->loadImage("Fill.jpg");	
	TFill.reset(new ofxSDTile(IFill,true,true,false));	
	sf3x3.reset(new ofxSDCornerEdgeFill(ICorner,TEdge,TFill,45.0f));



	DrawRect = ofRectangle(300,0,200,200);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	

	ICorner->draw(0,0,100,100);
	TEdge->draw(100,0,100,100);
	TFill->draw(200,0,100,100);

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


	float x = 10;
	float y = 25;
	float step = 25;

	ofDrawBitmapString("mouse drag: define the frame rectangle",x,y);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if(key=='1')
	{
		sf3x3->resetDrawsCorner();
	}
	else if(key=='2')
	{
		sf3x3->resetDrawsEdge();
	}
	else if(key=='3')
	{
		sf3x3->resetDrawsFill();
	}
	else if(key=='4')
	{
		sf3x3->setDrawsCorner(ICorner);
	}
	else if(key=='5')
	{
		sf3x3->setDrawsEdge(TEdge);
	}
	else if(key=='6')
	{
		sf3x3->setDrawsFill(TFill);
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

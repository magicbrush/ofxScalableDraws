#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	BarVer = gen3GridVertical();
	BarHor = gen3GridHorizontal();
	Bar3x3 = gen3x3Grid();

	BarVerOn = false;
	BarHorOn = false;
	Bar3x3On = false;

	BarVerR = ofRectangle(0,0,30,100);
	BarHorR = ofRectangle(0,0,100,30);
	Bar3x3R = ofRectangle(200,200,200,200);
}

//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){

	/*BarVer->draw(
		BarVerR.x,
		BarVerR.y, 
		BarVerR.width,
		BarVerR.height);

	BarHor->draw(
		BarHorR.x,
		BarHorR.y, 
		BarHorR.width,
		BarHorR.height);*/

	Bar3x3->draw(
		Bar3x3R.x,
		Bar3x3R.y,
		Bar3x3R.width,
		Bar3x3R.height);

	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if('1'==key)
	{
		BarVerOn = true;
	}
	else if('2'==key)
	{
		BarHorOn = true;
	}
	else if('3'==key)
	{
		Bar3x3On = true;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	if('1'==key)
	{
		BarVerOn = false;
	}
	else if('2'==key)
	{
		BarHorOn = false;
	}
	else if('3'==key)
	{
		Bar3x3On = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	reshapeSelectedRectangle(button, x, y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	reposSelectedRectangle(button, x, y);



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

void ofApp::reshapeRectangle( ofRectangle* r, int x, int y )
{
	ofPoint p = r->getPosition();
	float dx,dy;
	dx = x-p.x;
	dy = y-p.y;		
	r->setWidth(dx);
	r->setHeight(dy);
}

void ofApp::reposRectangle( ofRectangle* r, int x, int y )
{
	r->setPosition(x,y);
	r->setWidth(0);
	r->setHeight(0);
}

void ofApp::reshapeSelectedRectangle( int button, int x, int y )
{
	if(button==0)
	{
		ofRectangle* r(NULL);
		if(BarVerOn)
		{
			r = &BarVerR;
		}
		else if(BarHorOn)
		{
			r = &BarHorR;
		}
		else if(Bar3x3On)
		{
			r = &Bar3x3R;
		}

		r= &Bar3x3R;

		if(r!=NULL)
		{
			reshapeRectangle(r, x, y);
		}
	}
}

void ofApp::reposSelectedRectangle( int button, int x, int y )
{
	if(button==0)
	{
		ofRectangle* r(NULL);
		if(BarVerOn)
		{
			r = &BarVerR;
		}
		else if(BarHorOn)
		{
			r = &BarHorR;
		}
		else if(Bar3x3On)
		{
			r = &Bar3x3R;
		}
		
		r= &Bar3x3R;
		if(r!=NULL)
		{
			reposRectangle(r, x, y);
		}
		
	}
}

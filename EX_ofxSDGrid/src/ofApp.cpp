#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	genGrid2Ds();
	loadBaseDraws();
	linkBaseDraws();

	initStates();

}

//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){

	BarVer->draw(
		BarVerR.x,
		BarVerR.y, 
		BarVerR.width,
		BarVerR.height);

	BarHor->draw(
		BarHorR.x,
		BarHorR.y, 
		BarHorR.width,
		BarHorR.height);

	Bar3x3->draw(
		Bar3x3R.x,
		Bar3x3R.y,
		Bar3x3R.width,
		Bar3x3R.height);

	ofPushStyle();
	ofSetColor(0);
	string S0 = "pressing 1 + mouse dragging: reposition horizontal bar";
	ofDrawBitmapString(S0,5,25);
	string S1 = "pressing 2 + mouse dragging: reposition vertical bar";
	ofDrawBitmapString(S1,5,45);
	string S2 = "pressing 3 + mouse dragging: reposition 3x3 grid";
	ofDrawBitmapString(S2,5,65);
	ofPopStyle();

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

		//r= &Bar3x3R;

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
		
		//r= &Bar3x3R;
		if(r!=NULL)
		{
			reposRectangle(r, x, y);
		}
		
	}
}

void ofApp::loadBaseDraws()
{
	ITopVer.reset(new ofImage);
	ITopVer->loadImage("Top.png");	
	ITileVer.reset(new ofImage);
	ITileVer->loadImage("BarVer.png");
	IBotVer.reset(new ofImage);
	IBotVer->loadImage("Bot.png");
	TFillVer.reset(new ofxSDTile(ITileVer,false,true));

	ILeftHor.reset(new ofImage);
	ILeftHor->loadImage("Left.png");
	ITileHor.reset(new ofImage);
	ITileHor->loadImage("BarHor.png");
	IRightHor.reset(new ofImage);
	IRightHor->loadImage("Right.png");
	TFillHor.reset(new ofxSDTile(ITileHor,true,false));

	ILeftTop.reset(new ofImage);
	ILeftTop->loadImage("LeftTop.png");
	ICtrTop.reset(new ofImage);
	ICtrTop->loadImage("CtrTop.png");
	IRightTop.reset(new ofImage);
	IRightTop->loadImage("RightTop.png");
	ILeftMid.reset(new ofImage);
	ILeftMid->loadImage("LeftMid.png");
	ICtrMid.reset(new ofImage);
	ICtrMid->loadImage("CtrMid.png");
	IRightMid.reset(new ofImage);
	IRightMid->loadImage("RightMid.png");
	ILeftBot.reset(new ofImage);
	ILeftBot->loadImage("LeftBot.png");
	ICtrBot.reset(new ofImage);
	ICtrBot->loadImage("CtrBot.png");
	IRightBot.reset(new ofImage);
	IRightBot->loadImage("RightBot.png");

	TTop.reset(new ofxSDTile(ICtrTop,true,false));
	TLeft.reset(new ofxSDTile(ILeftMid,false,true));
	TFill.reset(new ofxSDTile(ICtrMid,true,true));
	TRight.reset(new ofxSDTile(IRightMid,false,true));
	TBot.reset(new ofxSDTile(ICtrBot,true,false));
}

void ofApp::linkBaseDraws()
{
	BarVer->setBaseDraw(0,0,ITopVer);
	BarVer->setBaseDraw(0,1,TFillVer);
	BarVer->setBaseDraw(0,2,IBotVer);

	BarHor->setBaseDraw(0,0,ILeftHor);
	BarHor->setBaseDraw(1,0,TFillHor);
	BarHor->setBaseDraw(2,0,IRightHor);

	Bar3x3->setBaseDraw(0,0,ILeftTop);
	Bar3x3->setBaseDraw(1,0,TTop);
	Bar3x3->setBaseDraw(2,0,IRightTop);
	Bar3x3->setBaseDraw(0,1,TLeft);
	Bar3x3->setBaseDraw(1,1,BarVer);
	Bar3x3->setBaseDraw(2,1,TRight);
	Bar3x3->setBaseDraw(0,2,ILeftBot);
	Bar3x3->setBaseDraw(1,2,TBot);
	Bar3x3->setBaseDraw(2,2,IRightBot);
}

void ofApp::genGrid2Ds()
{
	BarVer = gen3GridVertical();
	BarHor = gen3GridHorizontal();
	Bar3x3 = gen3x3Grid();
}

void ofApp::initStates()
{
	BarVerOn = false;
	BarHorOn = false;
	Bar3x3On = false;

	BarVerR = ofRectangle(0,0,30,100);
	BarHorR = ofRectangle(0,0,100,30);
	Bar3x3R = ofRectangle(200,200,200,200);
}

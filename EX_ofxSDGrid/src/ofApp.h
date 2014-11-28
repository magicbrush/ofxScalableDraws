#pragma once

#include "ofMain.h"

#include "ofxScalableDraws.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void reshapeRectangle( ofRectangle* r, int x, int y );
		void reshapeSelectedRectangle( int button, int x, int y );
		void reposRectangle( ofRectangle* r, int x, int y );
		void reposSelectedRectangle( int button, int x, int y );

private:
		void initStates();
		void genGrid2Ds();
		void linkBaseDraws();
		void loadBaseDraws();

private:
		ofPtr<ofxSDGrid2D<1,3> > BarVer;
		ofPtr<ofImage> ITopVer;
		ofPtr<ofImage> ITileVer;
		ofPtr<ofxSDTile> TFillVer;
		ofPtr<ofImage> IBotVer;

		ofPtr<ofxSDGrid2D<3,1> > BarHor;
		ofPtr<ofImage> ILeftHor;
		ofPtr<ofImage> ITileHor;
		ofPtr<ofxSDTile> TFillHor;
		ofPtr<ofImage> IRightHor;

		ofPtr<ofxSDGrid2D<3,3> > Bar3x3;
		ofPtr<ofImage> ILeftTop;
		ofPtr<ofImage> ICtrTop;
		ofPtr<ofImage> IRightTop;
		ofPtr<ofImage> ILeftMid;
		ofPtr<ofImage> ICtrMid;
		ofPtr<ofImage> IRightMid;
		ofPtr<ofImage> ILeftBot;
		ofPtr<ofImage> ICtrBot;
		ofPtr<ofImage> IRightBot;
		ofPtr<ofxSDTile> TTop;
		ofPtr<ofxSDTile> TLeft;
		ofPtr<ofxSDTile> TFill;
		ofPtr<ofxSDTile> TRight;
		ofPtr<ofxSDTile> TBot;


		bool BarVerOn, BarHorOn, Bar3x3On;
		ofRectangle BarVerR, BarHorR, Bar3x3R;
		
};

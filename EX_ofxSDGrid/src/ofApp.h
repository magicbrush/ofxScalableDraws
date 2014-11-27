#pragma once

#include "ofMain.h"

#include "ofxSDGrid2D.h"

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

		ofPtr<ofxSDGrid2D<1,3> > BarVer;
		ofPtr<ofxSDGrid2D<3,1> > BarHor;
		ofPtr<ofxSDGrid2D<3,3> > Bar3x3;

		bool BarVerOn, BarHorOn, Bar3x3On;
		ofRectangle BarVerR, BarHorR, Bar3x3R;
		
};

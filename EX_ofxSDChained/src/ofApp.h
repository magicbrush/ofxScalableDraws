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


		ofPtr<ofImage> I;
		ofPtr<ofImage> IBack;
		ofPtr<ofImage> IFront;

		ofPtr<ofxSDChained> S;

		ofRectangle RDisp;
		
};

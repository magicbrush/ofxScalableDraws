#pragma once

#include "ofMain.h"

class ofxSDCornerEdgeFill;
class ofxSDTile;

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

private:
	void setDrawRectShape( int x, int y );
	void setDrawRectPos( int x, int y );

private:
	ofPtr<ofImage> ICorner;
	ofPtr<ofImage> IEdge;
	ofPtr<ofxSDTile> TEdge;
	ofPtr<ofImage> IFill;
	ofPtr<ofxSDTile> TFill;
	ofPtr<ofxSDCornerEdgeFill> sf3x3;

	ofRectangle DrawRect;		
};

#pragma once

#include "ofMain.h"

class ofx3x3ScalableFrame;
class ofxTile;

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
	ofPtr<ofxTile> TEdge;
	ofPtr<ofImage> IFill;
	ofPtr<ofxTile> TFill;
	ofPtr<ofx3x3ScalableFrame> sf3x3;


	ofRectangle DrawRect;

		
};
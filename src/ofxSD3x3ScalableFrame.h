#pragma once
#ifndef OFX3X3SCALABLEFRAME_H
#define OFX3X3SCALABLEFRAME_H

#include "ofMain.h"

class ofxSD3x3ScalableFrame:
	public ofBaseDraws
{
public:
	enum edgePosition
	{
		OFXSD_SCALABLEFRAME_EDGE_OUT,
		OFXSD_SCALABLEFRAME_EDGE_CENTER,
		OFXSD_SCALABLEFRAME_EDGE_IN
	};

public:
	ofxSD3x3ScalableFrame(
		ofPtr<ofBaseDraws> drawsCorner,
		ofPtr<ofBaseDraws> drawsEdge,
		ofPtr<ofBaseDraws> drawsFill,
		float edge=20.0f,
		edgePosition edgePos = OFXSD_SCALABLEFRAME_EDGE_IN );
	~ofxSD3x3ScalableFrame();

	ofPtr<ofBaseDraws> getDrawsCorner() const;
	void setDrawsCorner(ofPtr<ofBaseDraws> val);
	ofPtr<ofBaseDraws> getDrawsEdge() const;
	void setDrawsEdge(ofPtr<ofBaseDraws> val);
	ofPtr<ofBaseDraws> getDrawsFill() const;
	void setDrawsFill(ofPtr<ofBaseDraws> val);
	float getEdge() const;
	void setEdge(float val);
	edgePosition getEdgePosition() const;
	void setEdgePosition(edgePosition val);
	
	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );
	
	virtual float getHeight();
	virtual float getWidth();

public:
	// debug
	void resetDrawsCorner();
	void resetDrawsEdge();
	void resetDrawsFill();

private:
	float getE( );

	void drawCorners( float ed, float wdOut, 
		float Rot, float htOut );
	void drawEdges( float ed, float wdIn, float wdOut, 
		float Rot, float htIn, float htOut );
	void drawFill( float ed, float wdIn, float htIn );


private:
	ofPtr<ofBaseDraws> DrawsCorner;	
	ofPtr<ofBaseDraws> DrawsEdge;	
	ofPtr<ofBaseDraws> DrawsFill;

	ofParameter<float> Edge;	
	ofParameter<int> EdgePosition;
	
};

#endif
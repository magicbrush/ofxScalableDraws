#pragma once
#ifndef OFX3X3SCALABLEFRAME_H
#define OFX3X3SCALABLEFRAME_H

#include "ofMain.h"

class ofx3x3ScalableFrame:
	public ofBaseDraws
{
public:
	enum edgePosition
	{
		SCALABLEFRAME_EDGE_OUT,
		SCALABLEFRAME_EDGE_CENTER,
		SCALABLEFRAME_EDGE_IN
	};

public:
	ofx3x3ScalableFrame(
		ofPtr<ofBaseDraws> drawsCorner,
		ofPtr<ofBaseDraws> drawsEdge,
		ofPtr<ofBaseDraws> drawsFill,
		float edge=20.0f,
		edgePosition edgePos = SCALABLEFRAME_EDGE_IN );
	~ofx3x3ScalableFrame();

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
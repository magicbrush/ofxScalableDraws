#pragma once
#ifndef OFXSDRECTFRAME_H
#define OFXSDRECTFRAME_H

#include "ofMain.h"

class ofxSDRectFrame:
	public ofBaseDraws
{
public:
	enum FramePositon
	{
		OFXSD_RECTFRAME_CENTER,
		OFXSD_RECTFRAME_IN,
		OFXSD_RECTFRAME_OUT
	};

public:
	ofxSDRectFrame(ofPtr<ofBaseDraws> pTile,
		float edge = 40.0f,
		float sectionLen = 40.0f,
		FramePositon framePos = OFXSD_RECTFRAME_IN,
		bool wrapXMirrored = false);
	~ofxSDRectFrame();

	ofPtr<ofBaseDraws> getTile() const;
	void setTile(ofPtr<ofBaseDraws> val);	
	float getEdge() const;
	void setEdge(float val);
	float getSectionLength() const;
	void setSectionLength(float val);
	void setFramePosition(FramePositon framePos);
	FramePositon getFramePosition();
	bool getWrapXMirrored() const;
	void setWrapXMirrored(bool val);

	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );
	virtual float getHeight();
	virtual float getWidth();

private:
	float getShiftOut( );
	void setPolylineFromRectangle( ofPolyline* pl, ofRectangle &R );
	void computeROutRIn( float e );
	void computeMFrame();
	void compute2Polylines();
	void updateMeshFrameByDrawingRectangle( float x, float y, float w, float h );

	void updateMeshFrameByDrawRect();

	void drawTileToFbo();

	void EdgeChanged(float& edge);
	void SectionLengthChanged(float& sectionLen);
	void FramePosChanged(int& framePos);
	void WrapXMirroredChanged(bool& wrapXMirrored);

private:
	// --------- setting ---------------//
	ofParameter<float> Edge;	
	ofParameter<float> SectionLength;	
	ofParameter<int> FramePos;
	ofParameter<bool> WrapXMirrored;
	
	// --------- state -----------------//
	ofPtr<ofBaseDraws> Tile;
	ofPtr<ofFbo> TileF;

	ofRectangle RDraw;
	ofRectangle ROut;
	ofRectangle RIn;

	ofPolyline POut;
	ofPolyline PIn;

	ofMesh MFrame;

};



#endif
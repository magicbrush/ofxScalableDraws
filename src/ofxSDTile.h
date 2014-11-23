#pragma once
#ifndef OFXTILE_H
#define OFXTILE_H

#include "ofMain.h"

class ofxSDTile:
	public ofBaseDraws
{
public:
	ofxSDTile(
		ofPtr<ofBaseDraws> _baseTile, 
		bool xtiling = true,
		bool ytiling = true,
		bool mirrorRepeat = false,
		bool trucateTiling = true,
		ofVec2f Scl= ofVec2f(1.0f,1.0f),
		ofVec2f Tran= ofVec2f(0.0f,0.0f));
	~ofxSDTile();
	
	ofPtr<ofBaseDraws> baseTile() const;
	void baseTile(ofPtr<ofBaseDraws> val);

	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );

	virtual float getHeight();
	virtual float getWidth();

	ofVec2f getScale() const;
	void setScale(ofVec2f val);
	virtual void setAnchorPercent( float xPct, float yPct );
	virtual void setAnchorPoint( float x, float y );
	virtual void resetAnchor();

	void setRepeatMode( bool mirrorRepeat );
	bool getRepeatMode();

	bool getXTiling() const { return xTiling; }
	void setXTiling(bool val) { xTiling = val; }
	bool getYTiling() const { return yTiling; }
	void setYTiling(bool val) { yTiling = val; }
	bool getTruncateTiling() const;
	void setTrucateTiling(bool val);

private:
	void initFbo();
	void copyBaseTileToFbo();
	void resizeFboToBaseTile() const;
	void popMSV();
	void pushMSV();
	void initMesh();
	void setMeshTexCoords( float w, float h );

private:
	ofParameter<bool> xTiling,yTiling;	
	ofParameter<bool> TrucateTiling;
	
	ofParameter<ofVec2f> Scale;
	ofParameter<ofVec2f> TransPct;	
	
	ofPtr<ofBaseDraws> BaseTile;
	ofPtr<ofFbo> pF;	
	ofMesh M;

	GLint TexWrap;

};

#endif


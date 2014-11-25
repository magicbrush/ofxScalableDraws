#pragma once
#ifndef OFXSDPATHTILER_H
#define OFXSDPATHTILER_H

#include "ofMain.h"

class ofxSDPathTiler:
	public ofBaseDraws
{
public:
	ofxSDPathTiler(
		ofPtr<ofBaseDraws> pDraw, 
		ofPath& pth,
		float breadth = 40.0f,
		float sectionLen = 40.0f,
		float offset = 0.0f);
	ofxSDPathTiler(
		ofPtr<ofBaseDraws> pDraw, 
		ofPolyline& P,
		float breadth = 40.0f,
		float sectionLen = 40.0f,
		float offset = 0.0f);
	ofxSDPathTiler(
		ofPtr<ofBaseDraws> pDraw, 
		vector<ofPolyline> pls,
		float breadth = 40.0f,
		float sectionLen = 40.0f,
		float offset = 0.0f);
	~ofxSDPathTiler();

	ofPtr<ofBaseDraws> getDTile() const { return DTile; }
	void setDTile(ofPtr<ofBaseDraws> val);
	void setPath(ofPath& pth);
	void setPolyline(ofPolyline& p);
	void addPolyline(ofPolyline& p);	

	void posPathTox0y0();

	float getOffset() const { return Offset; }
	void setOffset(float val) { Offset = val; }
	float getBreadth() const { return Breadth; }
	void setBreadth(float val) { Breadth = val; }
	float getSectionLength() const { return SectionLength; }
	void setSectionLength(float val) { SectionLength = val; }

	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );
	virtual float getHeight();
	virtual float getWidth();

private:
	void clearPath();
	void init( 
		ofPtr<ofBaseDraws> pDraw, 
		ofPath& pth, 
		float breadth,  
		float sectionLen, 
		float offset);

	ofRectangle computePathBoundingBox( );
	void tileMeshAlongPath();
	void tileMeshAlongPolyline( ofPolyline &p );

	void Offset_Changed(float& val);
	void Breadth_Changed(float& val);
	void SectionLength_Changed(float& val);

//private:
public:
	ofPtr<ofBaseDraws> DTile;	
	ofPtr<ofFbo> FTile;

	ofPtr<ofPath> P;
	ofRectangle PathBoundRect;
	ofPtr<ofMesh> M;

	ofParameter<float> Offset;	
	ofParameter<float> Breadth;	
	ofParameter<float> SectionLength;

private:
	static void addPolylineToPath( ofPolyline &P, ofPath &Pth );

	

};



#endif
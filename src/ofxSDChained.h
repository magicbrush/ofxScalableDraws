#pragma once
#ifndef OFXSDCHAINED_H
#define OFXSDCHAINED_H

#include "ofMain.h"

class ofxSDChained:
	public ofBaseDraws
{
public:
	struct TransformParams
	{
		TransformParams(
			float _tx = 0, 
			float _ty = 0, 
			float _sx = 1.0f, 
			float _sy = 1.0f);
		~TransformParams();
		float tx,ty,sx,sy;
	};
	struct Margin
	{
		Margin(
			float _top=10.0f, 
			float _bot=10.0f, 
			float _left=10.0f, 
			float _right=10.0f);
		~Margin();
		float top,bot,left,right;
	};

	enum SiblingType
	{
		FRONT_SIBLING,
		BACK_SIBLING
	};

	struct Sibling
	{
		Sibling(
			ofPtr<ofBaseDraws> pD, 
			TransformParams t, 
			Margin m);
		~Sibling();
		ofPtr<ofBaseDraws> pDraw;
		TransformParams T;
		Margin M;
	};

public:
	ofxSDChained(
		ofPtr<ofBaseDraws> _me,
		ofPtr<ofBaseDraws> _back,
		TransformParams Tback = TransformParams(),
		Margin Mback = Margin(),
		ofPtr<ofBaseDraws> _front = ofPtr<ofBaseDraws>(),		
		TransformParams Tfront = TransformParams(),
		Margin Mfront = Margin());
	~ofxSDChained();

	void setSibling(
		ofPtr<ofBaseDraws> pD, 
		SiblingType bType = BACK_SIBLING,
		TransformParams T = TransformParams(),
		Margin M = Margin());

	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );

	virtual float getHeight();
	virtual float getWidth();

private:
	void drawSibling( 
		Sibling& S, float x, float y, float w, float h);
	ofRectangle getTransformedRectangle( 
		float x, float y, float w, float h, 
		TransformParams &TF, Margin &MG );

private:
	ofPtr<ofBaseDraws> pMe;
	Sibling Front, Back;
};

#endif

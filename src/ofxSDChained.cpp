#include "ofxSDChained.h"


ofxSDChained::TransformParams::TransformParams(
	float _tx /*= 0*/, 
	float _ty /*= 0*/, 
	float _sx /*= 0*/, 
	float _sy /*= 0*/ )
	:tx(_tx),ty(_ty),sx(_sx),sy(_sy)
{}

ofxSDChained::TransformParams::~TransformParams()
{}

ofxSDChained::Margin::Margin(
	float _top/*=10*/, 
	float _bot/*=10*/, 
	float _left/*=10*/, 
	float _right/*=10*/ )
	:top(_top),bot(_bot),left(_left),right(_right)
{}

ofxSDChained::Margin::~Margin()
{}

ofxSDChained::Sibling::Sibling( 
	ofPtr<ofBaseDraws> pD, 
	TransformParams t, 
	Margin m ):
		pDraw(pD), T(t), M(m)
{}

		ofxSDChained::Sibling::~Sibling()
		{

		}

void ofxSDChained::draw( 
	float x, float y, 
	float w, float h )
{	
	drawSibling(Back,x,y,w,h);
	if(pMe.use_count()>0){pMe->draw(x,y,w,h);}
	drawSibling(Front,x,y,w,h);
}

void ofxSDChained::draw( float x, float y )
{
	draw(x,y,getWidth(),getHeight());
}

float ofxSDChained::getHeight()
{
	if(pMe.use_count()>0)
	{
		return pMe->getHeight();
	}
	else
	{
		return 0;
	}
}

float ofxSDChained::getWidth()
{
	if(pMe.use_count()>0)
	{
		return pMe->getWidth();
	}
	else
	{
		return 0;
	}
}

ofxSDChained::ofxSDChained( 
	ofPtr<ofBaseDraws> _me,
	ofPtr<ofBaseDraws> _back, 
	TransformParams Tback /*= TransformParams()*/,
	Margin Mback /*= Margin()*/, 
	ofPtr<ofBaseDraws> _front /*= ofPtr<ofBaseDraws>()*/, 
	TransformParams Tfront /*= TransformParams()*/, 
	Margin Mfront /*= Margin()*/ )
	:pMe(_me),
	Back(Sibling(_back,Tback, Mback)),
	Front(Sibling(_front, Tfront, Mfront))
{}

ofxSDChained::~ofxSDChained()
{}

ofRectangle ofxSDChained::getTransformedRectangle( 
	float x, float y, float w, float h, 
	TransformParams &TF,
	Margin &MG )
{
	ofRectangle R(x,y,w,h);		
	R.translate(TF.tx, TF.ty);
	R.scaleFromCenter(TF.sx,TF.sy);
	R.x -= MG.left;
	R.y -= MG.top;
	R.width += MG.left+MG.right;
	R.height += MG.top+MG.bot;

	return R;
}

void ofxSDChained::drawSibling( 
	Sibling& S, 
	float x, float y, 
	float w, float h )
{
	if(S.pDraw.use_count()!=0)
	{
		ofRectangle R =
			getTransformedRectangle( x, y, w, h, S.T, S.M);
		S.pDraw->draw(R);
	}
}

void ofxSDChained::setSibling(
	ofPtr<ofBaseDraws> pD, 
	SiblingType bType /*= BACK_SIBLING*/, 
	TransformParams T /*= TransformParams()*/,
	Margin M /*= Margin()*/ )
{
	if(bType==FRONT_SIBLING)
	{
		Front = Sibling(pD, T, M);
	}
	else if(bType == BACK_SIBLING)
	{
		Back = Sibling(pD, T, M);
	}
}




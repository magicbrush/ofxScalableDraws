#include "ofxSDCornerEdgeFill.h"


ofxSDCornerEdgeFill::ofxSDCornerEdgeFill( 
	ofPtr<ofBaseDraws> drawsCorner, 
	ofPtr<ofBaseDraws> drawsEdge, 
	ofPtr<ofBaseDraws> drawsFill, 
	float edge, 
	edgePosition edgePos /*= SCALABLEFRAME_EDGE_IN */ )
{
	DrawsCorner = drawsCorner;
	DrawsEdge = drawsEdge;
	DrawsFill = drawsFill;

	Edge.set("Edge",edge,0.0f,512.0f);

	EdgePosition = edgePos;

}

ofxSDCornerEdgeFill::~ofxSDCornerEdgeFill()
{

}

ofxSDCornerEdgeFill::edgePosition ofxSDCornerEdgeFill::getEdgePosition() const
{
	return (edgePosition)EdgePosition.get();
}

ofPtr<ofBaseDraws> ofxSDCornerEdgeFill::getDrawsCorner() const
{
	return DrawsCorner;
}

void ofxSDCornerEdgeFill::setDrawsCorner( ofPtr<ofBaseDraws> val )
{
	DrawsCorner = val;
}

ofPtr<ofBaseDraws> ofxSDCornerEdgeFill::getDrawsEdge() const
{
	return DrawsEdge;
}

void ofxSDCornerEdgeFill::setDrawsEdge( ofPtr<ofBaseDraws> val )
{
	DrawsEdge = val;
}

ofPtr<ofBaseDraws> ofxSDCornerEdgeFill::getDrawsFill() const
{
	return DrawsFill;
}

void ofxSDCornerEdgeFill::setDrawsFill( ofPtr<ofBaseDraws> val )
{
	DrawsFill = val;
}

float ofxSDCornerEdgeFill::getEdge() const
{
	return Edge;
}

void ofxSDCornerEdgeFill::setEdge( float val )
{
	Edge = val;
}

void ofxSDCornerEdgeFill::setEdgePosition( edgePosition val )
{
	EdgePosition = val;
}

void ofxSDCornerEdgeFill::draw( float x, float y )
{
	float w,h;
	w = getWidth();
	h = getHeight();
	draw(x,y,w,h);
}

void ofxSDCornerEdgeFill::draw( float x, float y, float w, float h )
{
	float e = getE();
	float ed = Edge;
	
	float wdOut = w + 2.0f*e;
	float htOut = h + 2.0f*e;
	float xOut = x-1.0f*e;
	float yOut = y-1.0f*e;

	float wdIn = w - 2.0f*Edge;
	float htIn = h - 2.0f*Edge;
	float xIn = x + 1.0f*e;
	float yIn = y + 1.0f*e;	

	float Rot = 90.0f;

	ofTranslate(xOut,yOut,0);

	drawCorners(ed, wdOut, Rot, htOut);
	drawEdges(ed, wdIn, wdOut, Rot, htIn, htOut);
	drawFill(ed, wdIn, htIn);

}

float ofxSDCornerEdgeFill::getHeight()
{
	float e = getE();
	float h = DrawsFill->getHeight()+2.0f*e;
	return h;
}

float ofxSDCornerEdgeFill::getWidth()
{
	float e = getE();
	float w = DrawsFill->getWidth()+2.0f*e;
	return w;
}

float ofxSDCornerEdgeFill::getE()
{
	float e;
	if(EdgePosition==OFXSD_SCALABLEFRAME_EDGE_OUT)
	{
		e = Edge;
	}
	else if(EdgePosition==OFXSD_SCALABLEFRAME_EDGE_CENTER)
	{
		e = Edge/2;
	}
	else if(EdgePosition==OFXSD_SCALABLEFRAME_EDGE_IN)
	{
		e = 0;
	}	return e;
}



void ofxSDCornerEdgeFill::drawCorners( float ed, float wdOut, float Rot, float htOut )
{
	if(DrawsCorner.use_count()==0)
	{
		return;
	}

	DrawsCorner->draw(0,0,ed, ed);

	ofTranslate(wdOut,0,0);
	ofRotate(Rot);
	DrawsCorner->draw(0,0,ed, ed);

	ofTranslate(htOut,0,0);
	ofRotate(Rot);
	DrawsCorner->draw(0,0,ed, ed);

	ofTranslate(wdOut,0,0);
	ofRotate(Rot);
	DrawsCorner->draw(0,0,ed, ed);

	ofTranslate(htOut,0,0);
	ofRotate(Rot);
}

void ofxSDCornerEdgeFill::drawEdges( float ed, float wdIn, float wdOut, float Rot, float htIn, float htOut )
{
	if(DrawsEdge.use_count()==0)
	{
		return;
	}

	DrawsEdge->draw(ed,0,wdIn,ed);

	ofTranslate(wdOut,0,0);
	ofRotate(Rot);
	DrawsEdge->draw(ed,0,htIn,ed);

	ofTranslate(htOut,0,0);
	ofRotate(Rot);
	DrawsEdge->draw(ed,0,wdIn,ed);

	ofTranslate(wdOut,0,0);
	ofRotate(Rot);
	DrawsEdge->draw(ed,0,htIn,ed);

	ofTranslate(htOut,0,0);
	ofRotate(Rot);
}

void ofxSDCornerEdgeFill::drawFill( float ed, float wdIn, float htIn )
{
	if(DrawsFill.use_count()==0)
	{
		return;
	}

	DrawsFill->draw(ed,ed,wdIn,htIn);
}

void ofxSDCornerEdgeFill::resetDrawsCorner()
{
	DrawsCorner.reset();
}

void ofxSDCornerEdgeFill::resetDrawsEdge()
{
	DrawsEdge.reset();
}

void ofxSDCornerEdgeFill::resetDrawsFill()
{
	DrawsFill.reset();
}

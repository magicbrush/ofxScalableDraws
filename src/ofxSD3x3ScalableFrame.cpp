#include "ofxSD3x3ScalableFrame.h"


ofxSD3x3ScalableFrame::ofxSD3x3ScalableFrame( 
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

ofxSD3x3ScalableFrame::~ofxSD3x3ScalableFrame()
{

}

ofxSD3x3ScalableFrame::edgePosition ofxSD3x3ScalableFrame::getEdgePosition() const
{
	return (edgePosition)EdgePosition.get();
}

ofPtr<ofBaseDraws> ofxSD3x3ScalableFrame::getDrawsCorner() const
{
	return DrawsCorner;
}

void ofxSD3x3ScalableFrame::setDrawsCorner( ofPtr<ofBaseDraws> val )
{
	DrawsCorner = val;
}

ofPtr<ofBaseDraws> ofxSD3x3ScalableFrame::getDrawsEdge() const
{
	return DrawsEdge;
}

void ofxSD3x3ScalableFrame::setDrawsEdge( ofPtr<ofBaseDraws> val )
{
	DrawsEdge = val;
}

ofPtr<ofBaseDraws> ofxSD3x3ScalableFrame::getDrawsFill() const
{
	return DrawsFill;
}

void ofxSD3x3ScalableFrame::setDrawsFill( ofPtr<ofBaseDraws> val )
{
	DrawsFill = val;
}

float ofxSD3x3ScalableFrame::getEdge() const
{
	return Edge;
}

void ofxSD3x3ScalableFrame::setEdge( float val )
{
	Edge = val;
}

void ofxSD3x3ScalableFrame::setEdgePosition( edgePosition val )
{
	EdgePosition = val;
}

void ofxSD3x3ScalableFrame::draw( float x, float y )
{
	float w,h;
	w = getWidth();
	h = getHeight();
	draw(x,y,w,h);
}

void ofxSD3x3ScalableFrame::draw( float x, float y, float w, float h )
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

float ofxSD3x3ScalableFrame::getHeight()
{
	float e = getE();
	float h = DrawsFill->getHeight()+2.0f*e;
	return h;
}

float ofxSD3x3ScalableFrame::getWidth()
{
	float e = getE();
	float w = DrawsFill->getWidth()+2.0f*e;
	return w;
}

float ofxSD3x3ScalableFrame::getE()
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



void ofxSD3x3ScalableFrame::drawCorners( float ed, float wdOut, float Rot, float htOut )
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

void ofxSD3x3ScalableFrame::drawEdges( float ed, float wdIn, float wdOut, float Rot, float htIn, float htOut )
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

void ofxSD3x3ScalableFrame::drawFill( float ed, float wdIn, float htIn )
{
	if(DrawsFill.use_count()==0)
	{
		return;
	}

	DrawsFill->draw(ed,ed,wdIn,htIn);
}

void ofxSD3x3ScalableFrame::resetDrawsCorner()
{
	DrawsCorner.reset();
}

void ofxSD3x3ScalableFrame::resetDrawsEdge()
{
	DrawsEdge.reset();
}

void ofxSD3x3ScalableFrame::resetDrawsFill()
{
	DrawsFill.reset();
}

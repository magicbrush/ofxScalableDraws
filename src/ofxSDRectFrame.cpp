#include "ofxSDRectFrame.h"
#include "ofxSDUtils.h"


ofxSDRectFrame::ofxSDRectFrame(
	ofPtr<ofBaseDraws> pTile,
	float edge /*= 40.0f*/, 
	float sectionLen /*= 40.0f*/, 
	FramePositon framePos /*= OFXSD_RECTFRAME_IN*/,
	bool wrapXMirrored )
{
	ofDisableArbTex();

	WrapXMirrored.set("WrapXMirrored",wrapXMirrored);
	WrapXMirrored.addListener(this,&ofxSDRectFrame::WrapXMirroredChanged);

	setTile(pTile);

	FramePos.set("FramePosition",framePos,0,2);
	FramePos.addListener(this,&ofxSDRectFrame::FramePosChanged);
	Edge.set("Edge",edge,0,512.0f);
	Edge.addListener(this,&ofxSDRectFrame::EdgeChanged);
	SectionLength.set("SectionLength",sectionLen,1.0f,512.0f);	
	SectionLength.addListener(this,&ofxSDRectFrame::SectionLengthChanged);
	
}

ofxSDRectFrame::~ofxSDRectFrame()
{

}

void ofxSDRectFrame::setFramePosition( FramePositon framePos )
{
	FramePos = framePos;
}

ofxSDRectFrame::FramePositon ofxSDRectFrame::getFramePosition()
{
	FramePositon F;
	F = (FramePositon)FramePos.get();
	return F;
}

float ofxSDRectFrame::getEdge() const
{
	return Edge;
}

void ofxSDRectFrame::setEdge( float val )
{
	Edge = val;
}

float ofxSDRectFrame::getSectionLength() const
{
	return SectionLength;
}

void ofxSDRectFrame::setSectionLength( float val )
{
	SectionLength = val;
}

void ofxSDRectFrame::draw( float x, float y )
{
	draw(x,y,4.0f*Edge,4.0f*Edge);
}

void ofxSDRectFrame::draw( float x, float y, float w, float h )
{
	updateMeshFrameByDrawingRectangle(x, y, w, h);

	if(Tile.use_count()==0)
	{
		MFrame.drawWireframe();
	}
	else
	{
		drawTileToFbo();
		TileF->getTextureReference().bind();
		MFrame.draw();
		TileF->getTextureReference().unbind();
	}

}

float ofxSDRectFrame::getHeight()
{
	return ROut.getHeight();
}

float ofxSDRectFrame::getWidth()
{
	return ROut.getWidth();
}

ofPtr<ofBaseDraws> ofxSDRectFrame::getTile() const
{
	return Tile;
}

void ofxSDRectFrame::setTile( ofPtr<ofBaseDraws> val )
{
	Tile = val;
	if(TileF.use_count()==0)
	{
		TileF.reset(new ofFbo);
	}	
	TileF->allocate(Tile->getWidth(),Tile->getHeight(),GL_RGBA);
	ofTexture& T = TileF->getTextureReference();

	GLint WrapX;
	if(WrapXMirrored)
	{
		WrapX = GL_MIRRORED_REPEAT;
	}
	else
	{
		WrapX = GL_REPEAT;
	}
	T.setTextureWrap(WrapX,GL_CLAMP_TO_EDGE);

}

float ofxSDRectFrame::getShiftOut(  )
{
	float e;
	if(FramePos==RECTFRAME_OUT)
	{
		e = Edge;
	}
	else if(FramePos==RECTFRAME_CENTER)
	{
		e = Edge/2.0f;
	}
	else if(FramePos==RECTFRAME_IN)
	{
		e = 0;
	}	return e;
}

void ofxSDRectFrame::computeROutRIn( float e )
{
	ofPoint POutLT;
	float wdOut,htOut;
	POutLT.x = RDraw.getMinX()-e;
	POutLT.y = RDraw.getMinY()-e;
	wdOut = RDraw.getWidth() + 2.0f*e;
	htOut = RDraw.getHeight() + 2.0f*e;
	ROut.set(POutLT,wdOut,htOut);

	ofPoint PInLt;
	float wdIn,htIn;
	PInLt.x = ROut.getMinX()+Edge;
	PInLt.y = ROut.getMinY()+Edge;
	wdIn = ROut.getWidth()-2.0f*Edge;
	htIn = ROut.getHeight()-2.0f*Edge;
	RIn.set(PInLt,wdIn,htIn);
}

void ofxSDRectFrame::setPolylineFromRectangle( ofPolyline* pl, ofRectangle &R )
{
	ofPoint PStart(R.getMinX(),R.getMinY()+R.getHeight()/2);
	pl->addVertex(PStart);
	pl->addVertex(R.getTopLeft());
	pl->addVertex(R.getTopRight());
	pl->addVertex(R.getBottomRight());
	pl->addVertex(R.getBottomLeft());
	pl->addVertex(PStart);	
}

void ofxSDRectFrame::compute2Polylines()
{
	POut.clear();		
	setPolylineFromRectangle(&POut, ROut);
	PIn.clear();
	setPolylineFromRectangle(&PIn,RIn);
}

void ofxSDRectFrame::computeMFrame()
{
	MFrame.clear();
	float LenTotal = PIn.getLengthAtIndex(PIn.size()-1);
	int numSection = LenTotal/SectionLength;
	float sectLen = LenTotal/numSection;
	ofIndexType index = -1;
	for(float len = 0.0f;len<LenTotal+0.001f;len+= sectLen)
	{
		float id = PIn.getIndexAtLength(len);

		ofPoint ptIn = PIn.getPointAtIndexInterpolated(id);
		ofPoint ptOut = POut.getPointAtIndexInterpolated(id);

		MFrame.addVertex(ptIn);
		MFrame.addVertex(ptOut);

		float uout,vout,uin,vin;
		uout = (index+1)/2;
		vout = 1.0f;
		uin = uout;
		vin = 0.0f;
		MFrame.addTexCoord(ofVec2f(uin,vin));
		MFrame.addTexCoord(ofVec2f(uout,vout));

		index+= 2;
		if(index<2)
		{
			continue;
		}			

		MFrame.addIndex(index-3);
		MFrame.addIndex(index-2);
		MFrame.addIndex(index);
		MFrame.addIndex(index-3);
		MFrame.addIndex(index-1);
		MFrame.addIndex(index);
	}
}

void ofxSDRectFrame::drawTileToFbo()
{
	float wt,ht;
	wt = Tile->getWidth();
	ht = Tile->getHeight();

	float wf,hf;
	wf = TileF->getWidth();
	hf = TileF->getHeight();

	if(wt!=wf||ht!=hf)
	{
		TileF->allocate(wt,ht);
	}
	sd::pushMSV();
	TileF->begin();
	Tile->draw(0,0,TileF->getWidth(),TileF->getHeight());
	TileF->end();
	sd::popMSV();
}

void ofxSDRectFrame::updateMeshFrameByDrawingRectangle( float x, float y, float w, float h )
{
	ofRectangle R(x,y,w,h);
	if(R!=RDraw)
	{
		RDraw = R;
		updateMeshFrameByDrawRect();
	}
}

bool ofxSDRectFrame::getWrapXMirrored() const
{
	return WrapXMirrored;
}

void ofxSDRectFrame::setWrapXMirrored( bool val )
{
	WrapXMirrored = val;
}

void ofxSDRectFrame::EdgeChanged( float& edge )
{
	updateMeshFrameByDrawRect();
}

void ofxSDRectFrame::SectionLengthChanged( float& sectionLen )
{
	updateMeshFrameByDrawRect();
}

void ofxSDRectFrame::FramePosChanged( int& framePos )
{
	updateMeshFrameByDrawRect();
}

void ofxSDRectFrame::WrapXMirroredChanged( bool& wrapXMirrored )
{
	updateMeshFrameByDrawRect();
}

void ofxSDRectFrame::updateMeshFrameByDrawRect()
{
	float e = getShiftOut();
	computeROutRIn(e);
	compute2Polylines();
	computeMFrame();
}

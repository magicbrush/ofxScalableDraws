#include "ofxTile.h"



ofxTile::ofxTile( 
	ofPtr<ofBaseDraws> _baseTile,
	bool xtiling,
	bool ytiling,
	bool mirrorRepeat,
	bool trucateTiling,
	ofVec2f Scl,
	ofVec2f TranPct)
{
	ofDisableArbTex();
	initFbo();

	xTiling.set("xTiling",xtiling);
	yTiling.set("yTiling",ytiling);
	TrucateTiling.set("TrucateTiling",trucateTiling);

	initMesh();
	Scale.set("Scale",
		Scl,
		ofVec2f(0.01f,0.01f),
		ofVec2f(100.0f,100.0f));
	TransPct.set(
		"TransPct",
		TranPct,
		ofVec2f(-1.0f,-1.0f),
		ofVec2f(1.0f,1.0f));

	baseTile(_baseTile);

	setRepeatMode(mirrorRepeat);

}

ofxTile::~ofxTile()
{

}

void ofxTile::draw( float x, float y )
{	
	BaseTile->draw(x,y);
}

void ofxTile::draw( float x, float y, float w, float h )
{
	copyBaseTileToFbo();

	ofPushStyle();
	ofPushView();
	setMeshTexCoords(w,h);
	pF->getTextureReference().bind();
	ofTranslate(x,y,0.0f);
	ofScale(w,h,1.0f);
	M.draw();
	
	pF->getTextureReference().unbind();
	ofPopView();
	ofPopStyle();	
}

float ofxTile::getHeight()
{
	return BaseTile->getHeight();
}

float ofxTile::getWidth()
{
	return BaseTile->getWidth();
}

ofPtr<ofBaseDraws> ofxTile::baseTile() const
{
	return BaseTile;
}

void ofxTile::baseTile( ofPtr<ofBaseDraws> val )
{
	BaseTile = val;	
	resizeFboToBaseTile();
}

void ofxTile::resizeFboToBaseTile() const
{
	float tw,th;
	tw = BaseTile->getWidth();
	th = BaseTile->getHeight();
	if(pF->getWidth()!=tw||
		pF->getHeight()!=th)
	{
		pF->allocate(tw,th,GL_RGBA);
		
	}
}

void ofxTile::copyBaseTileToFbo()
{
	pF->begin();
	pushMSV();
	BaseTile->draw(0,0,pF->getWidth(),pF->getHeight());
	popMSV();
	pF->end();
}

void ofxTile::pushMSV()
{
	ofPushView();
	ofPushMatrix();
	ofPushStyle();
}

void ofxTile::popMSV()
{
	ofPopStyle();
	ofPopMatrix();
	ofPopView();
}

void ofxTile::initFbo()
{
	if(pF.use_count()==0)
	{
		pF.reset(new ofFbo);		
	}
}

void ofxTile::initMesh()
{
	M.clear();

	M.addVertex(ofVec3f(0,0,0));
	M.addVertex(ofVec3f(1,0,0));
	M.addVertex(ofVec3f(1,1,0));
	M.addVertex(ofVec3f(0,1,0));

	M.addTexCoord(ofVec2f(0,0));
	M.addTexCoord(ofVec2f(1,0));
	M.addTexCoord(ofVec2f(1,1));
	M.addTexCoord(ofVec2f(0,1));

	ofIndexType id[6] = {0,1,2,0,2,3};
	M.addIndices(id,6);
}

void ofxTile::setMeshTexCoords( float w, float h )
{
	ofVec2f S = Scale;
	ofVec2f TPct = TransPct;
	float xmin,ymin;
	float wd,ht;
	wd = w/(BaseTile->getWidth()*S.x);
	ht = h/(BaseTile->getHeight()*S.y);
	xmin = TPct.x*wd;
	ymin = TPct.y*ht;
	float xmax,ymax;	
	xmax = xmin + wd;
	ymax = ymin + ht;

	if(TrucateTiling)
	{
		xmin = floorf(xmin);
		xmax = ceilf(xmax);
		ymin = floorf(ymin);
		ymax = ceilf(ymax);
	}

	if(!xTiling)
	{
		xmin = 0.0f;
		xmax = 1.0f;
	}
	if(!yTiling)
	{
		ymin = 0.0f;
		ymax = 1.0f;
	}

	M.clearTexCoords();
	M.addTexCoord(ofVec2f(xmin,ymin));
	M.addTexCoord(ofVec2f(xmax,ymin));
	M.addTexCoord(ofVec2f(xmax,ymax));
	M.addTexCoord(ofVec2f(xmin,ymax));
}

ofVec2f ofxTile::getScale() const
{
	return Scale;
}

void ofxTile::setScale( ofVec2f val )
{
	Scale = val;
}

void ofxTile::setAnchorPercent( float xPct, float yPct )
{
	TransPct = ofVec2f(xPct,yPct);
}

void ofxTile::setAnchorPoint( float x, float y )
{
	float tw = BaseTile->getWidth();
	float th = BaseTile->getHeight();

	float xPct,yPct;
	xPct = x/tw;
	yPct = y/th;

	setAnchorPercent(xPct,yPct);
}

void ofxTile::resetAnchor()
{
	setAnchorPercent(0,0);
}

void ofxTile::setRepeatMode( bool mirrorRepeat )
{
	if(mirrorRepeat)
	{
		TexWrap = GL_MIRRORED_REPEAT;
	}
	else
	{
		TexWrap = GL_REPEAT;
	}

	ofTexture& T = pF->getTextureReference();
	T.setTextureWrap(TexWrap,TexWrap);
}

bool ofxTile::getTruncateTiling() const
{
	return TrucateTiling;
}

void ofxTile::setTrucateTiling( bool val )
{
	TrucateTiling = val;
}

bool ofxTile::getRepeatMode()
{
	if(TexWrap == GL_MIRRORED_REPEAT)
	{
		return true;
	}
	else
	{
		return false;
	}
}


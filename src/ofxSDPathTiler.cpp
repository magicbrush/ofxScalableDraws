#include "ofxSDPathTiler.h"

#include "ofxSDUtils.h"

ofxSDPathTiler::ofxSDPathTiler( 
	ofPtr<ofBaseDraws> pDraw, 
	ofPath& pth, 
	float breadth /*= 30.0f*/,
	float sectionLen /*= 30.0f*/, 
	float offset /*= 0.0f*/ )
{
	init(pDraw, pth, breadth, sectionLen, offset);
}

ofxSDPathTiler::ofxSDPathTiler( 
	ofPtr<ofBaseDraws> pDraw, 
	ofPolyline& P, 
	float breadth /*= 30.0f*/, 
	float sectionLen /*= 20.0f*/, 
	float offset /*= 0.0f*/ )
{
	ofPath pth;
	addPolylineToPath(P, pth);
	init(pDraw, pth, breadth, sectionLen, offset);
}

ofxSDPathTiler::ofxSDPathTiler( 
	ofPtr<ofBaseDraws> pDraw, 
	vector<ofPolyline> pls, 
	float breadth /*= 30.0f*/,
	float sectionLen /*= 20.0f*/, 
	float offset /*= 0.0f*/ )
{
	ofPath pth;
	vector<ofPolyline>::iterator it;
	for(it = pls.begin();it<pls.end();it++)
	{
		addPolylineToPath(*it,pth);
	}
	init(pDraw, pth, breadth, sectionLen, offset);
}

ofxSDPathTiler::~ofxSDPathTiler()
{

}

void ofxSDPathTiler::setPath( ofPath& pth )
{
	if(P.use_count()==0)
	{
		P.reset(new ofPath(pth));
	}
	
	PathBoundRect = computePathBoundingBox();

	if(M.use_count()==0)
	{
		M.reset(new ofMesh);
	}
	M->clear();

	tileMeshAlongPath();

	//posPathTox0y0();
	//PathBoundRect =computePathBoundingBox();
}

void ofxSDPathTiler::setPolyline( ofPolyline& p )
{
	P->clear();
	M->clear();

	addPolyline(p);
}

void ofxSDPathTiler::addPolyline( ofPolyline& p )
{
	if(p.size()==0)
	{
		return;
	}
	
	P->moveTo(p[0]);
	int numPts = p.size();
	for(int i=0;i<numPts;i++)
	{
		P->curveTo(p[i]);
	}

	ofRectangle R = p.getBoundingBox();
	PathBoundRect = PathBoundRect.getUnion(R);

	tileMeshAlongPolyline(p);

	//posPathTox0y0();
	//PathBoundRect = computePathBoundingBox();
}

void ofxSDPathTiler::setDTile( ofPtr<ofBaseDraws> val )
{
	DTile = val;
	if(FTile.use_count()==0)
	{
		FTile.reset(new ofFbo);
	}

	float wf,hf;
	wf = FTile->getWidth();
	hf = FTile->getHeight();

	float w,h;
	w = val->getWidth();
	h = val->getHeight();
	if(wf!=w||hf!=h)
	{
		FTile->allocate(w,h,GL_RGBA);
		ofTexture& T= FTile->getTextureReference();
		T.setTextureWrap(GL_REPEAT,GL_MIRRORED_REPEAT);		
	}
}

void ofxSDPathTiler::init( 
	ofPtr<ofBaseDraws> pDraw, 
	ofPath& pth, 
	float breadth, 
	float sectionLen, 
	float offset )
{
	ofDisableArbTex();
	Breadth.set("Breadth",breadth,1.0f,512.0f);
	Breadth.addListener(this,&ofxSDPathTiler::Breadth_Changed);
	SectionLength.set("SectionLength",sectionLen,1.0f,512.0f);
	SectionLength.addListener(this,&ofxSDPathTiler::SectionLength_Changed);
	Offset.set("Offset",offset,-512.0f,512.0f);
	Offset.addListener(this,&ofxSDPathTiler::Offset_Changed);
	
	setDTile(pDraw);
	setPath(pth);	
}

void ofxSDPathTiler::addPolylineToPath( ofPolyline &P, ofPath &Pth )
{
	int numVts = P.size();
	for(int i=0;i<numVts;i++)
	{
		Pth.curveTo(P[i]);
	}
}

void ofxSDPathTiler::draw( float x, float y )
{
	draw(x,y,PathBoundRect.getWidth(),PathBoundRect.getHeight());
}

void ofxSDPathTiler::draw( float x, float y, float w, float h )
{
	sd::copyBaseDrawsToFbo(DTile.get(),FTile.get());	

	ofPoint Pt(x,y);
	ofPoint Ps(PathBoundRect.getTopLeft());
	
	float sx,sy;
	sx = w/PathBoundRect.width;
	sy = h/PathBoundRect.height;

	float tx,ty;
	tx = Pt.x - Ps.x*sx;
	ty = Pt.y - Ps.y*sy;

	ofTranslate(tx,ty);
	ofScale(sx,sy,1.0f);

	if(DTile.use_count()>0)
	{		
		FTile->getTextureReference().bind();		
		M->draw();
		FTile->getTextureReference().unbind();
	}
	else
	{
		M->drawWireframe();
	}	
}

float ofxSDPathTiler::getHeight()
{
	return PathBoundRect.getHeight();
}

float ofxSDPathTiler::getWidth()
{
	return PathBoundRect.getWidth();
}

ofRectangle ofxSDPathTiler::computePathBoundingBox(  )
{
	ofPtr<ofRectangle> RBound;
	vector<ofPolyline>::iterator it;
	vector<ofPolyline>& pls = P->getOutline();
	for(it=pls.begin();it<pls.end();it++)
	{
		ofPolyline& p = *it;

		ofRectangle RBoundP = p.getBoundingBox();
		if(RBound.use_count()==0)
		{
			RBound.reset(new ofRectangle(RBoundP));
		}
		else
		{
			ofRectangle& R = (*(RBound.get()));
			R = R.getUnion(RBoundP);
		}
	}

	return *RBound.get();
}

void ofxSDPathTiler::tileMeshAlongPolyline( ofPolyline &p )
{	
	float idSec = 0;
	int idVt = -1 + M->getNumVertices();
	for(float dist = 0;
		dist<p.getLengthAtIndex(p.size()-1);
		dist+= SectionLength)
	{
		float id = p.getIndexAtLength(dist);
		ofPoint Pid = p.getPointAtLength(dist);
		ofVec3f N = p.getNormalAtIndexInterpolated(id);		

		ofVec3f shift = N*(Breadth/2.0f);		
		ofVec3f shiftN = shift.getNormalized();
		ofPoint Pin = Pid - shift + shiftN*Offset;
		ofPoint Pout = Pid + shift + shiftN*Offset;

		M->addVertex(Pin);
		M->addVertex(Pout);
		idVt += 2;
				
		float u = dist/Breadth;

		ofVec2f Tcin(u,0.0f);
		ofVec2f Tcout(u,1.0f);
		M->addTexCoord(Tcin);
		M->addTexCoord(Tcout);

		if(idSec>0)
		{			
			M->addIndex(idVt-3);
			M->addIndex(idVt-2);
			M->addIndex(idVt);
			M->addIndex(idVt-3);
			M->addIndex(idVt-1);
			M->addIndex(idVt);
		}
		idSec++;
	}
}

void ofxSDPathTiler::tileMeshAlongPath()
{
	vector<ofPolyline>& pls = P->getOutline();
	vector<ofPolyline>::iterator it;	
	for(it = pls.begin();it<pls.end();it++)
	{
		ofPolyline& p = *it;		
		tileMeshAlongPolyline(p);
	}
}

void ofxSDPathTiler::Offset_Changed( float& val )
{

}

void ofxSDPathTiler::Breadth_Changed( float& val )
{

}

void ofxSDPathTiler::SectionLength_Changed( float& val )
{

}

void ofxSDPathTiler::posPathTox0y0()
{
	ofPoint Ctr = PathBoundRect.getCenter();
	vector<ofPolyline>& pls = P->getOutline();
	vector<ofPolyline>::iterator it;	
	for(it = pls.begin();it<pls.end();it++)
	{
		ofPolyline& p = *it;		
		int numPts = p.size();
		for(int j=0;j<numPts;j++)
		{
			p[j] -=Ctr;
		}
	}
}



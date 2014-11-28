#include "ofxSDGrid2D.h"
#include "ScalableGrid.h"


ofPtr<ofxSDGrid2D<3,3> > gen3x3Grid( float x /*= 0.0f*/, float y /*= 0.0f*/, float topRatio /*= 20.0f*/, float middleRatio/*= 60.0f*/, float bottomRatio/*= 20.0f*/, float leftRatio /*= 20.0f*/, float centerRatio/*= 60.0f*/, float rightRatio/*= 20.0f*/ )
{
	ScalableGrid gRow;
	gRow.setAnchor(y);
	gRow.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
	gRow.setSectionLength(0,topRatio);
	gRow.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
	gRow.setSectionLength(1,middleRatio);
	gRow.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
	gRow.setSectionLength(2,bottomRatio);

	ScalableGrid gCol;
	gCol.setAnchor(x);
	gCol.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
	gCol.setSectionLength(0,leftRatio);
	gCol.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
	gCol.setSectionLength(1,centerRatio);
	gCol.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
	gCol.setSectionLength(2,rightRatio);

	ofPtr<ofxSDGrid2D<3,3> > pGD;
	pGD.reset(new ofxSDGrid2D<3,3>(gRow,gCol));
	return pGD;
}

ofPtr<ofxSDGrid2D<1,3> > gen3GridVertical( float x /*= 0.0f*/, float y /*= 0.0f*/, float height /*= 30.0f*/, float leftRatio /*= 20.0f*/, float centerRatio/*= 60.0f*/, float rightRatio/*= 20.0f*/ )
{
	ScalableGrid gCol(height,1,y);
	gCol.setSectionScaleType(0,ScalableGrid::SCALE_RELATIVE);

	ScalableGrid gRow;
	gRow.setAnchor(x);
	gRow.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
	gRow.setSectionLength(0,leftRatio);
	gRow.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
	gRow.setSectionLength(1,centerRatio);
	gRow.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
	gRow.setSectionLength(2,rightRatio);

	ofPtr<ofxSDGrid2D<1,3> > pGD;
	pGD.reset(new ofxSDGrid2D<1,3>(gRow,gCol));
	return pGD;
}

ofPtr<ofxSDGrid2D<3,1> > gen3GridHorizontal( float x /*= 0.0f*/, float y /*= 0.0f*/, float width /*= 30.0f*/, float topRatio /*= 20.0f*/, float middleRatio/*= 60.0f*/, float bottomRatio/*= 20.0f*/ )
{
	ScalableGrid gCol;
	gCol.setAnchor(y);
	gCol.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
	gCol.setSectionLength(0,topRatio);
	gCol.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
	gCol.setSectionLength(1,middleRatio);
	gCol.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
	gCol.setSectionLength(2,bottomRatio);

	ScalableGrid gRow(width,1,x);
	gRow.setSectionScaleType(0,ScalableGrid::SCALE_RELATIVE);

	ofPtr<ofxSDGrid2D<3,1> > pGD;
	pGD.reset(new ofxSDGrid2D<3,1>(gRow,gCol));
	return pGD;
}

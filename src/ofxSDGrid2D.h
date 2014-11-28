#pragma once
#include "ofMain.h"
#include <array>
#include "ScalableGrid.h"

typedef ofPtr<ofBaseDraws> pBaseDraws;

template<int Col, int Row>
class ofxSDGrid2D :
	public ofBaseDraws
{
public:
	ofxSDGrid2D(
		ScalableGrid gdRow, 
		ScalableGrid gdCol);
	~ofxSDGrid2D(void);

	int getNumRows();
	int getNumCols();
	void setColScaleType(int colId, ScalableGrid::Type Tp);
	ScalableGrid::Type getColScaleType(int colId);
	void setRowScaleType(int rowId, ScalableGrid::Type Tp);
	ScalableGrid::Type getRowScaleType(int rowId);
	void setColWidth(int colId, float wd);
	float getColWidth(int colId);
	void setRowHeight(int rowId,float ht);
	float getRowHeight(int rowId);
	void setBaseDraw( int row, int col, ofPtr<ofBaseDraws> pDraw);

	virtual void draw( float x, float y );
	virtual void draw( float x, float y, float w, float h );
	virtual float getHeight();
	virtual float getWidth();
private:
	void checkInputGrids( int numGDRow, int numGDCol );

private:
	vector< vector<pBaseDraws> > pDrawsAry;
	ofPtr<ScalableGrid> GDY,GDX;
	
};

ofPtr<ofxSDGrid2D<1,3> > gen3GridVertical( 
	float x = 0.0f, float y = 0.0f, 
	float height = 30.0f, 
	float leftRatio = 20.0f, 
	float centerRatio= 60.0f, 
	float rightRatio= 20.0f);

ofPtr<ofxSDGrid2D<3,1> > gen3GridHorizontal(
	float x = 0.0f, float y = 0.0f, 
	float width = 30.0f, 
	float topRatio = 20.0f, 
	float middleRatio= 60.0f, 
	float bottomRatio= 20.0f);

ofPtr<ofxSDGrid2D<3,3> > gen3x3Grid( 
	float x = 0.0f, float y = 0.0f, 
	float topRatio = 20.0f, 
	float middleRatio= 60.0f, 
	float bottomRatio= 20.0f, 
	float leftRatio = 20.0f, 
	float centerRatio= 60.0f, 
	float rightRatio= 20.0f);


template<int Col, int Row>
ofxSDGrid2D<Col, Row>::ofxSDGrid2D(
	ScalableGrid gdRow, 
	ScalableGrid gdCol)
{	
	int numGDRow = gdRow.getNumSections();
	int numGDCol = gdCol.getNumSections();
	checkInputGrids(numGDRow, numGDCol);

	GDY.reset(new ScalableGrid(gdRow));
	GDX.reset(new ScalableGrid(gdCol));

	for(int i=0;i<gdRow.getNumSections();i++)
	{
		vector<pBaseDraws> pDraws;
		for(int j=0;j<gdCol.getNumSections();j++)
		{
			pBaseDraws pD;			
			pDraws.push_back(pD);
		}
		pDrawsAry.push_back(pDraws);
	}
}
template<int Col, int Row>
ofxSDGrid2D<Col, Row>::~ofxSDGrid2D( void )
{

}

template<int Col, int Row>
int ofxSDGrid2D<Col, Row>::getNumCols()
{
	int num =  GDX->getNumSections();
	return num;
}

template<int Col, int Row>
int ofxSDGrid2D<Col, Row>::getNumRows()
{
	int num =  GDY->getNumSections();
	return num;
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::setRowScaleType( 
	int rowId, 
	ScalableGrid::Type Tp )
{
	GDY->setSectionScaleType(rowId,Tp);	
}

template<int Col, int Row>
ScalableGrid::Type ofxSDGrid2D<Col, Row>::getRowScaleType( 
	int rowId )
{
	ScalableGrid::Section S = GDY->getSection(rowId);
	return S.ScaleType;
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::setColScaleType( 
	int colId, 
	ScalableGrid::Type Tp )
{
	GDX->setSectionScaleType(colId,Tp);
}

template<int Col, int Row>
ScalableGrid::Type ofxSDGrid2D<Col, Row>::getColScaleType( 
	int colId )
{
	ScalableGrid::Section S = GDX->getSection(colId);
	return S.ScaleType;
}


template<int Col, int Row>
float ofxSDGrid2D<Col, Row>::getRowHeight( int rowId )
{
	ScalableGrid::Section S = GDY->getSection(colId);
	return S.Length;
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::setRowHeight( int rowId,float ht )
{
	GDY->setSectionLength(rowId,ht);
}

template<int Col, int Row>
float ofxSDGrid2D<Col, Row>::getColWidth( int colId )
{
	ScalableGrid::Section S = GDX->getSection(colId);
	return S.Length;
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::setColWidth( int colId, float wd )
{
	GDX->setSectionLength(colId,wd);
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::setBaseDraw( 
	int col, int row, 
	ofPtr<ofBaseDraws> pDraw )
{
	if(col<=getNumCols()-1&&row<=getNumRows()-1)
	{
		pDrawsAry[row][col] = pDraw;
	}	
}

template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::draw( float x, float y )
{
	float w,h;
	w = getWidth();
	h = getHeight();
	draw(x,y,w,h);
}
template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::draw( 
	float x, float y,
	float w, float h )
{
	GDY->setAnchor(y);
	GDY->setTotalLength(h);
	GDX->setAnchor(x);
	GDX->setTotalLength(w);

	int _row(Row),_col(Col);

	for(int i=0;i<_col;i++)
	{
		float xcell = GDX->getAbsSectionAnchor(i);
		float wcell = GDX->getAbsSectionLength(i);
		for(int j=0;j<_row;j++)
		{
			float ycell = GDY->getAbsSectionAnchor(j);
			float hcell = GDY->getAbsSectionLength(j);
			if(pDrawsAry[j][i].use_count()>0)
			{
				pDrawsAry[j][i]->draw(
					xcell,ycell,wcell,hcell);
			}
			else
			{				
				ofNoFill();
				ofRect(xcell,ycell,wcell,hcell);
			}
		}
	}
}
template<int Col, int Row>
float ofxSDGrid2D<Col, Row>::getHeight()
{
	float h(0);

	h = GDY->getTotalLength();

	return h;
}
template<int Col, int Row>
float ofxSDGrid2D<Col, Row>::getWidth()
{
	float w(0);

	w = GDX->getTotalLength();

	return w;
}
template<int Col, int Row>
void ofxSDGrid2D<Col, Row>::checkInputGrids( 
	int numGDRow, 
	int numGDCol )
{
	cout << "Row: " << Row << " Col: "<< Col << endl;
	if(numGDRow!=Row||numGDCol!=Col)
	{
		string gdSize;
		gdSize += 
			"("+ ofToString(numGDCol) + "," 
			+ ofToString(numGDRow) + ")";
		string tpSize;
		tpSize +=  
			"("+ ofToString(Col) + "," 
			+ ofToString(Row) + ")";

		string StrError;
		StrError = "grid size ";
		StrError += gdSize + 
			"mismatch the template size " + 
			tpSize;
		throw (StrError);
	}
}

//
//
//ofPtr<ofxSDGrid2D<1,3> > gen3GridVertical( 
//	float x /*= 0.0f*/, 
//	float y /*= 0.0f*/, 
//	float height /*= 30.0f*/, 
//	float leftRatio /*= 20.0f*/,
//	float centerRatio/*= 60.0f*/, 
//	float rightRatio/*= 20.0f*/ )
//{
//	ScalableGrid gCol(height,1,y);
//	gCol.setSectionScaleType(0,ScalableGrid::SCALE_RELATIVE);
//
//	ScalableGrid gRow;
//	gRow.setAnchor(x);
//	gRow.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
//	gRow.setSectionLength(0,leftRatio);
//	gRow.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
//	gRow.setSectionLength(1,centerRatio);
//	gRow.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
//	gRow.setSectionLength(2,rightRatio);
//
//	ofPtr<ofxSDGrid2D<1,3> > pGD;
//	pGD.reset(new ofxSDGrid2D<1,3>(gRow,gCol));
//	return pGD;
//}
//
//
//ofPtr<ofxSDGrid2D<3,1> > gen3GridHorizontal( 
//	float x /*= 0.0f*/, 
//	float y /*= 0.0f*/, 
//	float width /*= 30.0f*/, 
//	float topRatio /*= 20.0f*/, 
//	float middleRatio/*= 60.0f*/, 
//	float bottomRatio/*= 20.0f*/ )
//{
//	ScalableGrid gCol;
//	gCol.setAnchor(y);
//	gCol.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
//	gCol.setSectionLength(0,topRatio);
//	gCol.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
//	gCol.setSectionLength(1,middleRatio);
//	gCol.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
//	gCol.setSectionLength(2,bottomRatio);
//
//	ScalableGrid gRow(width,1,x);
//	gRow.setSectionScaleType(0,ScalableGrid::SCALE_RELATIVE);
//
//	ofPtr<ofxSDGrid2D<3,1> > pGD;
//	pGD.reset(new ofxSDGrid2D<3,1>(gRow,gCol));
//	return pGD;
//}
//
//
//ofPtr<ofxSDGrid2D<3,3> > gen3x3Grid( 
//	float x /*= 0.0f*/, 
//	float y /*= 0.0f*/, 
//	float topRatio /*= 20.0f*/, 
//	float middleRatio/*= 60.0f*/, 
//	float bottomRatio/*= 20.0f*/, 
//	float leftRatio /*= 20.0f*/,
//	float centerRatio/*= 60.0f*/, 
//	float rightRatio/*= 20.0f*/ )
//{
//	ScalableGrid gRow;
//	gRow.setAnchor(y);
//	gRow.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
//	gRow.setSectionLength(0,topRatio);
//	gRow.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
//	gRow.setSectionLength(1,middleRatio);
//	gRow.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
//	gRow.setSectionLength(2,bottomRatio);
//
//	ScalableGrid gCol;
//	gCol.setAnchor(x);
//	gCol.setSectionScaleType(0,ScalableGrid::SCALE_ABSOLUTE);
//	gCol.setSectionLength(0,leftRatio);
//	gCol.setSectionScaleType(1,ScalableGrid::SCALE_RELATIVE);
//	gCol.setSectionLength(1,centerRatio);
//	gCol.setSectionScaleType(2,ScalableGrid::SCALE_ABSOLUTE);
//	gCol.setSectionLength(2,rightRatio);
//
//	ofPtr<ofxSDGrid2D<3,3> > pGD;
//	pGD.reset(new ofxSDGrid2D<3,3>(gRow,gCol));
//	return pGD;
//}













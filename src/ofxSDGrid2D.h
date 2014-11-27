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
	void setBaseDraw(
		int col, 
		int row, 
		ofPtr<ofBaseDraws> pDraw);

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














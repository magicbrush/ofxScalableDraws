#pragma  once
#ifndef SCALABLEGRID_H
#define SCALABLEGRID_H

#include <vector>

using namespace std;

class ScalableGrid
{
public:
	enum Type
	{
		SCALE_RELATIVE,
		SCALE_ABSOLUTE
	};

	struct Section
	{
		Section(
			Type type=SCALE_RELATIVE,
			float Len = 1.0f);
		~Section();

		Type ScaleType;
		float Length;
	};

public:
	ScalableGrid(
		float Len = 100.0f,
		int NumSections = 3,
		float anchor = 0);
	~ScalableGrid();

	void init( vector<Section> Secs, float anchor = 0.0f);

	void resetTempValues();

	void setAnchor(float x);
	float getAnchor();	

	void addSection(Section sec);	
	void setSection(int id, Section S);
	void setSectionScaleType(int id, Type T);
	void setSectionLength(int id, float Len);

	int getNumSections();	
	Section getSection(int idSection);
	float getAbsSectionAnchor(int idSection);
	float getAbsSectionLength(int idSection);

	void setTotalLength(float len);	
	float getTotalLength();	
private:
	void computeAbsoluteSectionLengths();

private:
	float Anchor;
	vector<Section> Sections;		
	float Length;

	// state	
	float TotalScaleLen,TotalFixLen;
	float absTotalScaleLen;
	float FixLenRatio;	

};




#endif

#include "ScalableGrid.h"


ScalableGrid::Section::Section( 	
	Type type/*=RELATIVE*/, 
	float Len /*= 1.0f*/ )
{
	ScaleType = type;
	Length = Len;
}

ScalableGrid::Section::~Section()
{

}

ScalableGrid::ScalableGrid( 
	float Len /*= 100.0f*/,
	int NumSections /*= 3*/ ,
	float Anchor)
{
	vector<Section> secs;
	float seclen = Len/NumSections;
	for(int i=0;i<NumSections;i++)
	{
		Section S(ScalableGrid::SCALE_RELATIVE,seclen);
		secs.push_back(S);
	}
	init(secs,Anchor);
}

ScalableGrid::~ScalableGrid()
{

}

void ScalableGrid::init( vector<Section> Secs, float anchor )
{
	Anchor = anchor;
	Sections = Secs;

	Length = 0.0f;

	resetTempValues();


	computeAbsoluteSectionLengths();
}

void ScalableGrid::addSection( Section sec )
{
	Sections.push_back(sec);
	computeAbsoluteSectionLengths();
}

void ScalableGrid::setTotalLength( float len )
{
	if(len<0)
	{
		len = 0;
	}
	Length = len;
	computeAbsoluteSectionLengths();
}

float ScalableGrid::getTotalLength()
{
	return Length;
}

int ScalableGrid::getNumSections()
{
	return Sections.size();
}

float ScalableGrid::getAbsSectionAnchor(int idSection)
{
	int NumSec = Sections.size();	
	if(idSection>NumSec-1)
	{
		return Anchor;
	}

	float Len = Anchor;
	for(int i=0;i<idSection;i++)
	{
		Len += getAbsSectionLength(i);
	}

	return Len;
}

float ScalableGrid::getAbsSectionLength( int idSection )
{	
	
	int NumSec = Sections.size();	
	if(idSection>NumSec-1)
	{
		return -1.0f;
	}

	Section S= Sections[idSection];

	float Len(0);
	if(S.ScaleType==SCALE_RELATIVE)
	{
		float ScaleLenRatio = S.Length/TotalScaleLen;
		Len = absTotalScaleLen*ScaleLenRatio;
	}
	else if(S.ScaleType==SCALE_ABSOLUTE)
	{
		Len = S.Length*FixLenRatio;
	}

	return Len;
}


void ScalableGrid::setSection( int id, Section S )
{
	int num = Sections.size();
	if(id>num-1)
	{
		return;
	}

	Sections[id] = S;
	computeAbsoluteSectionLengths();
}

void ScalableGrid::setSectionScaleType( int id, Type T )
{
	int num = Sections.size();
	if(id>num-1)
	{
		return;
	}

	Sections[id].ScaleType = T;
	computeAbsoluteSectionLengths();
}

void ScalableGrid::setSectionLength( int id, float Len )
{
	int num = Sections.size();
	if(id>num-1)
	{
		return;
	}

	Sections[id].Length = Len;
	computeAbsoluteSectionLengths();
}

ScalableGrid::Section ScalableGrid::getSection( int idSection )
{
	int num = Sections.size();
	if(idSection>num-1)
	{
		Section S;
		S.Length = -1.0f;
		return S;
	}

	return Sections[idSection];
}

void ScalableGrid::computeAbsoluteSectionLengths()
{
	
	resetTempValues();
	vector<Section>::iterator it;
	for(it=Sections.begin();it<Sections.end();it++)
	{
		Section Sec = *it;
		if(Sec.ScaleType == SCALE_RELATIVE)
		{
			TotalScaleLen += Sec.Length;			
		}	
		else if(Sec.ScaleType == SCALE_ABSOLUTE)
		{
			TotalFixLen += Sec.Length;
		}
	}

	absTotalScaleLen = Length - TotalFixLen;
	float TotalFixLen2 = TotalFixLen;
	if(absTotalScaleLen<0)
	{
		absTotalScaleLen = 0;
		TotalFixLen2 = Length;
	}
	FixLenRatio = TotalFixLen2/TotalFixLen;
}

void ScalableGrid::setAnchor( float x )
{
	Anchor = x;
}

float ScalableGrid::getAnchor()
{
	return Anchor;
}

void ScalableGrid::resetTempValues()
{

	TotalScaleLen = 0.0f;
	TotalFixLen = 0.0f;
	absTotalScaleLen = 0.0f;
	FixLenRatio = 1.0f;
}



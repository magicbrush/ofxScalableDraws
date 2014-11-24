#include "ofxSDUtils.h"

namespace sd
{
	void pushMSV()
	{
		ofPushMatrix();
		ofPushStyle();
		ofPushView();
	}

	void popMSV()
	{
		ofPopView();
		ofPopStyle();
		ofPopMatrix();
	}

	void copyBaseDrawsToFbo( ofBaseDraws* pdraws, ofFbo* pF )
	{		
		float w,h;
		w = pF->getWidth();
		h = pF->getHeight();
		pF->begin();
		pushMSV();
		pdraws->draw(0,0,w,h);
		popMSV();
		pF->end();
	}

}
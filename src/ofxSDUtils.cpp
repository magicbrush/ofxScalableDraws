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
}
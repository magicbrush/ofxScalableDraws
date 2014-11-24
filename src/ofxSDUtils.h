#pragma  once
#ifndef OFXSDUTILS_H
#define OFXSDUTILS_H

#include "ofMain.h"

namespace sd
{
	void pushMSV();
	void popMSV();

	void copyBaseDrawsToFbo(
		ofBaseDraws* pdraws,
		ofFbo* pF);


}


#endif
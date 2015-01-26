#pragma once

#include "ofMain.h"

#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

class ofxAnimation{
public:
    ofxAnimation();
    ~ofxAnimation();
    
    void setName(string name);
    string getName();
private:
    string name;
};
#pragma once

#include "ofMain.h"

#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimationKeyframe.h"


class ofxAnimation{
public:
    ofxAnimation();
    ~ofxAnimation();
    
    void setName(string name);
    string getName();
    ofxAnimationKeyframe* addKeyframe(string keyframePercent);
    vector<ofxAnimationKeyframe*> getKeyframeSequence();
    
    static bool keyframeCompare(ofxAnimationKeyframe* a, ofxAnimationKeyframe* b){
        return a->getPercentage() <= b->getPercentage();
    }
    
    set<string> getKeys();
    
private:
    string name;
    map<string,ofxAnimationKeyframe> keyframes;
    vector<ofxAnimationKeyframe*> keyframeSequence;
};
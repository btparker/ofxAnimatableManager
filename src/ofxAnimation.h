#pragma once
#include "ofMain.h"
#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimationInstance.h"
#include "ofxAnimationKeyframe.h"

class ofxAnimationInstance;
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
    
    ofxAnimationInstance* generateAnimationInstance(string ID);
    
private:
    string name;
    map<string,ofxAnimationKeyframe> keyframes;
    vector<ofxAnimationKeyframe*> keyframeSequence;
};
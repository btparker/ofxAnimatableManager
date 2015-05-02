#pragma once
#include "ofxAnimationInstance.h"
#include "ofxAnimation.h"
#include "ofxJSON.h"

const string INSTANCES = "instances";
const string ANIMATIONS = "animations";
const string ANIMATION = "animation";
const string DURATION = "duration";
const string DELAY = "delay";
const string TIMING_FUNCTION = "timing-function";

namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}

class ofxAnimatableManager{
public:
    ofxAnimatableManager();
    ~ofxAnimatableManager();
    void update(float dt);
    ofxAnimation* addAnimation(string animationName);
//    ofxAnimationInstance* generateAnimationInstance(string animationName, string animationInstanceID);
    ofxAnimationInstance* cloneAnimationInstance(string animationInstanceID);
    bool hasAnimation(string animationName);
    bool hasAnimationInstance(string animationInstanceID);
    ofxAnimation* getAnimation(string animationName);
    ofxAnimationInstance* getAnimationInstance(string animationInstanceID);
    
    void load(ofxJSONElement animationData);
    void loadAnimations(ofxJSONElement animationsData);
    void loadInstances(ofxJSONElement instancesData);
    
    map<string, string> data;
    static bool isColor(string colorStr);
    static ofColor parseColor(string colorValue);
    map<string, ofxAnimation*>* getAnimations();
    map<string, ofxAnimationInstance*>* getAnimationInstances();
protected:
    map<string, ofxAnimation*> animations;
    map<string, ofxAnimationInstance*> animationInstances;
    map<string, ofxAnimationInstance*> clonedAnimationInstances;
private:
};
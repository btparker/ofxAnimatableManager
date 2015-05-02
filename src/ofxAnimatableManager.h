#pragma once
#include "ofxAnimationInstance.h"
#include "ofxAnimation.h"
#include "ofxJSON.h"

const string INSTANCES = "instances";
const string ANIMATIONS = "animations";
const string ANIMATION = "animation";


namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}

class ofxAnimatableManager{
public:
    ofxAnimatableManager();
    ~ofxAnimatableManager();
    void update(float dt);
    ofxAnimationInstance* cloneAnimationInstance(string animationInstanceID);
    bool hasAnimation(string animationName);
    bool hasAnimationInstance(string animationInstanceID);
    ofxAnimation* getAnimation(string animationName);
    ofxAnimationInstance* getAnimationInstance(string animationInstanceID);
    
    void load(ofxJSONElement animationData);
    void loadAnimations(ofxJSONElement animationsData);
    void loadInstances(ofxJSONElement instancesData);
    
    map<string, string> data;
    map<string, ofxAnimation*>* getAnimations();
    map<string, ofxAnimationInstance*>* getAnimationInstances();
protected:
    map<string, ofxAnimation*> animations;
    map<string, ofxAnimationInstance*> animationInstances;
    map<string, ofxAnimationInstance*> clonedAnimationInstances;
private:
};
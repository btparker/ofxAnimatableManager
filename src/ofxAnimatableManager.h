#pragma once

#include "ofMain.h"

#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

namespace Animations {
    const string DEFAULT = "DEFAULT";
}

namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}

namespace AnimationAlignments {
    enum ENUM{START, END};
}

struct AnimatableValues{
    int durationUnits = -1;
    int delayUnits = -1;
    AnimationAlignments::ENUM alignAnimation = AnimationAlignments::START;
    AnimatableTypes::ENUM type;
    AnimCurve curveStyle;
    
    ofColor startColor;
    float startFloat;
    ofPoint startPoint;
    
    ofColor endColor;
    float endFloat;
    ofPoint endPoint;
};

struct State{
    float duration = -1.0;
    float durationUnitLength = -1;
    int durationUnits = -1;
    int delayUnits = -1;
    
    AnimCurve curveStyle;
    
    map<string, AnimatableValues> animatableValues;
};


class ofxAnimatableManager: public ofxAnimatableFloat{
public:
    ofxAnimatableManager();
    ~ofxAnimatableManager();
    void update(float dt);
    void setCurve( AnimCurve curveStyle );
    void addAnimatable(ofxAnimatable* animatable, string key = "");
    void setDurationUnits(string key, int units);
    void setDelayUnits(string key, int units, AnimationAlignments::ENUM alignAnimation = AnimationAlignments::START);
    void updateDurations();
    void setDuration(float duration);
    void startAnimationDefinition(string animation);
    void endAnimationDefinition(string animation);
    void startAnimationTransitionDefinition(string state1, string state2);
    void endAnimationTransitionDefinition(string state1, string state2);
    void animateTo(string key, ofPoint value, int durationUnits = 1, int delayUnits = -1, AnimationAlignments::ENUM alignAnimation = AnimationAlignments::START);
    void animateTo(string key, float value, int durationUnits = 1, int delayUnits = -1, AnimationAlignments::ENUM alignAnimation = AnimationAlignments::START);
    void animateTo(string key, ofColor value, int durationUnits = 1, int delayUnits = -1, AnimationAlignments::ENUM alignAnimation = AnimationAlignments::START);
    
    void animate(string key);
    
protected:
    string activeAnimation;
    map<string, ofxAnimatable*> animatables;
    map<string, State> animations;
    map<string, int> animatableDurationUnits;
    
private:
};
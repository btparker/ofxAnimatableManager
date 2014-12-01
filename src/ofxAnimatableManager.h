#pragma once

#include "ofMain.h"

#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

namespace States {
    const string DEFAULT = "DEFAULT";
}

namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}

struct AnimatableValues{
    int durationUnits = -1;
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
        void updateDurations();
        void setDuration(float duration);
        void startStateDefinition(string state);
        void endStateDefinition(string state);
        void startStateTransitionDefinition(string state1, string state2);
        void endStateTransitionDefinition(string state1, string state2);
        void animateTo(string key, ofPoint value, int durationUnits);
        void animateTo(string key, float value, int durationUnits);
        void animateTo(string key, ofColor value, int durationUnits);
        void animateState(string key);

    protected:
        string activeState;
        map<string, ofxAnimatable*> animatables;
        map<string, State> states;
        map<string, int> animatableDurationUnits;
    
    private:
    
        void startAfterWait();
};
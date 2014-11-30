#pragma once

#include "ofMain.h"

#include "ofxAnimatable.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

class ofxAnimatableManager: public ofxAnimatable{
    public:
        ofxAnimatableManager();
        ~ofxAnimatableManager();
        void update(float dt);
        void setRepeatType(AnimRepeat repeat);
        void setCurve( AnimCurve curveStyle );
        void addAnimatable(ofxAnimatable* animatable, string key = "");
        void setDurationUnits(string key, int units);
        void updateDurations();
        void setDuration(float duration);

    protected:
        map<string, ofxAnimatable*> animatables;
        map<string, int> animatableDurationUnits;
    
    private:
    
        void startAfterWait();
};
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

    protected:
        map<string, ofxAnimatable*> animatables;
    
    private:
    
        void startAfterWait();
};
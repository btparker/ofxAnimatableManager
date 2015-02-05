#include "ofxAnimation.h"

ofxAnimation::ofxAnimation(){
    addKeyframe("0%");
    addKeyframe("100%");
}

void ofxAnimation::setName(string name){
    this->name = name;
}

string ofxAnimation::getName(){
    return this->name;
}

ofxAnimationKeyframe* ofxAnimation::addKeyframe(string keyframePercent){
    float percent = ofToFloat(keyframePercent)/100.0f;
    if(keyframes.count(keyframePercent) == 0){
        keyframes[keyframePercent] = ofxAnimationKeyframe();
        keyframeSequence.push_back(&keyframes[keyframePercent]);
    }
    keyframes[keyframePercent].setPercentage(percent);
    keyframes[keyframePercent].setPercentageKey(keyframePercent);
    
    ofSort(keyframeSequence,ofxAnimation::keyframeCompare);
    return &keyframes[keyframePercent];
}

vector<ofxAnimationKeyframe*> ofxAnimation::getKeyframeSequence(){
    return this->keyframeSequence;
}

bool ofxAnimation::hasStartingKeyframe(){
    return getKeyframeSequence()[0]->getPercentageKey() == "0%";
}

ofxAnimationKeyframe* ofxAnimation::getStartingKeyframe(){
    if(hasStartingKeyframe()){
        return getKeyframeSequence()[0];
    }
    else{
        return NULL;
    }
}

ofxAnimation::~ofxAnimation(){
}
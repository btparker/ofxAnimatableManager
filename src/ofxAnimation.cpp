#include "ofxAnimation.h"

ofxAnimation::ofxAnimation(){
    addKeyframe("0%");
}

void ofxAnimation::setName(string name){
    this->name = name;
}

string ofxAnimation::getName(){
    return this->name;
}

ofxAnimationKeyframe* ofxAnimation::addKeyframe(string keyframePercent){
    // Cleaner naming conventions
    if(keyframePercent == "from"){
        keyframePercent = "0%";
    }
    else if(keyframePercent == "to"){
        keyframePercent = "100%";
    }
    
    float percent = ofToFloat(keyframePercent)/100.0f;
    
    if(keyframes.count(keyframePercent) > 0){
        int index = ofFind(keyframeSequence, &keyframes[keyframePercent]);
        keyframeSequence.erase(keyframeSequence.begin() + index);
    }
    keyframes[keyframePercent] = ofxAnimationKeyframe();
    keyframeSequence.push_back(&keyframes[keyframePercent]);
    
    keyframes[keyframePercent].setPercentage(percent);
    
    keyframes[keyframePercent].setPercentageKey(keyframePercent);
    
    ofSort(keyframeSequence,ofxAnimation::keyframeCompare);
    
    return &keyframes[keyframePercent];
}

set<string> ofxAnimation::getKeys(){
    set<string> keys;
    for(ofxAnimationKeyframe* keyframe : getKeyframeSequence()){
        for(string key : keyframe->getKeys()){
            keys.insert(key);
        }
    }
    return keys;
}

vector<ofxAnimationKeyframe*> ofxAnimation::getKeyframeSequence(){
    return this->keyframeSequence;
}

ofxAnimation::~ofxAnimation(){
}
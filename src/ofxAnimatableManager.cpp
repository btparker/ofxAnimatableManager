#include "ofxAnimatableManager.h"

ofxAnimatableManager::ofxAnimatableManager(){
    setup();
}

void ofxAnimatableManager::update(float dt){
    ofxAnimatable::update(dt);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->update(dt);
    }
}

void ofxAnimatableManager::addAnimatable(ofxAnimatable* animatable, string key){
    // If no key is provided, create unique key (perhaps a bit jankity, but I didn't want something "predictable")
    // And I want keys later as an option
    
    if(key == ""){
        key = ofToString(animatables.size())+"-"+ofToString(ofGetFrameNum());
    }
    animatables[key] = animatable;
    animatables[key]->setRepeatType(ofxAnimatable::repeat_);
    animatables[key]->setCurve(ofxAnimatable::curveStyle_);
}

void ofxAnimatableManager::setRepeatType( AnimRepeat repeat ){
    ofxAnimatable::setRepeatType(repeat);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->setRepeatType(repeat);
    }
}

void ofxAnimatableManager::setCurve( AnimCurve curveStyle ){
    ofxAnimatable::setCurve(curveStyle);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->setCurve(curveStyle);
    }
}

void ofxAnimatableManager::startAfterWait(){
}

ofxAnimatableManager::~ofxAnimatableManager(){
}
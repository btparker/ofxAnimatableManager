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

void ofxAnimatableManager::addAnimatable(string key, ofxAnimatable* animatable){
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
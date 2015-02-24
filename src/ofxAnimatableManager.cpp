#include "ofxAnimatableManager.h"


ofxAnimatableManager::ofxAnimatableManager(){
    
}

void ofxAnimatableManager::update(float dt){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        animationInstance->second->update(dt);
    }
}

ofxAnimation* ofxAnimatableManager::addAnimation(string animationName){
    if(animations.count(animationName) > 0){
        ofLogWarning("ofxAnimatableManager::addAnimation","Animation "+animationName+" already present, reinitialized");
    }
    animations[animationName] = new ofxAnimation();
    animations[animationName]->setName(animationName);
    return animations[animationName];
}

bool ofxAnimatableManager::hasAnimation(string animationName){
    return animations.count(animationName) > 0;
}


ofxAnimation* ofxAnimatableManager::getAnimation(string animationName){
    if(hasAnimation(animationName)){
        return animations[animationName];
    }
    else{
        return NULL;
    }
}

ofxAnimationInstance* ofxAnimatableManager::generateAnimationInstance(string animationName, string animationInstanceID){
    if(animations.count(animationName) == 0){
        ofLogError("ofxAnimatableManager::generateAnimationInstance", "No animation of name "+animationName+" found, ofxAnimationInstance requires ofxAnimation, returning NULL");
        return NULL;
    }
    else{
        animationInstances[animationInstanceID] = new ofxAnimationInstance(animations[animationName]);
        animationInstances[animationInstanceID]->setID(animationInstanceID);
        return animationInstances[animationInstanceID];
    }
}

void ofxAnimatableManager::triggerAnimationInstance(string animationInstanceID){
    animationInstances[animationInstanceID]->reset();
    animationInstances[animationInstanceID]->play();
}

ofxAnimatableManager::~ofxAnimatableManager(){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        delete animationInstance->second;
    }
}

AnimCurve ofxAnimatableManager::getCurveFromName(string name){
    if(name == "EASE_IN_EASE_OUT"){
        return EASE_IN_EASE_OUT;
    }
    else if(name == "EASE_IN"){
        return EASE_IN;
    }
    else if(name == "EASE_OUT"){
        return EASE_OUT;
    }
    else if(name == "LINEAR"){
        return LINEAR;
    }
    else if(name == "BOUNCY"){
        return BOUNCY;
    }
    else if(name == "TANH"){
        return TANH;
    }
    else if(name == "SINH"){
        return SINH;
    }
    else if(name == "SQUARE"){
        return SQUARE;
    }
    else if(name == "LATE_SQUARE"){
        return LATE_SQUARE;
    }
    else if(name == "EARLY_SQUARE"){
        return EARLY_SQUARE;
    }
    else if(name == "BLINK_5"){
        return BLINK_5;
    }
    else if(name == "BLINK_3"){
        return BLINK_3;
    }
    else if(name == "BLINK_2"){
        return BLINK_2;
    }
    else if(name == "BLINK_AND_FADE_1"){
        return BLINK_AND_FADE_1;
    }
    else if(name == "BLINK_AND_FADE_2"){
        return BLINK_AND_FADE_2;
    }
    else if(name == "BLINK_AND_FADE_3"){
        return BLINK_AND_FADE_3;
    }
    else if(name == "LATE_LINEAR"){
        return LATE_LINEAR;
    }
    else if(name == "LATE_EASE_IN_EASE_OUT"){
        return LATE_EASE_IN_EASE_OUT;
    }
    else if(name == "EARLY_LINEAR"){
        return EARLY_LINEAR;
    }
    else if(name == "VERY_LATE_LINEAR"){
        return VERY_LATE_LINEAR;
    }
    else if(name == "VERY_LATE_EASE_IN_EASE_OUT"){
        return VERY_LATE_EASE_IN_EASE_OUT;
    }
    else if(name == "QUADRATIC_EASE_IN"){
        return QUADRATIC_EASE_IN;
    }
    else if(name == "QUADRATIC_EASE_OUT"){
        return QUADRATIC_EASE_OUT;
    }
    else if(name == "EARLY_QUADRATIC_EASE_OUT"){
        return EARLY_QUADRATIC_EASE_OUT;
    }
    else if(name == "QUADRATIC_BEZIER_PARAM"){
        return QUADRATIC_BEZIER_PARAM;
    }
    else if(name == "CUBIC_BEZIER_PARAM"){
        return CUBIC_BEZIER_PARAM;
    }
    else if(name == "EXPONENTIAL_SIGMOID_PARAM"){
        return EXPONENTIAL_SIGMOID_PARAM;
    }
    else if(name == "SWIFT_GOOGLE"){
        return SWIFT_GOOGLE;
    }
    else if(name == "OBJECT_DROP"){
        return OBJECT_DROP;
    }
    else if(name == "EASE_IN_BACK"){
        return EASE_IN_BACK;
    }
    else if(name == "EASE_OUT_BACK"){
        return EASE_OUT_BACK;
    }
    else if(name == "EASE_IN_OUT_BACK"){
        return EASE_IN_OUT_BACK;
    }
    else if(name == "EASE_OUT_IN_BACK"){
        return EASE_OUT_IN_BACK;
    }
        
    else if(name == "EASE_IN_BOUNCE"){
        return EASE_IN_BOUNCE;
    }
    else if(name == "EASE_OUT_BOUNCE"){
        return EASE_OUT_BOUNCE;
    }
    else if(name == "EASE_IN_OUT_BOUNCE"){
        return EASE_IN_OUT_BOUNCE;
    }
    else if(name == "EASE_OUT_IN_BOUNCE"){
        return EASE_OUT_IN_BOUNCE;
    }
        
    else if(name == "EASE_IN_ELASTIC"){
        return EASE_IN_ELASTIC;
    }
    else if(name == "EASE_OUT_ELASTIC"){
        return EASE_OUT_ELASTIC;
    }
    else if(name == "EASE_IN_OUT_ELASTIC"){
        return EASE_IN_OUT_ELASTIC;
    }
    else if(name == "EASE_OUT_IN_ELASTIC"){
        return EASE_OUT_IN_ELASTIC;
    }
    else{
        return LINEAR;
    }
}
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
    animationInstances[animationInstanceID]->play();
}

ofxAnimatableManager::~ofxAnimatableManager(){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        delete animationInstance->second;
    }
}
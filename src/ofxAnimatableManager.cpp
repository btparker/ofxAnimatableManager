#include "ofxAnimatableManager.h"


ofxAnimatableManager::ofxAnimatableManager(){
    
}

void ofxAnimatableManager::update(float dt){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        animationInstance->second->update(dt);
    }
    for(auto animationInstance = clonedAnimationInstances.begin(); animationInstance != clonedAnimationInstances.end(); ++animationInstance){
        animationInstance->second->update(dt);
    }
}

bool ofxAnimatableManager::hasAnimation(string animationName){
    return animations.count(animationName) > 0;
}


bool ofxAnimatableManager::hasAnimationInstance(string animationInstanceID){
    return animationInstances.count(animationInstanceID) > 0 || clonedAnimationInstances.count(animationInstanceID) > 0;
}


ofxAnimation* ofxAnimatableManager::getAnimation(string animationName){
    if(hasAnimation(animationName)){
        return animations[animationName];
    }
    else{
        return NULL;
    }
}

ofxAnimationInstance* ofxAnimatableManager::getAnimationInstance(string animationInstanceID){
    if(hasAnimationInstance(animationInstanceID)){
        return animationInstances[animationInstanceID];
    }
    else{
        return NULL;
    }
}

ofxAnimationInstance* ofxAnimatableManager::cloneAnimationInstance(string animationInstanceID){
    if(animationInstances.count(animationInstanceID) == 0){
        ofLogError("ofxAnimatableManager::generateAnimationInstance", "No animation instance of id "+animationInstanceID+" found, returning NULL");
        return NULL;
    }
    else{
        ofxAnimationInstance* original = animationInstances[animationInstanceID];
        ofxAnimation* anim = original->getAnimation();
        ofxAnimationInstance* c = original->clone();
        string ID = animationInstanceID+":"+ofToString(c);
        clonedAnimationInstances[ID] = c;
        return clonedAnimationInstances[ID];
    }
}

ofxAnimatableManager::~ofxAnimatableManager(){
    for(auto animation = animations.begin(); animation != animations.end(); ++animation){
        delete animation->second;
    }
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        delete animationInstance->second;
    }
    for(auto animationInstance = clonedAnimationInstances.begin(); animationInstance != clonedAnimationInstances.end(); ++animationInstance){
        delete animationInstance->second;
    }
}

void ofxAnimatableManager::load(ofxJSONElement animationData){
    if(animationData[ANIMATIONS] != ofxJSONElement::null){
        loadAnimations(animationData[ANIMATIONS]);
    }
    if(animationData[INSTANCES] != ofxJSONElement::null){
        loadInstances(animationData[INSTANCES]);
    }
}

void ofxAnimatableManager::loadAnimations(ofxJSONElement animationsData){
    vector<string> animationNames = animationsData.getMemberNames();
    for(string animationName : animationNames){
        ofxAnimation* animation = new ofxAnimation();
        animation->setName(animationName);
        animation->init(animationsData[animationName]);
        animations[animationName] = animation;
    }
}

void ofxAnimatableManager::loadInstances(ofxJSONElement instancesData){
    vector<string> instanceNames = instancesData.getMemberNames();
    for(string instanceName : instanceNames){
        ofxJSONElement animationInstanceData = instancesData[instanceName];
        if(animationInstanceData[ANIMATION] == ofxJSONElement::null){
            ofLogError("ofxAnimatableManager::loadInstances", "No animation name for animation instance '"+instanceName+"' found, ofxAnimationInstance requires a name of an ofxAnimation");
            continue;
        }
        string animationName = animationInstanceData[ANIMATION].asString();
        if(hasAnimation(animationName)){
            ofxAnimationInstance* animationInstance = getAnimation(animationName)->generateAnimationInstance(instanceName);
            animationInstance->init(animationInstanceData);
            animationInstances[instanceName] = animationInstance;
            
        }
        else{
            ofLogWarning("ofxAnimatableManager::loadInstances","Instance '"+instanceName+"' calls for animation '"+animationName+"', which does not exist");
        }
        
    }
}

map<string, ofxAnimation*>* ofxAnimatableManager::getAnimations(){
    return &animations;
}

map<string, ofxAnimationInstance*>* ofxAnimatableManager::getAnimationInstances(){
    return &animationInstances;
}
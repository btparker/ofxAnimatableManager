#include "ofxAnimationInstance.h"

ofxAnimationInstance::ofxAnimationInstance(){
}

ofxAnimationInstance::ofxAnimationInstance(ofxAnimation* animation){
    keyframeIndex = 0;
    this->delay = 0.0f;
    this->animation = animation;
}

void ofxAnimationInstance::update(float dt){
    ofxAnimatableFloat::update(dt);
    for(auto colorIt = colorAnimatables.begin(); colorIt != colorAnimatables.end(); ++colorIt){
        colorIt->second->update(dt);
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        floatIt->second->update(dt);
    }
    if(started){
        while(
              // While there is a next keyframe
              getNextKeyframe() != NULL &&
              // and while the current keyframe percentage is less than the percent done
              animation->getKeyframeSequence()[keyframeIndex+1]->getPercentage() <= ofxAnimatableFloat::getPercentDone()
              ){
            keyframeIndex++;
            animateToNextKeyframe();
        }
    }
    else if(isAnimating() && !started){
        if(animation->hasStartingKeyframe()){
            ofxAnimationKeyframe* startingKeyframe = animation->getStartingKeyframe();
            applyKeyframe(startingKeyframe);
        }
        animateToNextKeyframe();
        started = true;
    }
}

void ofxAnimationInstance::setID(string ID){
    this->ID = ID;
}

string ofxAnimationInstance::getID(){
    return this->ID;
}

void ofxAnimationInstance::setDelay(float delay){
    this->delay = delay;
}

float ofxAnimationInstance::getDelay(){
    return this->delay;
}

void ofxAnimationInstance::play(){
    if(getDelay() > 0){
        ofxAnimatableFloat::startAnimationAfterDelay(getDelay());
        started = false;
    }
    else{
        started = true;
    }
    for(auto colorIt = colorAnimatables.begin(); colorIt != colorAnimatables.end(); ++colorIt){
        colorIt->second->setCurve(this->curveStyle_);
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        floatIt->second->setCurve(this->curveStyle_);
    }
    
    
}

void ofxAnimationInstance::applyKeyframe(ofxAnimationKeyframe *keyframe){
    for(auto colorIt = colorAnimatables.begin(); colorIt != colorAnimatables.end(); ++colorIt){
        if(keyframe->hasColorValue(colorIt->first)){
            colorIt->second->setColor(keyframe->getColor(colorIt->first));
        }
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        if(keyframe->hasFloatValue(floatIt->first)){
            floatIt->second->reset(keyframe->getFloat(floatIt->first));
        }
    }
}

void ofxAnimationInstance::animateToKeyframe(ofxAnimationKeyframe *keyframe, float duration){
    for(auto colorIt = colorAnimatables.begin(); colorIt != colorAnimatables.end(); ++colorIt){
        if(keyframe->hasColorValue(colorIt->first)){
            colorIt->second->pause();
            colorIt->second->setDuration(duration);
            colorIt->second->animateTo(keyframe->getColor(colorIt->first));
        }
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        if(keyframe->hasFloatValue(floatIt->first)){
            floatIt->second->pause();
            floatIt->second->setDuration(duration);
            floatIt->second->animateTo(keyframe->getFloat(floatIt->first));
        }
    }
}

void ofxAnimationInstance::setAnimatable(string key, ofxAnimatableFloat* floatAnimatable){
    floatAnimatables[key] = floatAnimatable;
}

void ofxAnimationInstance::setAnimatable(string key, ofxAnimatableOfColor* colorAnimatable){
    colorAnimatables[key] = colorAnimatable;
}

ofxAnimationKeyframe* ofxAnimationInstance::getCurrentKeyframe(){
    return this->animation->getKeyframeSequence()[keyframeIndex];
}

ofxAnimationKeyframe* ofxAnimationInstance::getNextKeyframe(){
    if(keyframeIndex < animation->getKeyframeSequence().size()-1){
        return this->animation->getKeyframeSequence()[keyframeIndex+1];
    }
    else{
        return NULL;
    }
}

void ofxAnimationInstance::animateToNextKeyframe(){
    ofxAnimationKeyframe* curr;
    ofxAnimationKeyframe* next;
    curr = getCurrentKeyframe();
    next = getNextKeyframe();
    if(next != NULL){
        float percentDiff =(next->getPercentage() - curr->getPercentage());
        animateToKeyframe(next, percentDiff*getDuration());
    }
}
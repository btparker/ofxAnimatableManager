#include "ofxAnimationInstance.h"

ofxAnimationInstance::ofxAnimationInstance(){
}

ofxAnimationInstance::ofxAnimationInstance(ofxAnimation* animation){
    keyframeIndex = 0;
    this->delay = 0.0f;
    this->animation = animation;
    ofAddListener(this->animFinished, this,  &ofxAnimationInstance::finished);
}

void ofxAnimationInstance::finished(AnimationEvent & args){
    args.who->setPercentDone(0.0);
    args.who->pause();
    ((ofxAnimationInstance*)args.who)->keyframeIndex = 0;
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
              animation->getKeyframeSequence()[keyframeIndex]->getPercentage() < ofxAnimatableFloat::getPercentDone()
              )
        {
            animateToNextKeyframe();
            keyframeIndex++;
        }
    }
    else if(isAnimating() && !started){
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

void ofxAnimationInstance::setDuration(float duration){
    this->duration = duration;
}

float ofxAnimationInstance::getDuration(){
    return this->duration;
}

void ofxAnimationInstance::play(){
    if(getDelay() > 0){
        ofxAnimatableFloat::startAnimationAfterDelay(getDelay());
        started = false;
    }
    else{
        ofxAnimatableFloat::startAnimation();
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

void ofxAnimationInstance::setStateID(string stateID){
    this->stateID = stateID;
}

string ofxAnimationInstance::getStateID(){
    return stateID;
}
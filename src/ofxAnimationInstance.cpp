#include "ofxAnimationInstance.h"

ofxAnimationInstance::ofxAnimationInstance(){
    keyframeIndex = 0;
    this->delay = 0.0f;
    this->duration = 1.0f;
    this->setCurve(EASE_IN_EASE_OUT);
    this->setRepeatTimes(1);
    ofAddListener(this->animFinished, this,  &ofxAnimationInstance::finished);
}

//
//ofxAnimationInstance::ofxAnimationInstance(ofxAnimation* animation){
//    keyframeIndex = 0;
//    this->delay = 0.0f;
//    this->duration = 1.0f;
//    this->setCurve(EASE_IN_EASE_OUT);
//    this->setRepeatTimes(1);
//    this->animation = animation;
//    ofAddListener(this->animFinished, this,  &ofxAnimationInstance::finished);
//}

void ofxAnimationInstance::setAnimation(ofxAnimation* animation){
    this->animation = animation;
}

void ofxAnimationInstance::finished(AnimationEvent & args){
    args.who->setPercentDone(0.0);
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
    
    if(isAnimating() && !started){
        started = true;
    }
    
    if(started){
        if(keyframeIndex == 0){
            applyKeyframe(getCurrentKeyframe());
        }
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
    ofxAnimatableFloat::setDuration(duration);
    this->duration = duration;
}

float ofxAnimationInstance::getDuration(){
    return this->duration;
}

void ofxAnimationInstance::play(){
    keyframeIndex = 0;
    if(getDelay() > 0){
        ofxAnimatableFloat::startAnimationAfterDelay(getDelay());
        started = false;
    }
    else{
        ofxAnimatableFloat::startAnimation();
        started = true;
    }
    for(auto colorIt = colorAnimatables.begin(); colorIt != colorAnimatables.end(); ++colorIt){
        ofxAnimatableOfColor* c = colorIt->second;
        c->setCurve(this->curveStyle_);
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        ofxAnimatableFloat* f = floatIt->second;
        f->setCurve(this->curveStyle_);
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
            colorIt->second->setDuration(duration);
            colorIt->second->animateTo(keyframe->getColor(colorIt->first));
        }
    }
    for(auto floatIt = floatAnimatables.begin(); floatIt != floatAnimatables.end(); ++floatIt){
        if(keyframe->hasFloatValue(floatIt->first)){
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
        float percentDiff = (next->getPercentage() - curr->getPercentage());
        animateToKeyframe(next, percentDiff*getDuration());
    }
}

set<string> ofxAnimationInstance::getKeys(){
    return this->animation->getKeys();
}

void ofxAnimationInstance::trigger(){
    this->reset();
    this->play();
}

ofxAnimationInstance* ofxAnimationInstance::clone(){
    ofxAnimationInstance* c = animation->generateAnimationInstance(getID());
    c->setAnimation(this->animation);
    c->setDelay(this->getDelay());
    c->setDuration(this->getDuration());
    c->setCurve(this->curveStyle_);
    return c;
}

void ofxAnimationInstance::init(ofxJSONElement animationInstanceData){
    if(animationInstanceData[DURATION] != ofxJSONElement::null){
        setDuration(ofToFloat(animationInstanceData[DURATION].asString()));
    }
    if(animationInstanceData[DELAY] != ofxJSONElement::null){
        setDelay(ofToFloat(animationInstanceData[DELAY].asString()));
    }
    if(animationInstanceData[TIMING_FUNCTION] != ofxJSONElement::null){
        string timingFunc = animationInstanceData[TIMING_FUNCTION].asString();
        setCurve(ofxAnimatable::getCurveFromName(timingFunc));
    }
}

ofxAnimation* ofxAnimationInstance::getAnimation(){
    return animation;
}
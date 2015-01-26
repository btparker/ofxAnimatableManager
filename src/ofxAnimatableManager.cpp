#include "ofxAnimatableManager.h"

ofxAnimatableManager::ofxAnimatableManager(){
    activeAnimation = Animations::DEFAULT;
    animations[Animations::DEFAULT] = State();
    setCurve(EASE_IN_EASE_OUT);
    setup();
}

void ofxAnimatableManager::startAnimationDefinition(string animation){
    if(activeAnimation != Animations::DEFAULT){
        ofLogError("Currently defining animation "+activeAnimation+", close with endAnimationDefinition("+activeAnimation+") first.");
        return;
    }
    activeAnimation = animation;
    animations[animation] = State();
}

void ofxAnimatableManager::endAnimationDefinition(string animation){
    if(activeAnimation == Animations::DEFAULT){
        ofLogError("Not currently defining animation, open with endAnimationDefinition("+animation+") first.");
        return;
    }
    activeAnimation = Animations::DEFAULT;
}

void ofxAnimatableManager::update(float dt){
    ofxAnimatableFloat::update(dt);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->update(dt);
    }
}

void ofxAnimatableManager::animate(string key){
    string transitionAnimation = "";
    if(animations.count(activeAnimation+"->"+key) == 1){
        transitionAnimation = activeAnimation+"->"+key;
    }
    if(animations.count(key) == 0){
        ofLogError("No animation "+key+" found!");
        return;
    }
    // TODO: possibly remove - Don't transition in same animation
    if(key == activeAnimation){
        return;
    }
    activeAnimation = key;
    float animationDuration;
    if(transitionAnimation.length() > 0 && animations[transitionAnimation].duration >= 0){
        animationDuration = animations[transitionAnimation].duration;
    }
    else{
        animationDuration = animations[activeAnimation].duration;
    }
    ofxAnimatableFloat::setDuration(animationDuration);
    int animationDurationUnits = animations[activeAnimation].durationUnits;
    if(transitionAnimation.length() > 0 && animations[transitionAnimation].durationUnits >= 0){
        animationDurationUnits = animations[transitionAnimation].durationUnits;
    }
    for(auto iterator = animations[activeAnimation].animatableValues.begin(); iterator != animations[activeAnimation].animatableValues.end(); iterator++){
        
        string animatableKey = iterator->first;
        AnimatableValues animatableValues = animations[activeAnimation].animatableValues[animatableKey];
        
        int durationUnits = animatableValues.durationUnits;
        if(transitionAnimation.length() > 0 && animations[transitionAnimation].animatableValues[animatableKey].durationUnits >= 0){
            durationUnits = animations[transitionAnimation].animatableValues[animatableKey].durationUnits;
        }
        int delayUnits;
        if(transitionAnimation.length() > 0 && animations[transitionAnimation].animatableValues[animatableKey].delayUnits >= 0){
            delayUnits = animations[transitionAnimation].animatableValues[animatableKey].delayUnits;
            
        }
        else if(animations[activeAnimation].animatableValues[animatableKey].delayUnits >= 0){
            delayUnits = animatableValues.delayUnits;
            
        }
        else{
            delayUnits = 0;
        }
        
        if(animations[transitionAnimation].animatableValues[animatableKey].alignAnimation == AnimationAlignments::END || animations[activeAnimation].animatableValues[animatableKey].alignAnimation == AnimationAlignments::END){
            delayUnits = animationDurationUnits - durationUnits - delayUnits;
        }
        
        float animatableDuration = animationDuration*(durationUnits/(float)animationDurationUnits);
        float animatableDelay = animationDuration*(delayUnits/(float)animationDurationUnits);
        ofPoint targetPos;
        ofPoint origPos;
        ofColor targetColor;
        ofColor origColor;
        float targetFloat;
        float origFloat;
        float percent = animatables[animatableKey]->getPercentDone();
        float curveAtPercent =  animatables[animatableKey]->calcCurveAt(percent);
        animatables[animatableKey]->setCurve(animations[activeAnimation].curveStyle);
        animatables[animatableKey]->setDuration(animatableDuration);
        switch(animatableValues.type){
            case AnimatableTypes::POINT:
                targetPos = ((ofxAnimatableOfPoint*)animatables[animatableKey])->getTargetPosition();
                origPos = ((ofxAnimatableOfPoint*)animatables[animatableKey])->getOriginalPosition();
                ((ofxAnimatableOfPoint*)animatables[animatableKey])->setPosition(origPos.interpolate(targetPos, curveAtPercent));
                if(animatableDelay > 0.0){
                    ((ofxAnimatableOfPoint*)animatables[animatableKey])->animateToAfterDelay(animatableValues.endPoint,animatableDelay);
                }
                else{
                    ((ofxAnimatableOfPoint*)animatables[animatableKey])->animateTo(animatableValues.endPoint);
                }
                break;
            case AnimatableTypes::FLOAT:
                targetFloat = ((ofxAnimatableFloat*)animatables[animatableKey])->getTargetValue();
                origFloat = ((ofxAnimatableFloat*)animatables[animatableKey])->getOriginalValue();
                ((ofxAnimatableFloat*)animatables[animatableKey])->reset(ofMap(curveAtPercent, 0.0, 1.0, origFloat, targetFloat));
                if(animatableDelay > 0.0){
                    ((ofxAnimatableFloat*)animatables[animatableKey])->animateToAfterDelay(animatableValues.endFloat,animatableDelay);
                }
                else{
                    ((ofxAnimatableFloat*)animatables[animatableKey])->animateTo(animatableValues.endFloat);
                }
                break;
            case AnimatableTypes::COLOR:
                targetColor = ((ofxAnimatableOfColor*)animatables[animatableKey])->getTargetColor();
                origColor = ((ofxAnimatableOfColor*)animatables[animatableKey])->getOriginalColor();
                ((ofxAnimatableOfColor*)animatables[animatableKey])->setColor(origColor.getLerped(targetColor, curveAtPercent));
                if(animatableDelay > 0.0){
                    ((ofxAnimatableOfColor*)animatables[animatableKey])->animateToAfterDelay(animatableValues.endColor,animatableDelay);
                }
                else{
                    ((ofxAnimatableOfColor*)animatables[animatableKey])->animateTo(animatableValues.endColor);
                }
                break;
            default:
                ofLogError("No type found");
        }
    }
    ofxAnimatableFloat::animateFromTo(0.0,1.0);
}

void ofxAnimatableManager::animateTo(string key, ofPoint value, int durationUnits, int delayUnits, AnimationAlignments::ENUM alignAnimation){
    animations[activeAnimation].animatableValues[key].type = AnimatableTypes::POINT;
    animations[activeAnimation].animatableValues[key].endPoint = value;
    setDurationUnits(key,durationUnits);
    setDelayUnits(key,delayUnits,alignAnimation);
}

void ofxAnimatableManager::animateTo(string key, float value, int durationUnits, int delayUnits, AnimationAlignments::ENUM alignAnimation){
    animations[activeAnimation].animatableValues[key].type = AnimatableTypes::FLOAT;
    animations[activeAnimation].animatableValues[key].endFloat = value;
    setDurationUnits(key,durationUnits);
    setDelayUnits(key,delayUnits,alignAnimation);
}

void ofxAnimatableManager::animateTo(string key, ofColor value, int durationUnits, int delayUnits, AnimationAlignments::ENUM alignAnimation){
    animations[activeAnimation].animatableValues[key].type = AnimatableTypes::COLOR;
    animations[activeAnimation].animatableValues[key].endColor = value;
    setDurationUnits(key,durationUnits);
    setDelayUnits(key,delayUnits,alignAnimation);
}

void ofxAnimatableManager::startAnimationTransitionDefinition(string state1, string state2){
    startAnimationDefinition(state1+"->"+state2);
}

void ofxAnimatableManager::endAnimationTransitionDefinition(string state1, string state2){
    endAnimationDefinition(state1+"->"+state2);
}

void ofxAnimatableManager::addAnimatable(ofxAnimatable* animatable, string key){
    // If no key is provided, create unique key (perhaps a bit jankity, but I didn't want something "predictable")
    // And I want keys later as an option
    
    if(key == ""){
        key = ofToString(animatables.size())+"-"+ofToString(ofGetFrameNum());
    }
    animatables[key] = animatable;
    animations[activeAnimation].animatableValues[key].curveStyle = ofxAnimatableFloat::curveStyle_;
}

void ofxAnimatableManager::setCurve( AnimCurve curveStyle ){
    animations[activeAnimation].curveStyle = curveStyle;
    ofxAnimatableFloat::setCurve(curveStyle);
    for(auto iterator = animations[activeAnimation].animatableValues.begin(); iterator != animations[activeAnimation].animatableValues.end(); iterator++){
        animations[activeAnimation].animatableValues[iterator->first].curveStyle = curveStyle;
    }
}

void ofxAnimatableManager::setDurationUnits(string key, int units){
    if(animatables.count(key) == 0){
        return 0;
    }
    animations[activeAnimation].animatableValues[key].durationUnits = units;
    updateDurations();
    
}

void ofxAnimatableManager::setDelayUnits(string key, int units, AnimationAlignments::ENUM alignAnimation){
    if(animatables.count(key) == 0){
        return 0;
    }
    animations[activeAnimation].animatableValues[key].delayUnits = units;
    animations[activeAnimation].animatableValues[key].alignAnimation = alignAnimation;
    updateDurations();
}

void ofxAnimatableManager::setDuration(float duration){
    ofxAnimatableFloat::setDuration(duration);
    animations[activeAnimation].duration = duration;
    updateDurations();
}

void ofxAnimatableManager::updateDurations(){
    float duration = animations[activeAnimation].duration;
    int totalUnits = 0;
    for(auto iterator = animations[activeAnimation].animatableValues.begin(); iterator != animations[activeAnimation].animatableValues.end(); iterator++){
        int durationUnits = animations[activeAnimation].animatableValues[iterator->first].durationUnits >= 0 ? animations[activeAnimation].animatableValues[iterator->first].durationUnits : 0;
        int delayUnits = animations[activeAnimation].animatableValues[iterator->first].delayUnits >= 0 ? animations[activeAnimation].animatableValues[iterator->first].delayUnits : 0;
        totalUnits = (delayUnits+durationUnits) > totalUnits ? (delayUnits+durationUnits) : totalUnits;
    }
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->setDuration(duration*(animations[activeAnimation].animatableValues[iterator->first].durationUnits/(float)totalUnits));
    }
    animations[activeAnimation].durationUnits = totalUnits;
}

ofxAnimatableManager::~ofxAnimatableManager(){
}
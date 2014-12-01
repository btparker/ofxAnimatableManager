#include "ofxAnimatableManager.h"

ofxAnimatableManager::ofxAnimatableManager(){
    activeState = States::DEFAULT;
    states[States::DEFAULT] = State();
    setup();
}

void ofxAnimatableManager::startStateDefinition(string state){
    if(activeState != States::DEFAULT){
        ofLogError("Currently defining state "+activeState+", close with endStateDefinition("+activeState+") first.");
        return;
    }
    activeState = state;
    states[state] = State();
}

void ofxAnimatableManager::endStateDefinition(string state){
    if(activeState == States::DEFAULT){
        ofLogError("Not currently definining state, open with endStateDefinition("+state+") first.");
        return;
    }
    activeState = States::DEFAULT;
}

void ofxAnimatableManager::update(float dt){
    ofxAnimatableFloat::update(dt);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->update(dt);
    }
}

void ofxAnimatableManager::animateState(string key){
    string transitionState = "";
    if(states.count(activeState+"->"+key) == 1){
        transitionState = activeState+"->"+key;
    }
    if(states.count(key) == 0){
        ofLogError("No state "+key+" found!");
        return;
    }
    // TODO: possibly remove - Don't transition in same state
    if(key == activeState){
        return;
    }
    activeState = key;
    float stateDuration;
    if(transitionState.length() > 0 && states[transitionState].duration >= 0){
        stateDuration = states[transitionState].duration;
    }
    else{
        stateDuration = states[activeState].duration;
    }
    ofxAnimatableFloat::setDuration(stateDuration);
    for(auto iterator = states[activeState].animatableValues.begin(); iterator != states[activeState].animatableValues.end(); iterator++){
        string animatableKey = iterator->first;
        AnimatableValues animatableValues = states[activeState].animatableValues[animatableKey];
        int stateDurationUnits = states[activeState].durationUnits;
        if(transitionState.length() > 0 && states[transitionState].durationUnits >= 0){
            stateDurationUnits = states[transitionState].durationUnits;
        }
        int durationUnits = animatableValues.durationUnits;
        if(transitionState.length() > 0 && states[transitionState].animatableValues[animatableKey].durationUnits >= 0){
            durationUnits = states[transitionState].durationUnits;
        }
        float animatableDuration = stateDuration*(durationUnits/(float)stateDurationUnits);
        
        ofPoint targetPos;
        ofPoint origPos;
        ofColor targetColor;
        ofColor origColor;
        float targetFloat;
        float origFloat;
        float percent = animatables[animatableKey]->getPercentDone();
        float curveAtPercent =  animatables[animatableKey]->calcCurveAt(percent);
        animatables[animatableKey]->setCurve(states[activeState].curveStyle);
        animatables[animatableKey]->setDuration(animatableDuration);
        switch(animatableValues.type){
            case AnimatableTypes::POINT:
                targetPos = ((ofxAnimatableOfPoint*)animatables[animatableKey])->getTargetPosition();
                origPos = ((ofxAnimatableOfPoint*)animatables[animatableKey])->getOriginalPosition();
                ((ofxAnimatableOfPoint*)animatables[animatableKey])->setPosition(origPos.interpolate(targetPos, curveAtPercent));
                ((ofxAnimatableOfPoint*)animatables[animatableKey])->animateTo(animatableValues.endPoint);
                break;
            case AnimatableTypes::FLOAT:
                targetFloat = ((ofxAnimatableFloat*)animatables[animatableKey])->getTargetValue();
                origFloat = ((ofxAnimatableFloat*)animatables[animatableKey])->getOriginalValue();
                ((ofxAnimatableFloat*)animatables[animatableKey])->reset(ofMap(curveAtPercent, 0.0, 1.0, origFloat, targetFloat));
                ((ofxAnimatableFloat*)animatables[animatableKey])->animateTo(animatableValues.endFloat);
                break;
            case AnimatableTypes::COLOR:
                targetColor = ((ofxAnimatableOfColor*)animatables[animatableKey])->getTargetColor();
                origColor = ((ofxAnimatableOfColor*)animatables[animatableKey])->getOriginalColor();
                ((ofxAnimatableOfColor*)animatables[animatableKey])->setColor(origColor.getLerped(targetColor, curveAtPercent));
                ((ofxAnimatableOfColor*)animatables[animatableKey])->animateTo(animatableValues.endColor);
                break;
            default:
                ofLogError("No type found");
        }
    }
    ofxAnimatableFloat::animateFromTo(0.0,1.0);
}

void ofxAnimatableManager::animateTo(string key, ofPoint value, int durationUnits){
    states[activeState].animatableValues[key].type = AnimatableTypes::POINT;
    states[activeState].animatableValues[key].endPoint = value;
    setDurationUnits(key,durationUnits);
}

void ofxAnimatableManager::animateTo(string key, float value, int durationUnits){
    states[activeState].animatableValues[key].type = AnimatableTypes::FLOAT;
    states[activeState].animatableValues[key].endFloat = value;
    setDurationUnits(key,durationUnits);
}

void ofxAnimatableManager::animateTo(string key, ofColor value, int durationUnits){
    states[activeState].animatableValues[key].type = AnimatableTypes::COLOR;
    states[activeState].animatableValues[key].endColor = value;
    setDurationUnits(key,durationUnits);
}

void ofxAnimatableManager::startStateTransitionDefinition(string state1, string state2){
    startStateDefinition(state1+"->"+state2);
}

void ofxAnimatableManager::endStateTransitionDefinition(string state1, string state2){
    endStateDefinition(state1+"->"+state2);
}

void ofxAnimatableManager::addAnimatable(ofxAnimatable* animatable, string key){
    // If no key is provided, create unique key (perhaps a bit jankity, but I didn't want something "predictable")
    // And I want keys later as an option
    
    if(key == ""){
        key = ofToString(animatables.size())+"-"+ofToString(ofGetFrameNum());
    }
    animatables[key] = animatable;
    states[activeState].animatableValues[key].curveStyle = ofxAnimatable::curveStyle_;
}

void ofxAnimatableManager::setCurve( AnimCurve curveStyle ){
    states[activeState].curveStyle = curveStyle;
}

void ofxAnimatableManager::startAfterWait(){
}

void ofxAnimatableManager::setDurationUnits(string key, int units){
    if(animatables.count(key) == 0){
        return 0;
    }
    states[activeState].animatableValues[key].durationUnits = units;
    updateDurations();
    
}

void ofxAnimatableManager::setDuration(float duration){
    ofxAnimatableFloat::setDuration(duration);
    states[activeState].duration = duration;
    updateDurations();
}

void ofxAnimatableManager::updateDurations(){
    float duration = states[activeState].duration;
    int totalUnits = 0;
    for(auto iterator = states[activeState].animatableValues.begin(); iterator != states[activeState].animatableValues.end(); iterator++){
        totalUnits = states[activeState].animatableValues[iterator->first].durationUnits > totalUnits ? states[activeState].animatableValues[iterator->first].durationUnits : totalUnits;
    }
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->setDuration(duration*(states[activeState].animatableValues[iterator->first].durationUnits/(float)totalUnits));
    }
    states[activeState].durationUnits = totalUnits;
}

ofxAnimatableManager::~ofxAnimatableManager(){
}
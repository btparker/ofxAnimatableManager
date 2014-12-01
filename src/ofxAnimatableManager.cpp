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
    ofxAnimatable::update(dt);
    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
        animatables[iterator->first]->update(dt);
    }
}

void ofxAnimatableManager::animateState(string key){
    if(states.count(key) == 0){
        ofLogError("No state "+key+" found!");
        return;
    }
    // TODO: possibly remove - Don't transition in same state
    if(key == activeState){
        return;
    }
    activeState = key;
    ofxAnimatable::setDuration(states[activeState].duration);
    for(auto iterator = states[activeState].animatableValues.begin(); iterator != states[activeState].animatableValues.end(); iterator++){
        string animatableKey = iterator->first;
        AnimatableValues animatableValues = states[activeState].animatableValues[animatableKey];
        float animatableDuration = states[activeState].duration*(animatableValues.durationUnits/(float)states[activeState].durationUnits);
        
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

void ofxAnimatableManager::addAnimatable(ofxAnimatable* animatable, string key){
    // If no key is provided, create unique key (perhaps a bit jankity, but I didn't want something "predictable")
    // And I want keys later as an option
    
    if(key == ""){
        key = ofToString(animatables.size())+"-"+ofToString(ofGetFrameNum());
    }
    animatables[key] = animatable;
    states[activeState].animatableValues[key].curveStyle = ofxAnimatable::curveStyle_;
}

void ofxAnimatableManager::setRepeatType( AnimRepeat repeat ){
//    ofxAnimatable::setRepeatType(repeat);
//    for(auto iterator = animatables.begin(); iterator != animatables.end(); iterator++){
//        animatables[iterator->first]->setRepeatType(repeat);
//    }
}

void ofxAnimatableManager::setCurve( AnimCurve curveStyle ){
    states[activeState].curveStyle = curveStyle;
}

void ofxAnimatableManager::startAfterWait(){
}

void ofxAnimatableManager::setDurationUnits(string key, int units){
    states[activeState].animatableValues[key].durationUnits = units;
    updateDurations();
    
}

void ofxAnimatableManager::setDuration(float duration){
    ofxAnimatable::setDuration(duration);
    states[activeState].duration = duration;
    updateDurations();
}

void ofxAnimatableManager::updateDurations(){
    float duration = states[activeState].duration;
    int totalUnits = 0;
    for(auto iterator = states[activeState].animatableValues.begin(); iterator != states[activeState].animatableValues.end(); iterator++){
        totalUnits = states[activeState].animatableValues[iterator->first].durationUnits > totalUnits ? states[activeState].animatableValues[iterator->first].durationUnits : totalUnits;
    }
    states[activeState].durationUnits = totalUnits;
}

ofxAnimatableManager::~ofxAnimatableManager(){
}
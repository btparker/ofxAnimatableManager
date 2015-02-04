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
    
    
    float percentDone = ofxAnimatableFloat::getPercentDone();
    while(
        // While there is a next keyframe
        keyframeIndex < animation->getKeyframeSequence().size()-1 &&
        // and while the current keyframe percentage is less than the percent done
        animation->getKeyframeSequence()[keyframeIndex+1]->getPercentage() <= percentDone
    ){
        keyframeIndex++;
        applyKeyframe(getCurrentKeyframe());
    }
//    cout << "[" << percentDone << ","<< getDuration() << "," << getCurrentKeyframe()->getPercentageKey() << "]" << endl;
}

void ofxAnimationInstance::setID(string ID){
    this->ID = ID;
}

string ofxAnimationInstance::getID(){
    return this->ID;
}

void ofxAnimationInstance::play(){
    getCurrentKeyframe()->print();
    ofxAnimatableFloat::startAnimation();
    if(animation->hasStartingKeyframe()){
        ofxAnimationKeyframe* startingKeyframe = animation->getStartingKeyframe();
        applyKeyframe(startingKeyframe);
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

void ofxAnimationInstance::setAnimatable(string key, ofxAnimatableFloat* floatAnimatable){
    floatAnimatables[key] = floatAnimatable;
}

void ofxAnimationInstance::setAnimatable(string key, ofxAnimatableOfColor* colorAnimatable){
    colorAnimatables[key] = colorAnimatable;
}

ofxAnimationKeyframe* ofxAnimationInstance::getCurrentKeyframe(){
    return this->animation->getKeyframeSequence()[keyframeIndex];
}
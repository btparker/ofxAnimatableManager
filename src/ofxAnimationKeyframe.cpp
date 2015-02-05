#include "ofxAnimationKeyframe.h"

ofxAnimationKeyframe::ofxAnimationKeyframe(){
    percentageKey = "0%";
    percentage = 0.0f;
}

void ofxAnimationKeyframe::setPercentage(float percentage){
    this->percentage = percentage;
}

float ofxAnimationKeyframe::getPercentage(){
    return this->percentage;
}

void ofxAnimationKeyframe::setPercentageKey(string percentageKey){
    this->percentageKey = percentageKey;
}

string ofxAnimationKeyframe::getPercentageKey(){
    return this->percentageKey;
}

void ofxAnimationKeyframe::setValue(string key, ofColor value){
    colorValues[key] = value;
    keys.insert(key);
}

void ofxAnimationKeyframe::setValue(string key, float value){
    floatValues[key] = value;
    keys.insert(key);
}

bool ofxAnimationKeyframe::hasValue(string key){
    return hasColorValue(key) || hasFloatValue(key);
}

bool ofxAnimationKeyframe::hasColorValue(string key){
    return colorValues.count(key) > 0;
}

bool ofxAnimationKeyframe::hasFloatValue(string key){
    return floatValues.count(key) > 0;
}

ofColor ofxAnimationKeyframe::getColor(string key){
    return colorValues[key];
}

float ofxAnimationKeyframe::getFloat(string key){
    return floatValues[key];
}

string ofxAnimationKeyframe::getValueType(string key){
    if(colorValues.count(key)>0){
        return "color";
    }
    else if(floatValues.count(key) > 0){
        return "float";
    }
    else{
        return "";
    }
}

set<string> ofxAnimationKeyframe::getKeys(){
    return keys;
}

void ofxAnimationKeyframe::print(){
    cout << " === " << getPercentageKey() << " === " << endl;
    for(auto colorIt = colorValues.begin(); colorIt != colorValues.end(); ++colorIt){
        cout << "   [" << colorIt->first << ", " << colorIt->second << "]" << endl;
    }
    for(auto floatIt = floatValues.begin(); floatIt != floatValues.end(); ++floatIt){
        cout << "   [" << floatIt->first << ", " << floatIt->second << "]" << endl;
    }
    cout << " =========== " << endl;
}
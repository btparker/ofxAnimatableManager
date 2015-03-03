#pragma once
#include "ofMain.h"

class ofxAnimationKeyframe{
public:
    ofxAnimationKeyframe();
    float getPercentage();
    string getPercentageKey();
    void setPercentage(float percentage);
    void setPercentageKey(string percentageKey);
    void setValue(string key, ofColor value);
    void setValue(string key, float value);
    ofColor getColor(string key);
    float getFloat(string key);
    string getValueType(string key);
    void print();
    bool hasValue(string key);
    bool hasFloatValue(string key);
    bool hasColorValue(string key);
    set<string> getKeys();
protected:
    string percentageKey;
    float percentage;
    map<string, ofColor> colorValues;
    map<string, float> floatValues;
    
    set<string> keys;
};

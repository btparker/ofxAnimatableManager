#include "ofxAnimation.h"

ofxAnimation::ofxAnimation(){
    addKeyframe("0%");
}

void ofxAnimation::setName(string name){
    this->name = name;
}

string ofxAnimation::getName(){
    return this->name;
}

ofxAnimationKeyframe* ofxAnimation::addKeyframe(string keyframePercent){
    // Cleaner naming conventions
    if(keyframePercent == "from"){
        keyframePercent = "0%";
    }
    else if(keyframePercent == "to"){
        keyframePercent = "100%";
    }
    
    float percent = ofToFloat(keyframePercent)/100.0f;
    
    if(keyframes.count(keyframePercent) > 0){
        int index = ofFind(keyframeSequence, &keyframes[keyframePercent]);
        keyframeSequence.erase(keyframeSequence.begin() + index);
    }
    keyframes[keyframePercent] = ofxAnimationKeyframe();
    keyframeSequence.push_back(&keyframes[keyframePercent]);
    
    keyframes[keyframePercent].setPercentage(percent);
    
    keyframes[keyframePercent].setPercentageKey(keyframePercent);
    
    ofSort(keyframeSequence,ofxAnimation::keyframeCompare);
    
    return &keyframes[keyframePercent];
}

set<string> ofxAnimation::getKeys(){
    set<string> keys;
    for(ofxAnimationKeyframe* keyframe : getKeyframeSequence()){
        for(string key : keyframe->getKeys()){
            keys.insert(key);
        }
    }
    return keys;
}

vector<ofxAnimationKeyframe*> ofxAnimation::getKeyframeSequence(){
    return this->keyframeSequence;
}

ofxAnimationInstance* ofxAnimation::generateAnimationInstance(string ID){
    ofxAnimationInstance* animInst = new ofxAnimationInstance();
    animInst->setID(ID);
    animInst->setAnimation(this);
    return animInst;
}

void ofxAnimation::init(ofxJSONElement animationData){
    vector<string> keyframeIndices = animationData.getMemberNames();
    for(string keyframeIndex : keyframeIndices){
        ofxAnimationKeyframe* keyframe = addKeyframe(keyframeIndex);
        vector<string> animatableKeys = animationData[keyframeIndex].getMemberNames();
        for(string animatableKey : animatableKeys){
            string value = animationData[keyframeIndex][animatableKey].asString();
            if(isColor(value)){
                keyframe->setValue(animatableKey, parseColor(value));
            }
            else{
                keyframe->setValue(animatableKey, ofToFloat(value));
            }
        }
    }
}

bool ofxAnimation::isColor(string colorStr){
    bool isHex = ofIsStringInString(colorStr,"#");
    bool isRGB = ofIsStringInString(colorStr,"rgb(") || ofIsStringInString(colorStr,"rgba(");
    return isHex || isRGB;
}

ofColor ofxAnimation::parseColor(string colorValue){
    ofColor color;
    
    // If given color in html hex form (#FF0000)
    if(ofIsStringInString(colorValue,"#")){
        int hex = ofHexToInt(ofSplitString(colorValue,"#")[1]);
        color = ofColor::fromHex(hex);
    }
    // If given color in rgb() or rgba() form
    else if(ofIsStringInString(colorValue,"rgb(") || ofIsStringInString(colorValue,"rgba(")){
        // Substring in C++ is annoying, starting index and length
        // Using the parenthesis and end of string
        int si = colorValue.find("(")+1;
        int l = colorValue.length()-si-1;
        
        // From 'rgb(255,0,128)', would get '255,0,128'
        string commaSeparatedChannels = colorValue.substr(si,l);
        
        //splitting string form '255,0,128' into array [255,0,128]
        vector<string> splitChannels = ofSplitString(commaSeparatedChannels,",");
        
        // Color channels
        int r = ofToInt(splitChannels[0]);
        int g = ofToInt(splitChannels[1]);
        int b = ofToInt(splitChannels[2]);
        color.set(r,g,b);
        // Alpha support
        if(splitChannels.size() == 4){
            int a = ofToInt(splitChannels[3]);
            color = ofColor(color, a);
        }
    }
    else{
        ofLogWarning("ofxAnimation::parseColor","Could not parse "+colorValue+" to ofColor, returning ofColor::black");
        color = ofColor::black;
    }
    return color;
}

ofxAnimation::~ofxAnimation(){
}
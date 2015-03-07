#include "ofxAnimatableManager.h"


ofxAnimatableManager::ofxAnimatableManager(){
    
}

void ofxAnimatableManager::update(float dt){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        animationInstance->second->update(dt);
    }
    for(auto animationInstance = clonedAnimationInstances.begin(); animationInstance != clonedAnimationInstances.end(); ++animationInstance){
        animationInstance->second->update(dt);
    }
}

ofxAnimation* ofxAnimatableManager::addAnimation(string animationName){
    if(animations.count(animationName) > 0){
        ofLogWarning("ofxAnimatableManager::addAnimation","Animation "+animationName+" already present, reinitialized");
    }
    animations[animationName] = new ofxAnimation();
    animations[animationName]->setName(animationName);
    return animations[animationName];
}

bool ofxAnimatableManager::hasAnimation(string animationName){
    return animations.count(animationName) > 0;
}


bool ofxAnimatableManager::hasAnimationInstance(string animationInstanceID){
    return animationInstances.count(animationInstanceID) > 0 || clonedAnimationInstances.count(animationInstanceID) > 0;
}


ofxAnimation* ofxAnimatableManager::getAnimation(string animationName){
    if(hasAnimation(animationName)){
        return animations[animationName];
    }
    else{
        return NULL;
    }
}

ofxAnimationInstance* ofxAnimatableManager::getAnimationInstance(string animationInstanceID){
    if(hasAnimationInstance(animationInstanceID)){
        return animationInstances[animationInstanceID];
    }
    else{
        return NULL;
    }
}

ofxAnimationInstance* ofxAnimatableManager::generateAnimationInstance(string animationName, string animationInstanceID){
    if(animations.count(animationName) == 0){
        ofLogError("ofxAnimatableManager::generateAnimationInstance", "No animation of name "+animationName+" found, ofxAnimationInstance requires ofxAnimation, returning NULL");
        return NULL;
    }
    else{
        animationInstances[animationInstanceID] = new ofxAnimationInstance(animations[animationName]);
        animationInstances[animationInstanceID]->setID(animationInstanceID);
        return animationInstances[animationInstanceID];
    }
}

ofxAnimationInstance* ofxAnimatableManager::cloneAnimationInstance(string animationInstanceID){
    if(animationInstances.count(animationInstanceID) == 0){
        ofLogError("ofxAnimatableManager::generateAnimationInstance", "No animation instance of id "+animationInstanceID+" found, returning NULL");
        return NULL;
    }
    else{
        ofxAnimationInstance* c = new ofxAnimationInstance();
        animationInstances[animationInstanceID]->clone(c);
        string ID = animationInstanceID+":"+ofToString(c);
        clonedAnimationInstances[ID] = c;
        clonedAnimationInstances[ID]->setID(ID);
        return clonedAnimationInstances[ID];
    }
}

void ofxAnimatableManager::triggerAnimationInstance(string animationInstanceID){
    if(animationInstances[animationInstanceID]){
        animationInstances[animationInstanceID]->reset();
        animationInstances[animationInstanceID]->play();
    }
    else if(clonedAnimationInstances[animationInstanceID]){
        clonedAnimationInstances[animationInstanceID]->reset();
        clonedAnimationInstances[animationInstanceID]->play();
    }
}

ofxAnimatableManager::~ofxAnimatableManager(){
    for(auto animationInstance = animationInstances.begin(); animationInstance != animationInstances.end(); ++animationInstance){
        delete animationInstance->second;
    }
}

AnimCurve ofxAnimatableManager::getCurveFromName(string name){
    if(name == "EASE_IN_EASE_OUT"){
        return EASE_IN_EASE_OUT;
    }
    else if(name == "EASE_IN"){
        return EASE_IN;
    }
    else if(name == "EASE_OUT"){
        return EASE_OUT;
    }
    else if(name == "LINEAR"){
        return LINEAR;
    }
    else if(name == "BOUNCY"){
        return BOUNCY;
    }
    else if(name == "TANH"){
        return TANH;
    }
    else if(name == "SINH"){
        return SINH;
    }
    else if(name == "SQUARE"){
        return SQUARE;
    }
    else if(name == "LATE_SQUARE"){
        return LATE_SQUARE;
    }
    else if(name == "EARLY_SQUARE"){
        return EARLY_SQUARE;
    }
    else if(name == "BLINK_5"){
        return BLINK_5;
    }
    else if(name == "BLINK_3"){
        return BLINK_3;
    }
    else if(name == "BLINK_2"){
        return BLINK_2;
    }
    else if(name == "BLINK_AND_FADE_1"){
        return BLINK_AND_FADE_1;
    }
    else if(name == "BLINK_AND_FADE_2"){
        return BLINK_AND_FADE_2;
    }
    else if(name == "BLINK_AND_FADE_3"){
        return BLINK_AND_FADE_3;
    }
    else if(name == "LATE_LINEAR"){
        return LATE_LINEAR;
    }
    else if(name == "LATE_EASE_IN_EASE_OUT"){
        return LATE_EASE_IN_EASE_OUT;
    }
    else if(name == "EARLY_LINEAR"){
        return EARLY_LINEAR;
    }
    else if(name == "VERY_LATE_LINEAR"){
        return VERY_LATE_LINEAR;
    }
    else if(name == "VERY_LATE_EASE_IN_EASE_OUT"){
        return VERY_LATE_EASE_IN_EASE_OUT;
    }
    else if(name == "QUADRATIC_EASE_IN"){
        return QUADRATIC_EASE_IN;
    }
    else if(name == "QUADRATIC_EASE_OUT"){
        return QUADRATIC_EASE_OUT;
    }
    else if(name == "EARLY_QUADRATIC_EASE_OUT"){
        return EARLY_QUADRATIC_EASE_OUT;
    }
    else if(name == "QUADRATIC_BEZIER_PARAM"){
        return QUADRATIC_BEZIER_PARAM;
    }
    else if(name == "CUBIC_BEZIER_PARAM"){
        return CUBIC_BEZIER_PARAM;
    }
    else if(name == "EXPONENTIAL_SIGMOID_PARAM"){
        return EXPONENTIAL_SIGMOID_PARAM;
    }
    else if(name == "SWIFT_GOOGLE"){
        return SWIFT_GOOGLE;
    }
    else if(name == "OBJECT_DROP"){
        return OBJECT_DROP;
    }
    else if(name == "EASE_IN_BACK"){
        return EASE_IN_BACK;
    }
    else if(name == "EASE_OUT_BACK"){
        return EASE_OUT_BACK;
    }
    else if(name == "EASE_IN_OUT_BACK"){
        return EASE_IN_OUT_BACK;
    }
    else if(name == "EASE_OUT_IN_BACK"){
        return EASE_OUT_IN_BACK;
    }
        
    else if(name == "EASE_IN_BOUNCE"){
        return EASE_IN_BOUNCE;
    }
    else if(name == "EASE_OUT_BOUNCE"){
        return EASE_OUT_BOUNCE;
    }
    else if(name == "EASE_IN_OUT_BOUNCE"){
        return EASE_IN_OUT_BOUNCE;
    }
    else if(name == "EASE_OUT_IN_BOUNCE"){
        return EASE_OUT_IN_BOUNCE;
    }
        
    else if(name == "EASE_IN_ELASTIC"){
        return EASE_IN_ELASTIC;
    }
    else if(name == "EASE_OUT_ELASTIC"){
        return EASE_OUT_ELASTIC;
    }
    else if(name == "EASE_IN_OUT_ELASTIC"){
        return EASE_IN_OUT_ELASTIC;
    }
    else if(name == "EASE_OUT_IN_ELASTIC"){
        return EASE_OUT_IN_ELASTIC;
    }
    else{
        return LINEAR;
    }
}

void ofxAnimatableManager::load(string filename){
    ofxJSONElement animationData;
    if(animationData.open(filename)){
        if(animationData[ANIMATIONS] != ofxJSONElement::null){
            loadAnimations(animationData[ANIMATIONS]);
        }
        if(animationData[INSTANCES] != ofxJSONElement::null){
            loadInstances(animationData[INSTANCES]);
        }
    }
}

void ofxAnimatableManager::loadAnimations(ofxJSONElement animationsData){
    vector<string> animationNames = animationsData.getMemberNames();
    for(string animationName : animationNames){
        animationName = populateExpressions(animationName);
        ofxAnimation* animation = addAnimation(animationName);
        vector<string> keyframeIndices = animationsData[animationName].getMemberNames();
        for(string keyframeIndex : keyframeIndices){
            keyframeIndex = populateExpressions(keyframeIndex);
            ofxAnimationKeyframe* keyframe = animation->addKeyframe(keyframeIndex);
            vector<string> animatableKeys = animationsData[animationName][keyframeIndex].getMemberNames();
            for(string animatableKey : animatableKeys){
                animatableKey = populateExpressions(animatableKey);
                string value = animationsData[animationName][keyframeIndex][animatableKey].asString();
                value = populateExpressions(value);
                if(isColor(value)){
                    keyframe->setValue(animatableKey, parseColor(value));
                }
                else{
                    keyframe->setValue(animatableKey, ofToFloat(value));
                }
            }
        }
    }
}

void ofxAnimatableManager::loadInstances(ofxJSONElement instancesData){
    vector<string> instanceNames = instancesData.getMemberNames();
    for(string instanceName : instanceNames){
        ofxJSONElement animationInstanceData = instancesData[instanceName];
        if(animationInstanceData[ANIMATION] == ofxJSONElement::null){
            ofLogError("ofxAnimatableManager::loadInstances", "No animation name for animation instance '"+instanceName+"' found, ofxAnimationInstance requires a name of an ofxAnimation");
            continue;
        }
        string animationName = animationInstanceData[ANIMATION].asString();
        ofxAnimationInstance* animationInstance = generateAnimationInstance(animationName, instanceName);
        if(animationInstanceData[DURATION] != ofxJSONElement::null){
            animationInstance->setDuration(ofToFloat(animationInstanceData[DURATION].asString()));
        }
        if(animationInstanceData[DELAY] != ofxJSONElement::null){
            animationInstance->setDelay(ofToFloat(animationInstanceData[DELAY].asString()));
        }
        if(animationInstanceData[TIMING_FUNCTION] != ofxJSONElement::null){
            animationInstance->setCurve(getCurveFromName(animationInstanceData[TIMING_FUNCTION].asString()));
        }
    }
}

bool ofxAnimatableManager::isColor(string colorStr){
    bool isHex = ofIsStringInString(colorStr,"#");
    bool isRGB = ofIsStringInString(colorStr,"rgb(") || ofIsStringInString(colorStr,"rgba(");
    return isHex || isRGB;
}

ofColor ofxAnimatableManager::parseColor(string colorValue){
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
        ofLogWarning("ofxAnimationKeyframe::parseColor","Could not parse "+colorValue+" to ofColor, returning ofColor::black");
        color = ofColor::black;
    }
    return color;
}

string ofxAnimatableManager::populateExpressions(string input){
    string value = input;
    while(ofStringTimesInString(value, "{{") > 0){
        string leftDeliminator = "{{";
        string rightDeliminator = "}}";
        
        int leftDeliminatorPos = input.find(leftDeliminator);
        int rightDeliminatorPos = input.find(rightDeliminator);
        
        int dataKeyPos = leftDeliminatorPos+leftDeliminator.length();
        int dataKeyLength = rightDeliminatorPos-dataKeyPos;
        
        string dataKey = input.substr(dataKeyPos, dataKeyLength);
        
        if(data.count(dataKey) > 0){
            ofStringReplace(value, leftDeliminator+dataKey+rightDeliminator, data[dataKey]);
        }
        else{
            ofLogWarning("ofxLayout::populateExpressions","Could not find data value for key '{{"+dataKey+"}}', replaced with ''.");
            ofStringReplace(value, leftDeliminator+dataKey+rightDeliminator, "");
        }
    }
    return value;
}

void ofxAnimatableManager::setData(map<string, string> data){
    this->data = data;
}

map<string, ofxAnimation*>* ofxAnimatableManager::getAnimations(){
    return &animations;
}

map<string, ofxAnimationInstance*>* ofxAnimatableManager::getAnimationInstances(){
    return &animationInstances;
}
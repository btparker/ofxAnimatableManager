#include "ofxAnimation.h"

ofxAnimation::ofxAnimation(){
}

void ofxAnimation::setName(string name){
    this->name = name;
}

string ofxAnimation::getName(){
    return this->name;
}

ofxAnimation::~ofxAnimation(){
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(28);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    //
    //  Like the basic example
    //
    
    ofxAnimation* ballAAnimation = ballAnimationManager.addAnimation("ball-a-animation");
    ofxAnimationKeyframe* keyframeA = ballAAnimation->addKeyframe("75%");
    keyframeA->setValue("background-color", ofColor::blue);
    keyframeA->setValue("x", (ofGetWidth()/2+75.0f));
    
    ofxAnimationKeyframe* keyframeB = ballAAnimation->addKeyframe("50%");
    keyframeB->setValue("background-color", ofColor::green);
    keyframeB->setValue("x", (ofGetWidth()/2+50.0f));
    
    ofxAnimationKeyframe* keyframeC = ballAAnimation->addKeyframe("25%");
    keyframeC->setValue("background-color", ofColor::orange);
    keyframeC->setValue("x", (ofGetWidth()/2+25.0f));
    
    ofxAnimationKeyframe* keyframeD = ballAAnimation->addKeyframe("100%");
    keyframeD->setValue("background-color", ofColor::purple);
    keyframeD->setValue("x", (ofGetWidth()/2+100.0f));
    
    ofxAnimationKeyframe* keyframeE = ballAAnimation->addKeyframe("0%");
    keyframeE->setValue("background-color", ofColor::red);
    keyframeE->setValue("x", ofGetWidth()/2);
    keyframeE->setValue("y", ofGetWidth()/2);
    
    ofxAnimationInstance* animInstance = ballAnimationManager.generateAnimationInstance("ball-a-animation", "ball-a-instance");
    animInstance->setDuration(5.0);
    animInstance->setDelay(5.0);
    animInstance->setAnimatable("background-color", &ballA.color);
    animInstance->setAnimatable("x", &ballA.x);
    animInstance->setAnimatable("y", &ballA.y);
    animInstance->setCurve(LINEAR);
    animInstance->play();
}

//--------------------------------------------------------------
void ofApp::update(){
    // ballB
    ballAnimationManager.update( 1.0f/ofGetFrameRate() );
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ballB
//    ofBackground(ballA.color.getCurrentColor());
    ofSetColor(ballA.color.getCurrentColor());
    ofFill();
    ofCircle(ballA.x.getCurrentValue(), ballA.y.getCurrentValue(), 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

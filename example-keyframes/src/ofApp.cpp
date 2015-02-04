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
    keyframeA->setValue("background-color", ofColor::green);
    
    ofxAnimationKeyframe* keyframeB = ballAAnimation->addKeyframe("50%");
    keyframeB->setValue("background-color", ofColor::blue);
    
    ofxAnimationKeyframe* keyframeC = ballAAnimation->addKeyframe("25%");
    keyframeC->setValue("background-color", ofColor::red);
    
    ofxAnimationKeyframe* keyframeD = ballAAnimation->addKeyframe("100%");
    keyframeD->setValue("background-color", ofColor::orange);
    
    ofxAnimationKeyframe* keyframeE = ballAAnimation->addKeyframe("0%");
    keyframeE->setValue("background-color", ofColor::purple);
    
    ofxAnimationInstance* animInstance = ballAnimationManager.generateAnimationInstance("ball-a-animation", "ball-a-instance");
    animInstance->setDuration(2);
    animInstance->setAnimatable("background-color", &ballA.color);
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
    ofBackground(ballA.color.getCurrentColor());
    ofSetColor(ballA.color.getCurrentColor());
    ofFill();
    ofCircle(ballA.pos.getCurrentPosition().x, ballA.pos.getCurrentPosition().y, ballA.s);
    
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

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
    ballB.color.setup();
    
    
    
    ofxAnimation* ballAnimation = ballAnimationManager.addAnimation("ball-animation");
    
    ofxAnimationKeyframe* keyframeE = ballAnimation->addKeyframe("0%");
    keyframeE->setValue("left", 50.0f);
    keyframeE->setValue("top", 50.0f);
    
    ofxAnimationKeyframe* keyframeA = ballAnimation->addKeyframe("75%");
    keyframeA->setValue("background-color", ofColor::green);
    
    ofxAnimationKeyframe* keyframeB = ballAnimation->addKeyframe("50%");
    keyframeB->setValue("background-color", ofColor::blue);
    
    ofxAnimationKeyframe* keyframeC = ballAnimation->addKeyframe("25%");
    keyframeC->setValue("background-color", ofColor::red);
    keyframeC->setValue("scale", 20.0f);
    
    ofxAnimationKeyframe* keyframeD = ballAnimation->addKeyframe("100%");
    keyframeD->setValue("background-color", ofColor::orange);
    keyframeD->setValue("scale", 5.0f);
    
    ofxAnimationInstance* animInstanceA = ballAnimationManager.generateAnimationInstance("ball-animation", "ball-a-instance");
    
    animInstanceA->addAnimatable("background-color", &ballA.color);
    
    animInstanceA->addAnimatable("left", &ballA.x);
    
    animInstanceA->addAnimatable("top", &ballA.y);
    
    animInstanceA->addAnimatable("scale", &ballA.s);
    
    animInstanceA->setDuration(5.0f);
    animInstanceA->setDelay(5.0f);
    ofxAnimationInstance* animInstanceB = ballAnimationManager.generateAnimationInstance("ball-animation", "ball-b-instance");
    
    animInstanceB->addAnimatable("background-color", &ballB.color);
    
    animInstanceB->addAnimatable("left", &ballB.x);
    
    animInstanceB->addAnimatable("top", &ballB.y);
    
    animInstanceB->addAnimatable("scale", &ballB.s);
    
    animInstanceB->setDuration(10.0f);
    
    ballAnimationManager.triggerAnimationInstance("ball-a-instance");
    ballAnimationManager.triggerAnimationInstance("ball-b-instance");
}

//--------------------------------------------------------------
void ofApp::update(){
    // ballB
    ballAnimationManager.update( 1.0f/ofGetFrameRate() );
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ballB
    ofBackground(20);
    
    ofSetColor(ballA.color.getCurrentColor());
    ofFill();
    ofCircle(ballA.x.getCurrentValue()+50, ballA.y.getCurrentValue(), ballA.s.getCurrentValue());

    ofSetColor(ballB.color.getCurrentColor());
    ofFill();
    ofCircle(ballB.x.getCurrentValue(), ballB.y.getCurrentValue(), ballB.s.getCurrentValue());
    
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

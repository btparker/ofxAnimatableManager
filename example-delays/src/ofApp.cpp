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
    
    ballAnimationManager.addAnimatable(&ballB.pos,"position");
    ballB.pos.setPosition( ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.33) );
    
    ballAnimationManager.addAnimatable(&ballB.s,"scale");
    ballB.s.reset(5.0);
    
    ballAnimationManager.addAnimatable(&ballB.color,"color");
    ballB.color.setColor(ofColor::grey);
    
    // Setting
    ballAnimationManager.startStateDefinition(States::STATE1);
    ballAnimationManager.setCurve(EASE_IN_EASE_OUT);
    
    ballAnimationManager.animateTo("position",ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.66),3);
    ballAnimationManager.animateTo("scale", 10.0, 1);
    ballAnimationManager.animateTo("color", ofColor::cyan, 2);
    
    ballAnimationManager.setDuration(3.0);
    
    ballAnimationManager.endStateDefinition(States::STATE1);
    
    ballAnimationManager.startStateDefinition(States::STATE2);
    ballAnimationManager.setCurve(QUADRATIC_EASE_IN);
    
    ballAnimationManager.animateTo("position",ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.33), 2, 0, AnimationAlignments::END);
    ballAnimationManager.animateTo("scale", 20.0, 10);
    ballAnimationManager.animateTo("color", ofColor::orange, 10);
    
    ballAnimationManager.setDuration(5.0);
    
    ballAnimationManager.endStateDefinition(States::STATE2);
}

//--------------------------------------------------------------
void ofApp::update(){
    // ballB
    ballAnimationManager.update( 1.0f/ofGetFrameRate() );
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ballB
    ofSetColor(ballB.color.getCurrentColor());
    ofFill();
    ofCircle(ballB.pos.getCurrentPosition().x, ballB.pos.getCurrentPosition().y, ballB.s);
    ofDrawBitmapString("Press 1 for State1, press 2 for State2, press 3 for State3", 15, ofGetHeight()-15);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '1':
            ballAnimationManager.animateState(States::STATE1);
            break;
        case '2':
            ballAnimationManager.animateState(States::STATE2);
            break;
        case '3':
            ballAnimationManager.animateState(States::STATE3);
            break;
    }
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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(28);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    //
    //  How to use ofxAnimatable to do multiple animation tweens of the same style
    //
    
    
    //set initial position
    ballA.pos.setPosition( ofPoint(150.0f,300.0f) );
    
    //set repeating style
    ballA.pos.setRepeatType(LOOP_BACK_AND_FORTH);
    
    //set animation curve
    ballA.pos.setCurve(EASE_IN_EASE_OUT);
    
    //start the animation, go from current pos to the specified point
    ballA.pos.animateTo( ofPoint(150.0f, 100.0f) );
    
    ballA.color.setColor(ofColor::grey);
    
    ballA.color.setRepeatType(LOOP_BACK_AND_FORTH);
    
    ballA.color.setCurve(EASE_IN_EASE_OUT);
    
    ballA.color.animateTo(ofColor::cyan);
    
    ballA.s.animateFromTo(5.0, 10.0);
    
    ballA.s.setRepeatType(LOOP_BACK_AND_FORTH);
    
    ballA.s.setCurve(EASE_IN_EASE_OUT);
    
    //
    //  How to use ofxAnimatableManager to do the equivalent animations
    //
    ballAnimationManager.setRepeatType(LOOP_BACK_AND_FORTH);
    ballAnimationManager.setCurve(EASE_IN_EASE_OUT);
    
    ballAnimationManager.addAnimatable(&ballB.pos);
    ballB.pos.setPosition( ofPoint(300.0f,300.0f) );
    ballB.pos.animateTo( ofPoint(300.0f, 100.0f) );
    
    ballAnimationManager.addAnimatable(&ballB.s);
    ballB.s.animateFromTo(5.0, 10.0);
    
    ballAnimationManager.addAnimatable(&ballB.color);
    ballB.color.setColor(ofColor::grey);
    ballB.color.animateTo(ofColor::cyan);
}

//--------------------------------------------------------------
void ofApp::update(){
    // ballA update with App timebase (60 fps)
    ballA.pos.update( 1.0f/ofGetFrameRate());
    ballA.color.update( 1.0f/ofGetFrameRate());
    ballA.s.update( 1.0f/ofGetFrameRate());
    
    // ballB
    ballAnimationManager.update( 1.0f/ofGetFrameRate() );
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ballA
    
    ofSetColor(ballA.color.getCurrentColor());
    ofFill();
    ofCircle(ballA.pos.getCurrentPosition().x, ballA.pos.getCurrentPosition().y, ballA.s);
    
    // ballB
    ofSetColor(ballB.color.getCurrentColor());
    ofFill();
    ofCircle(ballB.pos.getCurrentPosition().x, ballB.pos.getCurrentPosition().y, ballB.s);
    
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

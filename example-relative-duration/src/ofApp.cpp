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
    ballAnimationManager.setCurve(EASE_IN_EASE_OUT);
    
    ballAnimationManager.addAnimatable(&ballB.pos,"position");
    ballB.pos.setPosition( ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.33) );
    ballB.pos.animateTo( ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.66) );
    
    ballAnimationManager.addAnimatable(&ballB.s,"scale");
    ballB.s.animateFromTo(5.0, 10.0);
    
    ballAnimationManager.addAnimatable(&ballB.color,"color");
    ballB.color.setColor(ofColor::grey);
    ballB.color.animateTo(ofColor::cyan);
    
    // Setting duration
    ballAnimationManager.setDurationUnits("position", 3);
    ballAnimationManager.setDurationUnits("scale", 1);
    ballAnimationManager.setDurationUnits("color", 2);
    
    ballAnimationManager.setDuration(3.0);
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

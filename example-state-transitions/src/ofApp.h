#pragma once

#include "ofMain.h"
#include "ofxAnimatableManager.h"

struct Ball {
    ofxAnimatableOfPoint pos;
    ofxAnimatableFloat s;
    ofxAnimatableOfColor color;
    
};

namespace States {
    const string STATE1 = "state1";
    const string STATE2 = "state2";
    const string STATE3 = "state3";
}

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxAnimatableManager ballAnimationManager;
    
        Ball ballA;
        Ball ballB;
};

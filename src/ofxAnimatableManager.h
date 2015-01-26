#include "ofxAnimation.h"

namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}




class ofxAnimatableManager{
public:
    ofxAnimatableManager();
    ~ofxAnimatableManager();
    void update(float dt);
    ofxAnimation* addAnimation(string animationName);
protected:
    map<string, ofxAnimation> animations;
private:
};
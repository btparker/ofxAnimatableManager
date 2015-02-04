#include "ofxAnimationInstance.h"

namespace AnimatableTypes {
    enum ENUM{FLOAT, COLOR, POINT};
}

class ofxAnimatableManager{
public:
    ofxAnimatableManager();
    ~ofxAnimatableManager();
    void update(float dt);
    ofxAnimation* addAnimation(string animationName);
    ofxAnimationInstance* generateAnimationInstance(string animationName, string animationInstanceID);
    void triggerAnimationInstance(string animationInstanceID);
protected:
    map<string, ofxAnimation*> animations;
    map<string, ofxAnimationInstance*> animationInstances;
private:
};
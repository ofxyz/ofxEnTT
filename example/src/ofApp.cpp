#include "ofApp.h"

//--------------------------------------------------------------
class ofApp::Speckle {
public:
    Speckle(float diameter) {
        m_fDiameter = diameter;
    }

    void draw() {
        ofDrawCircle(0, 0, m_fDiameter);
    }
private:
    float m_fDiameter;
};

//--------------------------------------------------------------
struct ofApp::PositionComp {
    float x;
    float y;
};

//--------------------------------------------------------------
struct ofApp::VelocityComp {
    float x;
    float y;
};

//--------------------------------------------------------------
struct ofApp::SpeckleComp {
    Speckle speckle;
};

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 1; i < 15; i++) {
        auto entity = registry.create();
        registry.emplace<SpeckleComp>(entity, 10.f);
        registry.emplace<PositionComp>(entity, i * 10.f , i * 10.f);
        registry.emplace<VelocityComp>(entity, i * 0.25f, i * 0.25f);
    }
}

//--------------------------------------------------------------
void ofApp::update() {

    // Update everything with velocity

    auto view = registry.view<PositionComp, VelocityComp>();

    view.each([](auto& pos, auto& vel) {
        pos.x += vel.x;
        pos.y += vel.y;
        if ((pos.x >= ofGetWidth()  - 5) || (pos.x <= 5)) vel.x = (vel.x < 0) ? abs(vel.x) : -vel.x;
        if ((pos.y >= ofGetHeight() - 5) || (pos.y <= 5)) vel.y = (vel.y < 0) ? abs(vel.y) : -vel.y;
     });
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw everyting with a postion component

    auto posView = registry.view<const PositionComp>();

    ofPushStyle();
    ofFill();
    ofSetColor(0, 0, 0);
    posView.each([](const auto& pos) {
        ofDrawRectangle(pos.x, pos.y, 120, 120);
    });

    // Draw all speckles
    auto speckleView = registry.view<SpeckleComp, const PositionComp>();
    ofSetColor(255, 255, 255);
    speckleView.each([](auto& s, const auto p) {
        ofPushMatrix();
        ofTranslate(p.x,p.y);
        s.speckle.draw();
        ofPopMatrix();
    });
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
#include "ofApp.h"
#include <vector>
#include <cmath>
#include <iostream>
#define x first
#define y second
using namespace std;

using point = pair<double, double>;
using vec = pair<double, double>;
const double FRAME = 60;
const double G = 6.673;

class Object {
public:
	int mass;
	vec velo;
	vec acc;
	point pos;

	Object(int mass = 0, point pos = { 0, 0 }, vec velocity = { 0, 0 }, vec acceleration = { 0, 0 }) {
		this->mass = mass;
		this->velo = velocity;
		this->acc = acceleration;
		this->pos = pos;
	}
};

vector<Object> v;	

void init() {
	for (int i = 0; i < 15; i++) {
		//Object *obj = new Object(100, { 0, i * 100 });
		Object* obj = new Object(ofRandom(100) + 100, { 100 + ofRandom(500), 100 + ofRandom(500) }, { 0, 0 }, { 0, 0 });
		v.push_back(*obj);
	}
}

vec getVector(point p1, point p2) {
	return { p2.x - p1.x, p2.y - p1.y };
}

double SquaredNorm(vec vector) {
	return vector.x * vector.x + vector.y * vector.y;
}

vec mulVec(vec vector, double num) {
	return { vector.x * num, vector.y * num };
}

vec addVec(vec v1, vec v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

vec oppoVec(vec v1) {
	return { -v1.x, -v1.y };
}

void calAcc() {
	for (int i = 0; i < v.size(); i++) {
		v[i].acc = { 0, 0 };
		for (int j = i + 1; j < v.size(); j++) {
			vec r = getVector(v[i].pos, v[j].pos);
			cout << "r : " << i << ", (" << r.x << ", " << r.y << ")\n";
			if (SquaredNorm(r) == 0) continue;
			vec newAcc = mulVec(r, G * v[j].mass / SquaredNorm(r));
			cout << "accNorm : " << SquaredNorm(newAcc) << '\n';
			v[i].acc = addVec(v[i].acc, newAcc);
			v[j].acc = addVec(v[j].acc, oppoVec(newAcc));
		}
	}
}

void calVelo() {	//각 프레임마다의 속도 변화
	for (int i = 0; i < v.size(); i++) {
		//cout << "acc: " << v[i].acc.x << ' ' << v[i].acc.y << '\n';
		//cout << "velo: " << v[i].velo.x << ' ' << v[i].acc.y << '\n';
		//cout << "pos : " << v[i].pos.x << " " << v[i].pos.y << '\n';
		v[i].velo = addVec(v[i].velo, mulVec(v[i].acc, 1 / FRAME));
	}
}

void calPos() {
	for (int i = 0; i < v.size(); i++) {
		//cout << "p - velo: " << mulVec(v[i].velo, 1 / FRAME).x << ' ' << mulVec(v[i].velo, 1 / FRAME).y << '\n';
		v[i].pos = addVec(v[i].pos, mulVec(v[i].velo, 1 / FRAME));
	}
}

void move() {
	calAcc();
	calPos();
	calVelo();
	
}

//--------------------------------------------------------------
void ofApp::setup(){
	/*float value = 0.2;
	ofLogNotice() << "value: " << value;*/
	ofSetWindowTitle("nbody simulation");
	ofSetWindowShape(1024, 768);
	ofSetWindowPosition(100, 100);
	ofSetFrameRate(FRAME);
	ofBackground(ofColor::white);
	ofSetLineWidth(1.0);
	ofSetColor(ofColor::black);
	ofSetBackgroundAuto(true);

	init();
	/*img.load("images/sb.jpg");
	img.setAnchorPercent(0.5, 0.5);*/
}

//--------------------------------------------------------------
void ofApp::update(){
	//좌표 변환
	move();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//그리기
	for (auto p : v) {
		ofLogNotice() << "pos : " << p.pos.x << " " << p.pos.y << '\n';
		ofDrawCircle(p.pos.x, p.pos.y, 2 + (p.mass - 100) / 10);	//질량에 비례하여 크기 조절
	}
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

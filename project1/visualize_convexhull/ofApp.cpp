#include "ofApp.h"
#include <vector>
#include <algorithm>
using namespace std;
#define x first
#define y second
using ll = long long;
using point = pair<ll, ll>;
using vec = pair<ll, ll>;

ofImage img;

vec get_vector(vec& a, vec& b) {
	return { b.x - a.x, b.y - a.y };
}

int ccw(vec& u, vec& v) {
	ll cross_product = u.x * v.y - u.y * v.x;
	if (cross_product > 0) return 1;
	else if (cross_product < 0) return -1;
	else return 0;
}

int ccw(point& a, point& b, point& c) {
	vec u = get_vector(a, b);
	vec v = get_vector(b, c);
	return ccw(u, v);
}

const int N = 100;

point points[N] = {
	{200, 400},
	{300, 400},
	{300, 300},
	{400, 300},
	{400, 400},
	{500, 400},
	{500, 200},
	{350, 200},
	{200, 200},
	{170, 370}, {170, 100}, {270, 270}, {470, 470},
					{170, 170}, {100, 270}, {370, 170}, {370, 370}
};
vector<point> hull;	//convex hull에 포함되는 점 저장
vector<pair<point, point>> print;	//convex hull algorithm 수행 중 탐색하는 점을 순서대로 저장
vector<int> command;	//pop과 push 구분
int i = 0;

int dist(point& a, point& b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

int compare1(point& a, point& b) {	//y좌표 기준 오름차순 비교
	if (a.y == b.y) {
		return a.x < b.x;
	}

	return a.y < b.y;
}

int compare2(point& a, point& b) {	//기준점(points[0])에서 시계 방향으로 점 비교
	int result = ccw(points[0], a, b);

	if (result == 0) {	//일직선 상에 있다면 가까운 점 우선
		return dist(points[0], a) < dist(points[0], b);
	}

	return result < 0;
}

void convexHull() {	//graham scan
	for (int i = 0; i < N; i++) {
		points[i] = { ofRandom(100, 600), ofRandom(100, 600) };
	}
	sort(points, points + N, compare1);

	sort(points + 1, points + N, compare2);

	/*for (auto p : points) {
		ofLogNotice() << p.x << ' ' << p.y << '\n';
	}*/

	for (int i = 0; i < N; i++) {
		while (hull.size() >= 2) {
			if (ccw(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
				break;
			print.push_back({ hull.back(), points[i] });
			command.push_back(2);
			print.push_back({ hull.back(), points[i] });
			command.push_back(0);
			print.push_back({ hull[hull.size() - 2], hull.back() });
			command.push_back(0);
			hull.pop_back();
		}
		if (hull.empty()) 
			print.push_back({ { -1, -1 }, points[i] });
		else
			print.push_back({ hull.back(), points[i] });
		command.push_back(1);
		hull.push_back(points[i]);
		
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	/*float value = 0.2;
	ofLogNotice() << "value: " << value;*/
	ofSetWindowTitle("convex hull algorithm");
	ofSetWindowShape(1024, 768);
	ofSetWindowPosition(100, 100);
	ofSetFrameRate(60);
	ofBackground(ofColor::white);
	ofSetLineWidth(1.0);
	ofSetColor(ofColor::black);
	ofSetBackgroundAuto(false);

	/*img.load("images/sb.jpg");
	img.setAnchorPercent(0.5, 0.5);*/
	convexHull();
}

//--------------------------------------------------------------

void ofApp::update(){
	/*float r, g, b;
	ofSetColor(r, g, b);
	float rand = ofRandom(0, 3);
	if (rand < 1) {
		if (r < 255) r++;
	}
	else if (rand < 2) {
		if (g < 255) g++;
	}
	else if(rand < 3) {
		if (b < 255) b++;
	}*/
}

//--------------------------------------------------------------
void ofApp::draw() {
	/*ofFill();
	ofDrawRectangle(0, 0, 10, 10);
	ofNoFill();
	ofDrawRectangle(20, 20, 100, 100);*/
	/*float value = 0.2;
	ofSetColor(ofColor::hotPink);
	ofDrawBitmapString("value: " + ofToString(value), 100, 100);
	ofDrawRectangle({ 0, 0 }, 100, 100);
	ofNoFill();
	ofSetColor(ofColor::black);
	ofDrawCurve(100, 0, 100, 100, 500, 100, 0, 0);
	ofDrawRectangle({ 400, 400 }, 10, 10);
	ofDrawRectangle({ 100, 0 }, 10, 10);*/

	/*if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		float randomColor = ofRandom(0, 255);
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));

		ofSetRectMode(OF_RECTMODE_CENTER);
		float size = ofRandom(10, 20);
		ofDrawRectangle(ofGetMouseX() + ofRandom(-30, 30), ofGetMouseY() + ofRandom(-30, 30), size, size);
	}*/

	/*if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		float randomColor = ofRandom(0, 255);
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));

		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 50, 50);
	}*/

	/*if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		ofSetColor(ofColor::white);
		img.draw(ofGetMouseX(), ofGetMouseY(), img.getWidth() / 2, img.getHeight() / 2);
		ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 50, 50);
	}

	if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
		ofBackground(ofColor::white);
	}*/
	//ofLogNotice() << i << ' ' << print.size();
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		ofSetColor(ofColor::black);
			for (auto p : points) {
				ofDrawCircle(p.x, p.y, 2);
					//ofDrawBitmapString(ofToString(p.x) + "," + ofToString(p.y), p.x + 2, p.y);
			}
		if (ofGetFrameNum() % 15 == 0) {
			if (i < print.size()) {
				point p1 = print[i].first;
					point p2 = print[i].second;
					if (p1.x != -1 && p2.x != -1) {
						if (command[i] == 1) {
							ofSetColor(ofColor::black);
							ofDrawLine(p1.x, p1.y, p2.x, p2.y);
							ofLogNotice() << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << " draw\n";
						}
						else if (command[i] == 0) {
							ofSetColor(ofColor::white);
							ofDrawLine(p1.x, p1.y, p2.x, p2.y);
							ofLogNotice() << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << " erase\n";
							if (i > 0 && command[i - 1] == 2) {
								i++;
								p1 = print[i].first;
								p2 = print[i].second;
								ofSetColor(ofColor::white);
								ofDrawLine(p1.x, p1.y, p2.x, p2.y);
								ofLogNotice() << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << " erase\n";
							}
						}
						else if (command[i] == 2) {
							ofSetColor(ofColor::red);
							ofDrawLine(p1.x, p1.y, p2.x, p2.y);
							ofLogNotice() << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << " draw\n";
						}
					}
				i++;
			}
			else {
				point p1 = print[print.size() - 1].second;
				point p2 = points[0];
				ofSetColor(ofColor::black);
				ofDrawLine(p1.x, p1.y, p2.x, p2.y);
				ofLogNotice() << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << " draw\n";
			}
		}
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

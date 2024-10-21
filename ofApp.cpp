#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	if (ofGetFrameNum() % 2 == 0) {
		
		this->radius_list.push_back(1);
		this->max_radius_list.push_back(300);
		this->rotate_list.push_back(
			glm::vec3(
				ofMap(ofNoise(1984, ofGetFrameNum() * 0.0035), 0, 1, -360, 360),
				ofMap(ofNoise(1103, ofGetFrameNum() * 0.0035), 0, 1, -360, 360),
				ofMap(ofNoise(0702, ofGetFrameNum() * 0.0035), 0, 1, -360, 360))
		);
	}

	for (int i = this->radius_list.size() - 1; i > -1; i--) {

		if (this->radius_list[i] < this->max_radius_list[i]) {

			this->radius_list[i] += 2;
		}
		else {

			this->radius_list.erase(this->radius_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->rotate_list.erase(this->rotate_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	for (int i = 0; i < this->radius_list.size(); i++) {

		ofPushMatrix();

		ofRotateZ(this->rotate_list[i].z);
		ofRotateY(this->rotate_list[i].y);
		ofRotateX(this->rotate_list[i].x);

		ofNoFill();
		ofSetColor(0, ofMap(this->radius_list[i], 1, this->max_radius_list[i], 255, 0));

		ofDrawCircle(glm::vec3(), this->radius_list[i]);
		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
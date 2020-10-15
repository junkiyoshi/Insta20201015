#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int deg_param = 15;
	int radius_span = 1;
	float noise_seed = ofRandom(1000);

	for (int deg_location = 0; deg_location < 360; deg_location += 90) {

		int start_index = this->frame.getNumVertices();
		for (int radius = 10; radius < 150; radius += radius_span) {

			int next_radius = radius + radius_span;
			int index = this->face.getNumVertices();

			float angle_y = ofMap(ofNoise(noise_seed, radius * 0.005 + ofGetFrameNum() * 0.008), 0, 1, PI * -1.5, PI * 1.5);
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

			float next_angle_y = ofMap(ofNoise(noise_seed, next_radius * 0.005 + ofGetFrameNum() * 0.008), 0, 1, PI * -1.5, PI * 1.5);
			auto next_rotation_y = glm::rotate(glm::mat4(), next_angle_y, glm::vec3(0, 1, 0));

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec4(radius * cos((deg_location + deg_param) * DEG_TO_RAD), radius * sin((deg_location + deg_param) * DEG_TO_RAD), 0, 0) * rotation_y);
			vertices.push_back(glm::vec4(radius * cos((deg_location - deg_param) * DEG_TO_RAD), radius * sin((deg_location - deg_param) * DEG_TO_RAD), 0, 0) * rotation_y);
			vertices.push_back(glm::vec4(next_radius * cos((deg_location - deg_param) * DEG_TO_RAD), next_radius * sin((deg_location - deg_param) * DEG_TO_RAD), 0, 0) * next_rotation_y);
			vertices.push_back(glm::vec4(next_radius * cos((deg_location + deg_param) * DEG_TO_RAD), next_radius * sin((deg_location + deg_param) * DEG_TO_RAD), 0, 0) * next_rotation_y);

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
		
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->face.draw();

	ofDrawSphere(5);

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
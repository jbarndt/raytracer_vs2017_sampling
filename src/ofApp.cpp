#include "ofApp.h"
#include "ofxGui.h"
#include "of3dPrimitives.h"
#include <iostream>

#include <cmath>
#include "ray.h"
#include "camera.h"
#include "float.h"

ofxIntSlider numSamplesSlider;
ofxPanel gui;
ofImage image;

ofSpherePrimitive sphere;

bool run_once;
vec3 unit_direction;
int numSamples;

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup(); 

	image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);

	ofPixels & pixels = image.getPixels();

	std::cout << "print" << "\n";

	//std::cout << numSamplesSlider.getParameter << "\n";
	
	// add a slider with <label>, <initial value>, <min>, <max>
	//gui.add(radius.setup("radius", 140, 10, 300));
	//gui.add(image);
	gui.add(numSamplesSlider.setup("numSamples", 1, 1, 50));
	run_once = false;
}

vec3 color(const ray & r) {
	unit_direction = 10.83*unit_vector(r.direction());
	float sin_xy_squared = sin((unit_direction.x()*unit_direction.x()*unit_direction.y()*unit_direction.y()));
	float t = 0.5*(1 + sin_xy_squared);
	return t * vec3(1.0, 1.0, 1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (run_once == false) {
		numSamples = 10;

		ofPixels& pixels = image.getPixels();

		camera cam;
		int w = image.getWidth();
		int h = image.getHeight();
		int x = 0;
		for (auto line : pixels.getLines()) {
			int y = 0;
			for (auto pixel : line.getPixels()) {

				vec3 col(0, 0, 0);
				for (int s = 0; s < numSamples; s++) {
					float random1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float random2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float u = float(x + random1) / float(w);
					float v = float(y + random2) / float(h);
					ray r = cam.get_ray(u, v);
					col += color(r);
				}
				col /= float(numSamples);

				pixel[0] = int(255.*col[0]);
				pixel[1] = int(255.*col[1]);
				pixel[2] = int(255.*col[2]);
				y += 1;
			}
			x += 1;
		}
		image.update();
		run_once = true;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	int centerX = ofGetWidth() / 2;
	int centerY = ofGetHeight() / 2;
	
	image.draw(0, 0, ofGetWidth(), ofGetHeight());
	gui.draw();
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
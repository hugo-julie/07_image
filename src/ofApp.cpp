#include "ofApp.h"

ofColor ofApp::filter(ofColor color, int effectP, float p = 0.2f) {
	float r = color.r;
	float g = color.g;
	float b = color.b;
	float luminance = 0.299f * r + 0.587f * g + 0.114f * b;
	float blur = 2.0f * r + 2.0f * g + 2.0f * b;


	if (effectP == 1) {
		ofColor inversedColor = ofColor(255 - r, 255 - g, 255 - b);
		return inversedColor;
	} else if (effectP == 2) {
		float grey = (r + g + b) / 3.0f;
		ofColor greyColor = ofColor(grey, grey, grey);
		return greyColor;
	} else if (effectP == 3) {
		ofColor greyColor = ofColor(luminance, luminance, luminance);
		return greyColor;
	} else if (effectP == 4) {
		float k = (p - 0.5f) * 256;
		int newRed = ofClamp(r + k, 0, 255);
		int newGreen = ofClamp(g + k, 0, 255);
		int newBlue = ofClamp(b + k, 0, 255);
		ofColor brightnessColor = ofColor(newRed, newGreen, newBlue);
		return brightnessColor;
	} else if (effectP == 5) {
		float k = p * 3;
		int newRed = ofClamp((r - 128) * k + 128, 0, 255);
		int newGreen = ofClamp((g - 128) * k + 128, 0, 255);
		int newBlue = ofClamp((b - 128) * k + 128, 0, 255);
		ofColor contrastColor = ofColor(newRed, newGreen, newBlue);
		return contrastColor;
	} else if (effectP == 6) {
		int newRed = ofClamp(0.393 * r + 0.769 * g + 0.189 * b, 0, 255);
		int newGreen = ofClamp(0.349 * r + 0.686 * g + 0.168 * b, 0, 255);
		int newBlue = ofClamp(0.272 * r + 0.534 * g + 0.131 * b, 0, 255);
		ofColor sepiaColor = ofColor(newRed, newGreen, newBlue);
		return sepiaColor;
	}

	else {
		return color;
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(600, 396);
	bool loadingOk = img.load("Panda roux.jpg");
	if (!loadingOk) {
		ofLogError() << "Image non trouvée";
	}
	imgResult.allocate(img.getWidth(), img.getHeight(),
		OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
	/* int px = ofClamp(mouseX, 0, img.getWidth() - 1);
	int py = ofClamp(mouseY, 0, img.getWidth() - 1);
	currentColor = img.getColor(px, py);
	*/

	float power = mouseX / (float)ofGetWidth();

	for (int y = 0; y < img.getHeight(); y++) {
		for (int x = 0; x < img.getWidth(); x++) {
			ofColor transferColor = img.getColor(x, y);
			ofColor modifiedColor = filter(transferColor, effect, power);
			imgResult.setColor(x, y, modifiedColor);
		}
	}
	imgResult.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	img.draw(0, 0);
	imgResult.draw(0, 0);

	ofSetColor(currentColor);
	ofDrawRectangle(mouseX + 10, mouseY + 10, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_LEFT) {
		effect--;
		effect = effect % numberEffect;
	}
	if (key == OF_KEY_RIGHT) {
		effect++;
		effect = effect % numberEffect;
	}
	effect = (effect + numberEffect) % numberEffect;
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

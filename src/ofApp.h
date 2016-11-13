#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxUDPManager.h"

#define HOST "127.0.0.1"
#define PORT 11999
#define RESOLUTION_X 1280
#define RESOLUTION_Y 960
#define MIN_AREA 1000
#define MAX_AREA (RESOLUTION_X * RESOLUTION_Y) / 2
#define MAX_CONSIDERED 20
#define TARGET_FACTOR 10
#define THRESHOLD 60

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		bool bLearnBackground;
		bool readyToSend;
		ofVideoGrabber vidGrabber;
		ofxCvColorImage colorImg;
		ofImage imageTest;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage grayDiff;
		ofxCvContourFinder contourFinder;
		ofxUDPManager udpConnection;
};

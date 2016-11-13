#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	bLearnBackground = true;
	readyToSend = true;

	vidGrabber.setVerbose(true);
	int deviceId = 0;
	for (int i = 0; i < vidGrabber.listDevices().size(); i++)
	{
		if (vidGrabber.listDevices()[i].deviceName.find("Hercules Dualpix Exchange") != string::npos)
		{
			deviceId = vidGrabber.listDevices()[i].id;
		}
	}
	vidGrabber.setDeviceID(deviceId);
	vidGrabber.initGrabber(RESOLUTION_X, RESOLUTION_Y);

	colorImg.allocate(RESOLUTION_X, RESOLUTION_Y);
	grayImage.allocate(RESOLUTION_X, RESOLUTION_Y);
	grayBg.allocate(RESOLUTION_X, RESOLUTION_Y);
	grayDiff.allocate(RESOLUTION_X, RESOLUTION_Y);

	// Open UDP connection to the localhost
	udpConnection.Create();
	udpConnection.Connect(HOST, PORT);
	udpConnection.SetNonBlocking(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
	vidGrabber.update();

	// TODO use blearnbackground to send data only when something changed
	if (vidGrabber.isFrameNew())
	{
		colorImg.setFromPixels(vidGrabber.getPixels());
		grayImage = colorImg; // convert our color image to a grayscale image
		if (bLearnBackground == true)
		{
			grayBg = grayImage; // update the background image
			bLearnBackground = false;
		}
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(THRESHOLD);
		contourFinder.findContours(grayDiff, MIN_AREA, MAX_AREA, MAX_CONSIDERED, false, true);

		if (readyToSend)
		{
			ostringstream ss;
			for (int i = 0; i < contourFinder.blobs.size(); i++)
			{
				for (int j = 0; j < contourFinder.blobs[i].pts.size(); j += 1)
				{
					ss << (contourFinder.blobs[i].pts[j].x / RESOLUTION_X) * TARGET_FACTOR - TARGET_FACTOR / 2;
					ss << "&";
					ss << ((RESOLUTION_Y - contourFinder.blobs[i].pts[j].y) / RESOLUTION_Y) * TARGET_FACTOR - TARGET_FACTOR / 2;
					if (j + 1 < contourFinder.blobs[i].pts.size())
					{
						ss << ",";
					}
				}
				if (i + 1 < contourFinder.blobs.size())
				{
					ss << ";";
				}
			}

			string message = ss.str();
			udpConnection.Send(message.c_str(), message.length());
			//readyToSend = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetHexColor(0xffffff);
	colorImg.contrastStretch();
	colorImg.draw(0, 0, 320, 240);
	grayDiff.draw(0, 240, 320, 240);
	ofDrawRectangle(320, 0, 320, 240);
	contourFinder.draw(320, 0, 320, 240);

	/*
	ofColor c(255, 255, 255);
	for (int i = 0; i < contourFinder.blobs.size(); i++)
	{
		for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++)
		{
			c.setHsb(i * 64, 255, 255);
			ofSetColor(c);
			ofPoint pt = contourFinder.blobs[i].pts[j];
			pt.x += 320;
			pt.y += 240;
			ofDrawCircle(pt, 1);
		}
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//bLearnBackground = true;
	//if (key == OF_KEY_CONTROL)
	//{
		//bLearnBackground = true;
		//readyToSend = true;
	//}
	// Sinon il prend une image tout cle quand on change de window...
	//bLearnBackground = true;
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

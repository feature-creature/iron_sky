#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxDelaunay.h"
using namespace cv;

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();
    vector <ofPoint> getTriangle(int i);

    //frame source
    ofVideoGrabber video;
    ofVideoPlayer ironSky;

    //pre-processing images
    ofxCvColorImage image;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage blurred;
    ofxCvGrayscaleImage mask;
    ofxCvGrayscaleImage inverted;

    ofxDelaunay triangulation;

    vector<Point2f> corners;



};


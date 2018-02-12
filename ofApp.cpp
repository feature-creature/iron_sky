#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//video.setDeviceID(0);
    //video.setDesiredFrameRate(60);
    //video.initGrabber(320,240);

    
    ironSky.load("videos/iron_sky-paolo_nutini.mkv");
    //ironSky.load("videos/iron_sky-daniel_wolfe.mkv");
    ironSky.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	//video.update();	//Decode the new frame if needed
    ironSky.update();

	//Do computing only if the new frame was obtained
	//if ( video.isFrameNew() ) {
	if ( ironSky.isFrameNew() ) {
		//Getting a new frame
		//image.setFromPixels( video.getPixels() );
		image.setFromPixels( ironSky.getPixels() );

		//Convert to grayscale image
		grayImage = image;

		//Smoothing image
		blurred = grayImage;
		blurred.blurGaussian( 5 );

//		//Thresholding for obtaining binary image
//		mask = blurred;
//		mask.threshold( ofMap(mouseX, 0, ofGetWidth(), 0, 200) );

//        //Getting an inverted mask of image to use in contour finder
//        inverted = mask;
//        inverted.invert();

        //#### FIND INTERESTING POINTS #####
		Mat imageCV;
		imageCV = Mat( blurred.getCvImage() );
        //param 3 is how many points you want to get
		goodFeaturesToTrack(imageCV, corners, 200, 0.01, 4);
        
        // empty triangulation object of previous points
        triangulation.reset();
        // fill triangulation object with new points
        for(int i = 0; i < corners.size(); i++){
            triangulation.addPoint(ofPoint(corners[i].x,corners[i].y));
        }

        //prepare points for plotting by
        //calculate the triangulation object's triangulation
        triangulation.triangulate();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
		ofBackground(255, 255, 255);	//Set the background color

		ofSetColor( 255, 255, 255 );	//Set color for images drawing

        int w = image.width;
        int h = image.height;
		//Original decimated image
		image.draw(0, 0, w/2, h/2);

        //blurred immage
		blurred.draw( w/2, 0, w/2, h/2);

//		//Thresholded image
//		mask.draw( w, 0, w/2, h/2);
//		//Inverted image
//		inverted.draw( w/2*3, 0, w/2, h/2);

        ofTranslate(ofGetWidth()/2-w/2, h/2+10);
        ofSetColor(0);
        ofNoFill();
        ofDrawRectangle(0,0,w,h);

        //draw the interesting points in RED
        //ofSetColor(255,0,0);
        //ofFill();
		//for (int i=0; i<corners.size(); i++) {
            //ofDrawEllipse(corners[i].x, corners[i].y, 5,5);
        //}

        //for(int g = 0; g < corners.size(); g++){
            //corners[g].update();
            //corners[g].draw();
        //}
        
        ofNoFill();
        ofSetColor(0,0,0);

        for (int g=0; g<triangulation.getNumTriangles(); g++){ // loop over the triangles
            vector <ofPoint> pts = getTriangle(g);             // extract the vector with 3 points
            ofDrawTriangle(pts[0], pts[1], pts[2]);             // use this point to draw a triangle
        }
}

vector <ofPoint> ofApp::getTriangle(int i){
    int pA = triangulation.triangleMesh.getIndex(i*3);
    int pB = triangulation.triangleMesh.getIndex(i*3+1);
    int pC = triangulation.triangleMesh.getIndex(i*3+2);
    
    ofPoint pointA = triangulation.triangleMesh.getVertex(pA);
    ofPoint pointB = triangulation.triangleMesh.getVertex(pB);
    ofPoint pointC = triangulation.triangleMesh.getVertex(pC);
    
    vector <ofPoint> points;
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
    return points;
}

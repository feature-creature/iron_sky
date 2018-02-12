#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // declare video source

    // use camera source
	//video.setDeviceID(0);
    //video.setDesiredFrameRate(60);
    //video.initGrabber(320,240);

    // use file source
    ironSky.load("videos/iron_sky-daniel_wolfe.mp4");
    ironSky.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Decode the new frame if needed
    
    //camera or file source
	//video.update();	
    ironSky.update();

	//if a new frame was created from the video source
    //create images and points from the new frame
	if ( ironSky.isFrameNew() ) {
	//if ( video.isFrameNew() ) {
        
        //
        // IMAGE PRE-PROCESSING FOR COMPOSITION SIMPLIFICATION + FEATURE ISOLATION
        //
    

		//create a 'default' image from the source of the new frame
		//image.setFromPixels( video.getPixels() );
		image.setFromPixels( ironSky.getPixels() );

		//create a grayscale image from default image
		grayImage = image;

		//create a blurred image from the grayscale image
		blurred = grayImage;
		blurred.blurGaussian( 5 );

        //create a masking image (binary?) from the blurred image
        //via a mouse-based vector threshold 
        //mask = blurred;
		//mask.threshold( ofMap(mouseX, 0, ofGetWidth(), 0, 200) );

        //create an inverted image from the masking image 
        //useful for finding contours
        //inverted = mask;
        //inverted.invert();


        //
        // STORE POINTS OF INTEREST FROM PRE-PROCESSED FRAME DATA
        //
        

        //create a local mat from the blurred image
		Mat imageCV;
		imageCV = Mat( blurred.getCvImage() );
        
        //store points from the mat
        //param 3 dictates # of points stored
		goodFeaturesToTrack(imageCV, corners, 200, 0.01, 4);

        //remove previous frame's stored points from the delaunay object
        triangulation.reset();

        //add this frame's points of interest to the delaunay object
        for(int i = 0; i < corners.size(); i++){
            triangulation.addPoint(ofPoint(corners[i].x,corners[i].y));
        }

        //calculate the delaunay object's triangulation
        triangulation.triangulate();
        // triangle data is now prepared for drawing
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

        // black background
		ofBackground(0);	

        //!! could be created as global variables since values are generally constant
        int w = image.width;
        int h = image.height;

        //default background to white for all images that are drawn to screen 
		ofSetColor(255);	
        
		//draw default image with border
        ofPushMatrix();
        ofTranslate((ofGetWidth()-(2*w))/2,10);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0,0,w/2,h/2);
		image.draw(0, 0,w/2,h/2);
        ofPopMatrix();

        //draw grayscale image with border
        ofPushMatrix();
        ofTranslate((ofGetWidth()-(0.5*w))/2,10);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0,0,w/2,h/2);
		grayImage.draw(0,0,w/2,h/2);
        ofPopMatrix();

        //draw blurred image with border
        ofPushMatrix();
        ofTranslate((ofGetWidth()+w)/2,10);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0,0,w/2,h/2);
		blurred.draw(0,0,w/2,h/2);
        ofPopMatrix();

        //draw mask thresholded image
        //mask.draw( w, 0, w/2, h/2);
        
        //draw inverted image
        //inverted.draw( w/2*3, 0, w/2, h/2);

        
        //
        // VISUALIZE TRIANGLE DATA
        //


        // move triangles to ideal location
        ofTranslate(ofGetWidth()/2-w/2, h/2+50);
        
        // rectangle outlining window for triangle data 
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(0,0,w,h);

        
        //draw triangle data
        //iterate through stored triangle data
        for (int g=0; g<triangulation.getNumTriangles(); g++){
            
            //locally store this triangle as a vector of 3 points
            vector <ofPoint> pts = getTriangle(g);             

            
            //fill the entire triangle with the color of its central pixel
            //primitive method which can reference any of the images created in update
            int centerX = (pts[0][0] + pts[1][0] + pts[2][0])/3;
            int centerY = (pts[0][1] + pts[1][1] + pts[2][1])/3;
            ofColor triFill = grayImage.getPixels().getColor(centerX, centerY);
           
            // draw current triangle 
            ofPushStyle();
            ofFill();
            ofSetColor(triFill);
            ofDrawTriangle(pts[0], pts[1], pts[2]);            
            ofPopStyle();
        }
        

        //optionally draw the 'interesting' points generated for this frame
        ofPushStyle();
        ofSetColor(255,0,0);
        ofFill();
		for (int i=0; i<corners.size(); i++) {
            ofDrawEllipse(corners[i].x, corners[i].y, 5,5);
        }
        ofPopStyle();

}


//--------------------------------------------------------------
vector <ofPoint> ofApp::getTriangle(int i){
    // return a vector of points
    
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

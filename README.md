# Memo Akten's 'Techno Fan' Workflow

## init

Memo was tasked with creating a programmatically generated visualization process that would be mapped to pre-created video files. 

Memo was provided with many separate video files of individual layers of individual video shots. These separate video files were originially part of a single, large file that was in a final 'content/timeline' stage.  

After Memo created 'enhanced' video files, the original videographer re-composited the separate video files into a final single, large file.

## workflow
    
### video analysis and point identification
Every frame, pre-process the current video frame with computer vision techniques - c++/openFrameworks/opencv - to isolate points of interest. Image simplication and feature isolation can be achieved through the combination of different cv techniques. Some options:

cvSmooth
cvThreshold
cvErode
cvDialate


After Image simplication and feature isolation, points of interest can be predetermined or discovered through the combination of other cv techniques.

cvFindContours
cvGoodFeatures
OpenSURF

Points of interest are then stored into an array.

Depending on hardware and concept requirements, simplifying the array of points might be necessary. Using cvCalcOpticalFlowPyrLK or 'manual' techniques - adding a vector threshold between points for removing data that is visually irrelevant - can create a more elegant data set.

### triangulate identified points

Every frame, feed the simplified array of points into a Delaunay Triangulation structure and output a set of triangle data.

ofxDelaunay

Current magnitude of data reduction?

### display triangles

Manipulate visual appearance "phenotype" of generated triangle data.

As an aside, to visualize the entire window, instead of the triangulated subsection, you can add the coordinates of the window's corners into the triangle data set. This technique and others can be combined with the original video files, among other elements, in transparent layers to create complex visuals.

### save image sequence to disk

Realtime video processing with scrubbing, pausing, and playback was implemented via a custom interface for the user. Images are always displayed on screen as processing is performed and applied for visual confirmation and feedback. Additionally, images can be optionally written to hard disk in real time while the next sequential frames are processing. Memo stored frames in png format - perhaps for alpha capabilities. Using a real-time interface prevented the use of
framecounting and keyframe referencing for time-based decision making.



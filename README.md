# Memo Akten's 'Techno Fan' Workflow

## background

I am starting to learn the principles of Computer Vision. I used Memo Akten's 'Techno Fan' as a guide for this first CV system. This is a reference review of his workflow.

## init

Memo was tasked with creating a programmatically generated visualization process that would be mapped to previously-created video files. Memo was provided with many separate video files of individual layers of individual video shots. These separate video files were originially part of a single, large, finalized file. After Memo created the 'enhanced' video files, the original videographer re-composited the separate video files back into the single, large, finalized file to be used as a music video.

## workflow
    
### video analysis and point identification
Every frame, pre-process the frame received from the video source with computer vision techniques -- <i>c++ + openFrameworks + opencv</i> -- to isolate points of interest. Image simplication and feature isolation can be achieved through the combination of different cv techniques. Some options:

    cvSmooth
    cvThreshold
    cvErode
    cvDialate


After Image simplication and feature isolation is sufficient to your requirements, points of interest, whether predetermined or discovered through the previous process, can be identified and stored through the combination of other cv techniques. Some options:

    cvFindContours
    cvGoodFeatures
    OpenSURF

Points of interest are then stored in an array.

Depending on hardware requirements and concept requirements, simplifying the array of points might be necessary. You can use libraries or 'custom' techniques - adding a vector threshold between points of interest for removing data that is visually irrelevant - to create a more elegant data set.

    cvCalcOpticalFlowPyrLK 

### triangulate identified points

Every update cycle, feed the simplified array of points into a Delaunay Triangulation structure and output a set of triangle data.

ofxDelaunay

Current magnitude of data reduction?

### display triangles

Create the visual appearance "phenotype" of generated triangle data. You have complete freedom, of course. As an aside, to visualize the entire window, instead of the triangulated subsection, you can add the coordinates of the display window's corners to the triangle data set. This technique and others can be combined with the original video files in semi-transparent layers to create complex visuals.

### save image sequence to disk

Real-time video processing with scrubbing, pausing, and playback was implemented via a custom user interface. Images are always displayed on screen as image processing is performed. Additionally, images can be optionally written to your hard disk in real-time while the next frame is processing. Memo stored frames in png format - perhaps for alpha capabilities in comparison to jpeg format. Using a real-time interface prevented the use of framecounting and keyframe referencing for the time-based decision making.



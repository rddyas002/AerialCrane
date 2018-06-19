#include "imageprocessing.h"
#include <QDebug>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

ImageProcessing::ImageProcessing(void)
{
    if(!capture.open(1)){
        qDebug() << "Error opening video device";
    }
    else{
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        capture.set(CV_CAP_PROP_FPS, 125);
        capture.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);

        // create worker thread
        captureTimer = new QTimer(this);
        //connect(captureTimer, SIGNAL(timeout()), this, SLOT(sampleCamera()));
        //captureTimer->start(16);
        mShutdown = false;
    }
}

void ImageProcessing::run(){
    static double timer = 0;
    float fps = 0;
/*
    string trackerTypes[6] = {"BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN"};
    // vector <string> trackerTypes(types, std::end(types));

    // Create a tracker
    string trackerType = trackerTypes[2];
    Ptr<Tracker> tracker;
    tracker = Tracker::create(trackerType);

    // Read first frame
    bool ok = capture.read(frame);
    // Define initial boundibg box
    Rect2d bbox(287, 23, 86, 320);
    // Uncomment the line below to select a different bounding box
    bbox = selectROI(frame, false);

    // Display bounding box.
    rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
    imshow("Tracking", frame);

    tracker->init(frame, bbox);
*/
    while(!mShutdown){
        if (timer != 0){
            fps = getTickFrequency() / ((double)getTickCount() - timer);
        }
        timer = (double)getTickCount();

        if (capture.isOpened()){
            capture >> frame;
            if(!frame.empty()){
                /*
                // Update the tracking result
                bool ok = tracker->update(frame, bbox);
                if (ok)                {
                    // Tracking success : Draw the tracked object
                    rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
                }
                else{
                    // Tracking failure detected.
                    putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
                }
                // Display tracker type on frame
                putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
                */
                // Display FPS on frame
                putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
                imshow("Tracking", frame);
                int k = waitKey(1);
            }
        }
    }
}

ImageProcessing::~ImageProcessing(){
    mShutdown = true;
    captureTimer->stop();
    delete captureTimer;
    if(capture.isOpened())
    {
        capture.release();
    }
}

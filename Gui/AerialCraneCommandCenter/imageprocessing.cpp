#include "imageprocessing.h"
#include <QDebug>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

ImageProcessing::ImageProcessing(){

}

void ImageProcessing::openDevice(int dev){
    if(!capture.open(dev)){
        qDebug() << "Error opening video device";
    }
    else{
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        capture.set(CV_CAP_PROP_FPS, 125);
        capture.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);
        mShutdown = false;
    }
}

void ImageProcessing::closeDevice(void){
    mShutdown = true;
    if(capture.isOpened()){
        capture.release();
    }
}

void ImageProcessing::run(){
    static double timer = 0;
    float fps = 0;

    while(true){
        mutex.lock();
        if(mShutdown)
            break;
        mutex.unlock();

        if (timer != 0){
            fps = getTickFrequency() / ((double)getTickCount() - timer);
        }
        timer = (double)getTickCount();

        if (capture.isOpened()){
            capture >> frame;
            if(!frame.empty()){
                // Display FPS on frame
                putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
                imshow("Tracking", frame);
                int k = waitKey(1);
            }
        }
    }
}

ImageProcessing::~ImageProcessing(){
    mutex.lock();
    mShutdown = true;
    mutex.unlock();
    if(capture.isOpened())
    {
        capture.release();
    }
}

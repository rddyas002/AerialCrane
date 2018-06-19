#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include <QMutex>
#include <QImage>
#include <QWaitCondition>
#include <QCloseEvent>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

class ImageProcessing : public QThread
{
    Q_OBJECT
public:
    explicit ImageProcessing();
    ~ImageProcessing();
    void run();
signals:

public slots:

private:
    QTimer * captureTimer;
    QMutex mutex;
    volatile bool mShutdown;

    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;
};

#endif // IMAGEPROCESSING_H

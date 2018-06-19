#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtWidgets>
#include <opencv2/opencv.hpp>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);

    QImage m_img;
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void setImage(const QImage & img);
};

#endif // IMAGEVIEWER_H

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QThread>

class ImageProcessing : public QThread
{
    Q_OBJECT
public:
    explicit ImageProcessing(void);

signals:

public slots:
};

#endif // IMAGEPROCESSING_H

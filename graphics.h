#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>
#include "graphicsmemorysegmnet.h"
#include "memorysegment.h"

class Graphics :public QGraphicsView
{
public:
    Graphics(QWidget *parent = 0);


public slots:
    void zoomIn();
    void zoomOut();
    void drawMemory(int memorysize,QVector<MemorySegment*> MyMemory,QVector<MemorySegment*> *MyMemoryAddress);
    void compactMemoryHoles(int ProccessID);
    void addProccesToHole(int holeID,MemorySegment processSegment);
    void updateMemoryAfterDeallocation();
    void destoryMemory();



protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);
private:
    QGraphicsScene *scene;
    QVector<GraphicsMemorySegmnet*> segments;
    QVector<GraphicsMemorySegmnet*>::iterator it;
    int MemorySize;

    QVector<MemorySegment*> *MyMemory;




};

#endif // GRAPHICS_H

#ifndef MEMORYSEGMENTS_H
#define MEMORYSEGMENTS_H

#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsView>


class Graphics;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE



class GraphicsMemorySegmnet : public QGraphicsItem,QWidget
{
public:
    GraphicsMemorySegmnet(Graphics *graphicsView ,QString ProcessName,QString SegmentName,int SegmentSize,qreal SegmentGraphicsSize,
                   int processid,int segmentid,bool process);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    QString ProcessName;
    QString SegmentName;
    qreal SegmentSize;
    qreal SegmentGraphicsSize;
    Graphics *parent;
    bool IsProcess;
    int ProccessId;
    int SegmentId;
    qreal YaxisFinish;
    int segmentStartAddress;
};

#endif // MEMORYSEGMENTS_H

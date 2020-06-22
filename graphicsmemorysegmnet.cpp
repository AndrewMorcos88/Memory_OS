#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QtWidgets/QMessageBox>


#include "graphics.h"
#include "graphicsmemorysegmnet.h"

#define segmentWidth 400

GraphicsMemorySegmnet::GraphicsMemorySegmnet(Graphics *graphicsView, QString processName, QString segmentName, int segmentSize,qreal segmentGraphicsSize,
                               int processId,int segmentId, bool process)
{
    parent = graphicsView;
    setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(2);
    ProcessName = processName;
    SegmentName = segmentName;
    SegmentSize = segmentSize;
    SegmentGraphicsSize = segmentGraphicsSize;
    ProccessId = processId;
    SegmentId = segmentId;
    IsProcess = process;
}

QRectF GraphicsMemorySegmnet::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, segmentWidth + adjust, SegmentGraphicsSize + adjust);
}

QPainterPath GraphicsMemorySegmnet::shape() const
{
    QPainterPath path;
    path.addRect(-10, -10, segmentWidth, SegmentGraphicsSize);
    return path;
}

void GraphicsMemorySegmnet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QLinearGradient gradient(QPointF(-10,-10),QPointF(-10,SegmentGraphicsSize));
    if(IsProcess){
        if (option->state & QStyle::State_Sunken) {
            gradient.setColorAt(1, QColor(Qt::green).light(120));
            gradient.setColorAt(0, QColor(Qt::darkGreen).light(120));
        } else {
            gradient.setColorAt(0, Qt::green);
            gradient.setColorAt(1, Qt::white);
        }
    }
    else{
        if (option->state & QStyle::State_Sunken) {
            gradient.setColorAt(1, QColor(Qt::cyan).light(120));
            gradient.setColorAt(0, QColor(Qt::darkCyan).light(120));
        } else {
            gradient.setColorAt(0, Qt::cyan);
            gradient.setColorAt(1, Qt::white);
        }
    }

    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    QRectF segment(-10, -10, segmentWidth, SegmentGraphicsSize);
    painter->drawRect(segment);

}

void GraphicsMemorySegmnet::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsMemorySegmnet::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(IsProcess){
        if(QMessageBox::question(this,"Deallocate Process","Do You Want To Deallocate Process " + ProcessName + " All Segments",
                                 QMessageBox::Yes|QMessageBox::No) ==QMessageBox::Yes){
            parent->compactMemoryHoles(this->ProccessId);
        }
    }


    QGraphicsItem::update();
    QGraphicsItem::mouseReleaseEvent(event);
}

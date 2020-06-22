#include "graphics.h"
#include <QKeyEvent>
#include <math.h>
#include "mainwindow.h"
#define XaxisCenter 280.0
#define YaxisMemoryBegin 90.0
#define FixedMemorySize 700

Graphics::Graphics(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setMouseTracking(true);
    this->setBackgroundRole(QPalette::Base);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,800,800);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->scale(qreal(0.8), qreal(0.8));
    this->setMinimumSize(400, 400);

}



void Graphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}


#if QT_CONFIG(wheelevent)
void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif



void Graphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Hover On A Memory Segment To Show Its Info, Click On The Procces Segment To Deallocate It, And Zoom With The Mouse "
                       "Wheel Or The '+' And '-' Keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);


    // process and hole map color
    QRect processColor(20,90,40,40);
    QLinearGradient processColorGradient(QPointF(20,90),QPointF(20,130));
    processColorGradient.setColorAt(0, Qt::green);
    processColorGradient.setColorAt(1, Qt::white);
    painter->fillRect(rect.intersected(processColor), processColorGradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(processColor);

    QRect processColorText(80,90,70,40);
    QString colorText1 = "Process";
    painter->setPen(Qt::lightGray);
    painter->drawText(processColorText.translated(2, 2), colorText1);
    painter->setPen(Qt::black);
    painter->drawText(processColorText, colorText1);



    QRect holeColor(20,150,40,40);
    QLinearGradient holeColorGradient(QPointF(20,150),QPointF(20,190));
    holeColorGradient.setColorAt(0, Qt::cyan);
    holeColorGradient.setColorAt(1, Qt::white);
    painter->fillRect(rect.intersected(holeColor), holeColorGradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(holeColor);

    QRect holeColorText(80,150,60,60);
    QString colorText2(tr("Hole"));
    painter->setPen(Qt::lightGray);
    painter->drawText(holeColorText.translated(2, 2), colorText2);
    painter->setPen(Qt::black);
    painter->drawText(holeColorText, colorText2);





}


void Graphics::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void Graphics::zoomIn()
{
    scaleView(qreal(1.2));
}

void Graphics::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void Graphics::drawMemory(int memorysize,QVector<MemorySegment*> Mymemory,QVector<MemorySegment*> *MyMemoryAddress)
{
    MyMemory = MyMemoryAddress;
    MemorySize = memorysize;
    //for to to create graphics segments vector
    for(int i=0;i<MyMemory->size();i++){
        GraphicsMemorySegmnet *segment = new GraphicsMemorySegmnet(this,Mymemory[i]->proccesName,Mymemory[i]->segmentName,
                                                          Mymemory[i]->segmentSize,((qreal)Mymemory[i]->segmentSize/MemorySize*FixedMemorySize),
                                                          Mymemory[i]->processID,Mymemory[i]->segmentID,
                                                          Mymemory[i]->isProcces);
        segment->segmentStartAddress = Mymemory[i]->segmentStartAddress;
        segments.push_back(segment);
    }


    for(int i=0;i<segments.size();i++){
        scene->addItem(segments[i]);
        if(i==0){
            segments[i]->setPos(XaxisCenter,YaxisMemoryBegin);
            segments[i]->YaxisFinish = segments[i]->SegmentGraphicsSize+YaxisMemoryBegin;
        }
        else {
           segments[i]->setPos(XaxisCenter,segments[i-1]->YaxisFinish);
           segments[i]->YaxisFinish = segments[i]->SegmentGraphicsSize+segments[i-1]->YaxisFinish;

        }

        if(segments[i]->IsProcess){
            QString tooltiptext = "<html><body><h4>Process Name:"+ segments[i]->ProcessName +"</h4>"
                                  "<h4>Segment Name:"+" "+ segments[i]->SegmentName +"</h4>"
                                  "<h4>Segment Size:"+" "+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                  "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";

            segments[i]->QGraphicsItem::setToolTip(tooltiptext);
        }
        else {
            QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                  "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                  "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
            segments[i]->QGraphicsItem::setToolTip(tooltiptext);
        }

    }


}

void Graphics::compactMemoryHoles(int ProccessID)
{
    it = segments.begin();
    for(int i=0;i<this->segments.size();i++,it++){
        // if deallocating at begin of memory
        if(i==0 && segments[i]->ProccessId == ProccessID && segments.size() !=1 ){
            if(!segments[i+1]->IsProcess){
                segments[i+1]->QGraphicsItem::hide();

                //updates On hole after deallocation
                segments[i]->SegmentGraphicsSize += segments[i+1]->SegmentGraphicsSize;
                segments[i]->SegmentSize += segments[i+1]->SegmentSize;
                segments[i]->YaxisFinish = segments[i+1]->YaxisFinish;
                segments[i]->IsProcess = false;
                segments[i]->ProccessId = -1;
                segments[i]->ProcessName = "";
                segments[i]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();

                QVector<GraphicsMemorySegmnet*>::iterator eraseIt = it;
                segments.erase(++eraseIt);
                i--;
                it--;
            }
            else{
                segments[i]->IsProcess=false;
                segments[i]->ProccessId = -1;
                segments[i]->ProcessName = "";
                segments[i]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();
            }
        }
        //if deallocating at end of memory
        else if(i==segments.size()-1 && segments[i]->ProccessId == ProccessID && segments.size() !=1){
            if(!segments[i-1]->IsProcess){
                segments[i]->QGraphicsItem::hide();

                //updates On hole after deallocation
                segments[i-1]->SegmentGraphicsSize += segments[i]->SegmentGraphicsSize;
                segments[i-1]->SegmentSize += segments[i]->SegmentSize;
                segments[i-1]->YaxisFinish = segments[i]->YaxisFinish;
                segments[i-1]->IsProcess = false;
                segments[i-1]->ProccessId = -1;
                segments[i-1]->ProcessName = "";
                segments[i-1]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i-1]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i-1]->QGraphicsItem::update();

                QVector<GraphicsMemorySegmnet*>::iterator eraseIt = it;
                segments.erase(eraseIt);
                i--;
                it--;
            }
            else{
                segments[i]->IsProcess=false;
                segments[i]->ProccessId = -1;
                segments[i]->ProcessName = "";
                segments[i]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();
            }
        }
        // if deallocating at the middle of memory
        else if(segments[i]->ProccessId == ProccessID && segments.size() !=1){
            //if only the memory before it is hole
            if(!segments[i-1]->IsProcess){
                segments[i]->QGraphicsItem::hide();

                //updates On hole after deallocation
                segments[i-1]->SegmentGraphicsSize += segments[i]->SegmentGraphicsSize;
                segments[i-1]->SegmentSize += segments[i]->SegmentSize;
                segments[i-1]->YaxisFinish = segments[i]->YaxisFinish;
                segments[i-1]->IsProcess = false;
                segments[i-1]->ProccessId = -1;
                segments[i-1]->ProcessName = "";
                segments[i-1]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i-1]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i-1]->QGraphicsItem::update();

                QVector<GraphicsMemorySegmnet*>::iterator eraseIt = it;
                segments.erase(eraseIt);
                i--;
                it--;
            }
            //if only the memory after it is a hole
            if(!segments[i+1]->IsProcess){
                segments[i+1]->QGraphicsItem::hide();

                //updates On hole after deallocation
                segments[i]->SegmentGraphicsSize += segments[i+1]->SegmentGraphicsSize;
                segments[i]->SegmentSize += segments[i+1]->SegmentSize;
                segments[i]->YaxisFinish = segments[i+1]->YaxisFinish;
                segments[i]->IsProcess = false;
                segments[i]->ProccessId = -1;
                segments[i]->ProcessName = "";
                segments[i]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();

                QVector<GraphicsMemorySegmnet*>::iterator eraseIt = it;
                segments.erase(++eraseIt);
                i--;
                it--;
            }

            //if no hole before or after
            if(i!=0 && segments[i+1]->IsProcess && segments[i-1]->IsProcess){
                segments[i]->IsProcess=false;
                segments[i]->ProccessId = -1;
                segments[i]->ProcessName = "";
                segments[i]->SegmentName = "";
                QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();
            }
        }
        // if only a reserved memroy is in memory
        else if( segments.size() ==1){
            segments[i]->IsProcess=false;
            segments[i]->ProccessId = -1;
            segments[i]->ProcessName = "";
            segments[i]->SegmentName = "";
            QString tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                  "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                  "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
            segments[i]->QGraphicsItem::setToolTip(tooltiptext);
            segments[i]->QGraphicsItem::update();
        }
    }

    updateMemoryAfterDeallocation();
}

void Graphics::addProccesToHole(int holeID, MemorySegment processSegment)
{
    GraphicsMemorySegmnet *addedSegment = new GraphicsMemorySegmnet(this,processSegment.proccesName,processSegment.segmentName
                                                                    ,processSegment.segmentSize,((double)processSegment.segmentSize/MemorySize*FixedMemorySize),
                                                                   processSegment.processID,processSegment.segmentID,processSegment.isProcces);

    it = segments.begin();
    for(int i=0;i<segments.size();i++,it++){
        if(segments[i]->SegmentId == holeID){

            addedSegment->segmentStartAddress = segments[i]->segmentStartAddress;
            if(i==0){
                addedSegment->YaxisFinish = addedSegment->SegmentGraphicsSize + YaxisMemoryBegin;
                addedSegment->setPos(XaxisCenter,YaxisMemoryBegin);
            }
            else {
                addedSegment->YaxisFinish = segments[i-1]->YaxisFinish + addedSegment->SegmentGraphicsSize;
                addedSegment->setPos(XaxisCenter,segments[i-1]->YaxisFinish);
            }
            QString tooltiptext = "<html><body><h4>Process Name:"+ addedSegment->ProcessName +"</h4>"
                                  "<h4>Segment Name:"+" "+ addedSegment->SegmentName +"</h4>"
                                  "<h4>Segment Size:"+" "+ QString::number(addedSegment->SegmentSize) +"</h4>"
                                  "<h4>Starting Address:"+" "+ QString::number(addedSegment->segmentStartAddress) +"</h4></body></html>";
            addedSegment->QGraphicsItem::setToolTip(tooltiptext);
            addedSegment->QGraphicsItem::update();
            if((int)addedSegment->SegmentSize == (int)segments[i]->SegmentSize){
                segments[i]->QGraphicsItem::hide();
                QVector<GraphicsMemorySegmnet*>::iterator eraseIt = it;
                segments.erase(eraseIt);

            }
            else {
                segments[i]->SegmentSize -= addedSegment->SegmentSize;
                segments[i]->SegmentGraphicsSize -=addedSegment->SegmentGraphicsSize;
                segments[i]->segmentStartAddress = addedSegment->segmentStartAddress+addedSegment->SegmentSize;
                segments[i]->setY(addedSegment->YaxisFinish);
                tooltiptext = "<html><body><h3>Memory Hole</h3>"
                                      "<h4>Hole Size:"+ QString::number(segments[i]->SegmentSize) +"</h4>"
                                      "<h4>Starting Address:"+" "+ QString::number(segments[i]->segmentStartAddress) +"</h4></body></html>";
                segments[i]->QGraphicsItem::setToolTip(tooltiptext);
                segments[i]->QGraphicsItem::update();
            }


            segments.insert(i,addedSegment);
            scene->addItem(addedSegment);
            break;
        }
    }
    updateMemoryAfterDeallocation();
}

void Graphics::updateMemoryAfterDeallocation()
{
    int MyMemorySize = MyMemory->size();
    for(int i=0;i<MyMemorySize;i++){
         MemorySegment *segment = MyMemory->first();
         MyMemory->pop_front();
         delete segment;
    }
    for(int i=0;i<segments.size();i++){
        MemorySegment *segment = new MemorySegment(segments[i]->ProcessName,segments[i]->SegmentName,segments[i]->segmentStartAddress,
                                                          segments[i]->SegmentSize,
                                                          segments[i]->SegmentId,segments[i]->ProccessId,
                                                          segments[i]->IsProcess);
        MyMemory->push_back(segment);
    }
}

void Graphics::destoryMemory()
{
    while(!segments.isEmpty()){
         GraphicsMemorySegmnet *segment = segments.first();
         segments.pop_front();
         segment->QGraphicsItem::hide();
    }

}





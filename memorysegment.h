#ifndef MEMORYSEGMENT_H
#define MEMORYSEGMENT_H

#include <QString>

class MemorySegment
{
public:
    MemorySegment();
    MemorySegment(QString proccesName,QString segmentName,int segmentStartAddress,int segmentSize,int SegmentID,int processID,bool IsProcces);

    QString proccesName;
    QString segmentName;
    int segmentStartAddress;
    int segmentSize;
    int segmentID;
    int processID;
    bool isProcces;
    // members to add segments to holes after algorthms
    int holeId;

};

#endif // MEMORYSEGMENT_H

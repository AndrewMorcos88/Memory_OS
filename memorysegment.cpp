#include "memorysegment.h"



MemorySegment::MemorySegment()
{

}

MemorySegment::MemorySegment(QString proccesname, QString segmentname, int segmentstartaddress, int segmentsize, int segmentiD, int processiD, bool isprocces)
{
     proccesName = proccesname;
     segmentName= segmentname;
     segmentStartAddress = segmentstartaddress;
     segmentSize = segmentsize ;
     segmentID = segmentiD;
     processID = processiD;
     isProcces = isprocces;
     holeId = -1;
}

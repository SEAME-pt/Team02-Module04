

#include "RaceTrack.h"

RaceTrack::RaceTrack()
{}

RaceTrack::~RaceTrack()
{}

void RaceTrack::setSize(int size)
{
    _size = size;
}
void RaceTrack::setFinishLine(int finishLine)
{
    _finishLine = finishLine;
}
int RaceTrack::getSize()
{
    return _size;
}

int RaceTrack::getFinishLine()
{
    return _finishLine;
}
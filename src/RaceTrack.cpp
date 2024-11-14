

#include "../include/RaceTrack.h"

RaceTrack::RaceTrack()
{}

RaceTrack::~RaceTrack()
{}

void RaceTrack::setWidth(int width)
{
    this->_width = width;
}

void RaceTrack::setHeight(int height)
{
    this->_height = height;
}

void RaceTrack::setFinishLine(int finishLine)
{
    _finishLine = finishLine;
}

int RaceTrack::getWidth() const
{
    return this->_width;
}

int RaceTrack::getHeight() const
{
    return this->_height;
}

int RaceTrack::getFinishLine()
{
    return _finishLine;
}
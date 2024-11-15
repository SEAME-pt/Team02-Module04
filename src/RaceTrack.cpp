

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

void RaceTrack::setFinishLineX(int finishLineX)
{
    _finishLineX = finishLineX;
}

void RaceTrack::setFinishLineY(int finishLineY)
{
    _finishLineY = finishLineY;
}

int RaceTrack::getWidth() const
{
    return this->_width;
}

int RaceTrack::getHeight() const
{
    return this->_height;
}

int RaceTrack::getFinishLineX()
{
    return _finishLineX;
}

int RaceTrack::getFinishLineY()
{
    return _finishLineY;
}